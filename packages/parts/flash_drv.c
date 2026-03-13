#include <flash_drv.h>
#include <image.h>
#include "sfud.h"
#include "partition_table.h"

partition_info_t partition_info;
part_t *cur_part = NULL;

u32 FLASH_SIZE = 0x200000;
static u8 mask_done = 0; //每次烧录过程中，只进一次。

extern void sfud_hexdump(const u8 *ptr, u32 buflen);

#define SPI_PMAP		(BASE_SYSCFG + 0x1F0)
void spic_pin_remap(u32 pin_map1, u32 pin_map2, u32 srcsel)
{
	cbit(0xFF<<8, SPI_PMAP);
	sbit((pin_map1<<12 | pin_map2<<8), SPI_PMAP);

	cbit(0x3, SPI_PMAP);
	sbit(srcsel, SPI_PMAP);
}


u16 flash_crc16(u8 *pData, u16 sLen)
{
   u16 CRC = 0;    //
   u16 i = 0;

   while (sLen--)  //len是所要计算的长度
   {
       CRC = CRC^(s32)(*pData++) << 8; //
       for (i=8; i!=0; i--)
       {
           if (CRC & 0x8000)
               CRC = CRC << 1 ^ 0x1021;
           else
               CRC = CRC << 1;
       }
   }
   return CRC;
}


static u32 flash_pages_mask(part_t *part)
{
	if(!mask_done){
		//upgrade_log("flash_pages_mask: part->name=%s...\n", part->name);
		sfud_erase(me_flash, part->start, part->size);
		mask_done = 1;	//标记已经擦除。
	}

}


u32 flash_write_bank(u8 *pData, u32 addr, u16 size)
{
	sfud_err err;
//	upgrade_log("flash_write_bank: addr=0x%x, size=%d\n", addr, size);
	err = sfud_write(me_flash, addr, size, pData);
	mask_done = 1; //标记已经擦除, 写入新数据后，再触发flash_program_done前，保持置1
}

u32 flash_read_bank(u8 *pData, u32 addr, u16 size)
{
	sfud_err err;
//	upgrade_log("flash_read_bank: addr=0x%x, size=%d\n", addr, size);
	err = sfud_read(me_flash, addr, size, pData);
	return err;
}


void flash_program_start(part_t *part)
{
	//upgrade_log("flash_program_start: part->name=%s...\n", part->name);
	set_wri_sw_reboot_r(SW_REBOOT_R_INUPDATE); //进入FOE升级流程
	flash_pages_mask(part);
}

/*只在不更新分区划分的情况下，才能完整记录信息。*/
void flash_save_partition(void)
{
	u16 part_info_size = sizeof(partition_info);
	part_t *p = get_part_by_name(PNAME_PARTITION);
	sfud_erase(me_flash, p->start, p->size);

	u16 part_info_crc = flash_crc16((u8*)&partition_info, part_info_size-4);
	partition_info.this_crc = part_info_crc;
	sfud_write(me_flash,  p->start, part_info_size, (u8 *)&partition_info);

}

void flash_program_done(part_t *part)
{
	//upgrade_log("flash_program_done: part->name=%s...\n", part->name);
	mask_done = 0;

	//part->upgrade_times++;				//记录更新次数
	partition_info.UpgrageOrNot = 0;	//清除升级标志

	if(0 == _strncmp(PNAME_BOOTLOADER, cur_part->name, _strlen(PNAME_BOOTLOADER))){
		//如果升级的是bootloader分区，需要把分区表信息擦除，否则flash中残留的是旧的bootloader分区数据。
		partition_info_t partition_info_temp;
		u16 part_info_size = sizeof(partition_info_temp);
		part_t *p = get_part_by_name(PNAME_BOOTLOADER);
		sfud_read(me_flash, p->start, part_info_size, (u8 *)&partition_info_temp);
		u16 part_info_crc = flash_crc16((u8*)&partition_info_temp, part_info_size-4);
		//主要是检测当前更新的分区，是否已经把PARTITION分区已经覆盖，如果已经覆盖，无需擦除，那么bootloader在启动时，将会把默认分区写入（即新分区表）
		if(part_info_crc == partition_info_temp.this_crc) {
			p = get_part_by_name(PNAME_PARTITION);
			sfud_erase(me_flash, p->start, p->size);
		}
	}else{
		flash_save_partition();	//写入flash中
	}
}

