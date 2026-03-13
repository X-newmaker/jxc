#ifndef _DOWNLOAD_H_
#define _DOWNLOAD_H_

/* Includes ------------------------------------------------------------------*/
#include <all_inc.h>
#include <sfud.h>

#define BL_NO_UPGRADE 1

#define foe_flash_log printk
extern u32 FLASH_SIZE;
#define SYSCFG_BASE                 0x18000000UL /* - 0x18000FFF, 4KB   ,64KB   */
#define SYSCFG_FLASH_CFG            0x1F0
#define syscfg_readl(reg)           readl(SYSCFG_BASE + reg)
#define syscfg_writel(val, reg)     writel(val, SYSCFG_BASE + reg)

#define FLASH_START_ADDR 0

//分区表的这几个分区需要固定命名，否则bootlaoder无法按照流程加载跳转
#define PNAME_BOOTLOADER 	"spl"
#define PNAME_PARTITION 	"pdata"
#define PNAME_UPLOADER 		"uploader"
#define PNAME_APP1 			"app1"
#define PNAME_APP2 			"app2"
#define BIN_INDEX_MAX 10

//AIC头有entry, load, file_size,
typedef struct
{
	u8 name[32];		//分区名字
	u32 start;			//分区在flash中的偏移地址
	u32 size;			//分区的大小
}part_t;

typedef struct
{
    u32 UpgrageOrNot;			 // 1为有升级   0为没有要升级
    part_t part[BIN_INDEX_MAX];
    u32 this_crc;				//该结构体的crc值。
}partition_info_t;

char* aic_spinor_get_partition_string(sfud_flash *me_flash);
part_t *get_part_by_name(char *name);
void list_part(void);
part_t* mtd_parts_parse(char *parts, u32 spi_bus);

void flash_program_start(part_t *part);
void flash_program_done(part_t *part);
u32 flash_write_bank(u8 *pData, u32 addr, u16 size);
u32 flash_read_bank(u8 *pData, u32 addr, u16 size);
void flash_init(void);
void flash_save_partition(void);
extern sfud_flash *me_flash;
extern partition_info_t partition_info;
extern part_t *cur_part;



typedef enum sw_reboot_r{
	SW_REBOOT_R_CLR		=    0,
	SW_REBOOT_R_RESET	=    1,
	SW_REBOOT_R_TOUPDATE	=    2,	//跳转到UPLOADER的标志
	SW_REBOOT_R_INUPDATE	=    3,	//在UPLOADER的标志
	SW_REBOOT_R_MAX		=    255,
}sw_reboot_r_t;
sw_reboot_r_t get_wri_sw_reboot_r(void);
sw_reboot_r_t set_wri_sw_reboot_r(sw_reboot_r_t r);
u8 get_wri_sw_bapp_fail_times(void);
u8 set_wri_sw_bapp_fail_times(u8 times);
#endif