sfud_flash *me_flash;
extern sfud_flash* sfud_probe(u32 spi_bus);
void flash_init(void)
{
	unsigned long offset = 0;
	//uint8_t data[BUFFER_SIZE]={0x6};
	sfud_err err;
	//M7000 合封 flash 固定用法
	gpio_enable(GPIO_GRP_H, 0, 6, GPIO_FUN_2);
	gpio_pin_cfg(GPIO_GRP_H, 0, 6, GPIO_DRV_60R, GPIO_PULL_UP);
	spic_pin_remap(5,5,2);

	//初始化 flash
	me_flash = sfud_probe(0);

	//从bootloader.aic中解析获取分区表信息。
	aic_spinor_get_partition_string(me_flash);

	part_t *p = get_part_by_name(PNAME_PARTITION);
	partition_info_t partition_info_temp;
	u16 part_info_size = sizeof(partition_info_temp);
	sfud_read(me_flash, p->start, part_info_size, (u8 *)&partition_info_temp);
	u16 part_info_crc = flash_crc16((u8*)&partition_info_temp, part_info_size-4);
	if((part_info_crc == partition_info_temp.this_crc) && (0!=part_info_crc)) {
		if(partition_info.this_crc != partition_info_temp.this_crc){
			//如果存在partiton的分区表与从aicbin解析的分区表不一致，那就默认用bin解析出来的，把解析出来的写入分区表区域，供APP与其他固件使用。
			flash_save_partition();	//写入flash中
		}
	} else {
		//分区表区域没有完整的分区表信息，需要重新写入。
		flash_save_partition();	//写入flash中
	}

	cur_part = get_part_by_name(PNAME_APP1);
}



#define DATA_SECT_TYPE_DRAM        0x41490001
#define DATA_SECT_TYPE_SYS_UART    0x41490002
#define DATA_SECT_TYPE_SYS_JTAG    0x41490003
#define DATA_SECT_TYPE_SYS_UPGMODE 0x41490004
#define DATA_SECT_TYPE_PARTITION   0x41490005
#define DATA_SECT_TYPE_END         0x4149FFFF
#pragma GCC push_options
#pragma GCC optimize ("O0")

#define MAX_MTD_NAME 32
static int partition_count = 0;

part_t* get_part_by_name(char *name)
{
	u8 temp_name[32];
	_memset(temp_name, 0, 32);
	for (u8 i = 0; i < BIN_INDEX_MAX; i++) {
		if (_strncmp(partition_info.part[i].name, name, _strlen(name)) == 0) {
			return &partition_info.part[i];
		}

		if (_memcmp(partition_info.part[i].name, temp_name, 32) == 0) {
			return NULL;
		}
	}
}

void list_part(void)
{
	u8 temp_name[32];
	_memset(temp_name, 0, 32);
	partition_info_t *p = &partition_info;
	printk("UpgradeOrNot: %d\n", p->UpgrageOrNot);
	printk("-----------------\n");
	for (u8 i = 0; i < BIN_INDEX_MAX; i++) {
		if (_memcmp(partition_info.part[i].name, temp_name, 32) == 0) {
			break;
		}
		printk("PART[%d] INFO\n", i);
		printk("name: %s\n", p->part[i].name);
		printk("flash offset: 0x%x\n", p->part[i].start);
		printk("flash size: 0x%x\n", p->part[i].size);
		printk("-----------------\n");
	}
	printk("UpgradeOrNot: %d\n", p->this_crc);
}

// 自定义字符串转无符号长整型
static u32 custom_strtoul(const char *str, const char **endptr)
{
	u32 value = 0;

	while (*str >= '0' && *str <= '9') {
		value = value * 10 + (*str - '0');
		str++;
	}

	if (endptr) {
		*endptr = str;
	}

	return value;
}

// 解析单个分区描述
static int parse_single_partition(char *desc, u32 *start_addr)
{
	if (partition_count >= BIN_INDEX_MAX) {
		printk("Error: Maximum partitions reached (%d)\n", BIN_INDEX_MAX);
		return -1;
	}

	part_t *part = &partition_info.part[partition_count];
	_memset(part, 0, sizeof(part_t));

	char *p = desc;
	part->start = *start_addr;  // 默认使用传入的起始地址

	// 解析分区大小
	if (*p == '-') {
		part->size = 0;  // 特殊标记：使用剩余空间
		p++;
	} else {
		const char *end;
		part->size = custom_strtoul(p, &end);
		p = (char*) end;

		// 处理单位 (K/M/G)
		if ((*p == 'k') || (*p == 'K')) {
			part->size *= 1024;
			p++;
		} else if ((*p == 'm') || (*p == 'M')) {
			part->size *= (1024 * 1024);
			p++;
		} else if ((*p == 'g') || (*p == 'G')) {
			part->size *= (1024 * 1024 * 1024);
			p++;
		}
	}

	// 解析可选起始地址
	if (*p == '@') {
		p++;
		const char *end;
		part->start = custom_strtoul(p, &end);
		p = (char*) end;
	}

	// 解析分区名称
	if (*p != '(') {
		printk("Partition name missing: %s\n", p);
		return -1;
	}
	p++;

	int cnt = 0;
	while (*p != ')' && cnt < (MAX_MTD_NAME - 1)) {
		part->name[cnt++] = *p++;
	}
	part->name[cnt] = '\0';

	// 更新下一个分区的起始地址
	*start_addr = part->start + part->size;
	partition_count++;

	return 0;
}

part_t* mtd_parts_parse(char *parts, u32 spi_bus)
{
	partition_count = 0;  // 重置分区计数器

	if (!parts || !*parts) {
		printk("Empty partition string\n");
		return NULL;
	}

	// 根据SPI总线选择分区配置
	char *p = parts;
	if (spi_bus == 1) {
		while (*p && *p != '1')
			p++;
	} else if (spi_bus == 2) {
		while (*p && *p != '2')
			p++;
	}

	// 定位配置起始点
	while (*p && *p != ':')
		p++;
	if (*p != ':') {
		printk("Invalid mtdparts format: %s\n", parts);
		return NULL;
	}
	p++;

	u32 current_start = 0;
	char *part_start = p;

	// 迭代解析每个分区
	while (*p && partition_count < BIN_INDEX_MAX) {
		if (*p == ',' || *p == ';') {
			*p = '\0';  // 临时替换为字符串结束符
			if (parse_single_partition(part_start, &current_start) != 0) {
				return NULL;
			}
			part_start = p + 1;  // 移动到下一个分区
		}
		p++;
	}

	// 解析最后一个分区
	if (*part_start && partition_count < BIN_INDEX_MAX) {
		if (parse_single_partition(part_start, &current_start) != 0) {
			return NULL;
		}
	}

	return &partition_info.part[0];
}

// 获取分区数量
int get_partition_count(void)
{
	return partition_count;
}

// 获取分区指针
part_t* get_partition(int index)
{
	if (index < 0 || index >= partition_count) {
		return NULL;
	}
	return &partition_info.part[index];
}

u32* find_section(void *start, u32 len, u32 type) {

	u32 *p = start, *end, data_type;
	end = p + (len >> 2);
	while(p < end){
		data_type = *p;
		if(data_type == type){
			return p;
		}
		if(data_type == DATA_SECT_TYPE_END){
			return NULL;
		}
		p++;
	}
	return NULL;

}

u8* private_get_partition_string(void *res_addr, u32 len)
{
	u32 *p, data_len;

	if (res_addr == NULL) {
		return NULL;
	}

	/* Should be 4 byte aligned */
	if (((unsigned long) res_addr) & 0x3) {
		return NULL;
	}

	p = find_section(res_addr, len, DATA_SECT_TYPE_PARTITION);
	if (p == NULL) {
		return NULL;
	}
	p++;
	data_len = *p;
	p++;

	if (data_len == 0)
		return NULL;
	printk("data_len: %d\n", data_len);
	return (u8*) p;
}
#pragma GCC pop_options

char* aic_spinor_get_partition_string(sfud_flash *me_flash)
{
	struct image_header head;
	int ret = 0;
	sfud_err err;
	//加载镜像头
	err = sfud_read(me_flash, FLASH_START_ADDR, sizeof(head), (void*) &head);
	if (err) {
		printk("Application header read failed...\n");
	}

	//验证是否有效同
	ret = image_verify_magic((void*) &head, AIC_IMAGE_MAGIC);
	if (ret) {
		printk("Application header is unknown.\n");
	}

	if (head.priv_data_offset) {
		const u8 *parts = NULL;
		u8 buf[head.priv_data_len];
		sfud_read(me_flash, FLASH_START_ADDR + head.priv_data_offset, head.priv_data_len, buf);
		parts = private_get_partition_string(buf, head.priv_data_len);
		if (parts != NULL) {
			printk("parts info got from aic bin:\n");
		} else {
			printk("parts info use code define IMAGE_CFG_JSON_PARTS_MTD:\n");
			parts = (const u8*) IMAGE_CFG_JSON_PARTS_MTD;
		}
		printk("%s\n", parts);
		mtd_parts_parse((u8*) parts, 0);
	} else {
		u8 parts[] = IMAGE_CFG_JSON_PARTS_MTD;
		printk("parts info use code define IMAGE_CFG_JSON_PARTS_MTD:\n");
		printk("%s\n", parts);
		mtd_parts_parse(parts, 0);
	}

#if 0
	// 打印解析结果
	int count = get_partition_count();
	for (int i = 0; i < count; i++) {
		part_t *part = get_partition(i);
		printk("Partition %d: %s, start: 0x%x, size: 0x%x\n", i, part->name,
				part->start, part->size);
	}
#endif

	return NULL;
}


#define WRI_SYS_BAK (BASE_WRI + 0X104)
sw_reboot_r_t get_wri_sw_reboot_r(void)
{
	u32 result = 0;
	result = readl(WRI_SYS_BAK) & 0xFF;

	return (sw_reboot_r_t)result;
}

sw_reboot_r_t set_wri_sw_reboot_r(sw_reboot_r_t r)
{
	u32 result = 0;
	result = (readl(WRI_SYS_BAK) & 0xffffff00) | r;
	writel(result, WRI_SYS_BAK);

	return (sw_reboot_r_t)(result & 0xFF);
}

u8 get_wri_sw_bapp_fail_times(void)
{
	u32 result = 0;
	result = (readl(WRI_SYS_BAK)>>8) & 0xFF;

	return (u8)result;
}

u8 set_wri_sw_bapp_fail_times(u8 times)
{
	u32 result = 0;
	result = (readl(WRI_SYS_BAK) & 0xffff00ff) | ((u32)times<<8);
	writel(result, WRI_SYS_BAK);

	return (u8)((result>>8) & 0xFF);
}
/********************************* END ****************************************/

