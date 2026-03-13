#include <flash_drv.h>
#include "aic_ecat_foe.h"
#include "ecat_def.h"

#if FOE_SUPPORTED

#include "foeappl.h"
#include "servo_drv_setting.h"

#define FOE_PASSWORD		(0x00000000)

#define FILE_NAME_MAX_LEN	(32)

static u32 read_file_size;
static char *read_file_ptr;
static u32 write_file_pos;

const char* ecat_foe_get_file_name(char *file_name, u16 nameSize);
u32 ecat_foe_get_file_size(void);
char* ecat_foe_get_file_ptr(void);
u32 ecat_foe_erase_flash(void);
u32 ecat_foe_get_flash_size(void);
u32 ecat_foe_write_flash(char *data, u32 addr_off, u32 size, BOOL bDataFollowing);

//#ifdef ABS_SERVO_EXAMPLE
static u32 m_ProgramAddr = 0;

const char* ecat_foe_get_file_name(char *file_name, u16 nameSize)
{
	/*
	if(0 == _strncmp(partition_info.part[BOOTLOADER].name, file_name, nameSize)){
		m_ProgramAddr = partition_info.part[BOOTLOADER].start;
		cur_part = &partition_info.part[BOOTLOADER];
		foe_flash_log("part name: %s\n", partition_info.part[BOOTLOADER].name);
	}else if(0 == _strncmp(partition_info.part[APP].name, file_name, nameSize)){
		m_ProgramAddr = partition_info.part[APP].start;
		cur_part = &partition_info.part[APP];
		foe_flash_log("part name: %s\n", partition_info.part[APP].name);
	}else if(0 == _strncmp(partition_info.part[PARTITION].name, file_name, nameSize)){
		m_ProgramAddr = partition_info.part[PARTITION].start;
		cur_part = &partition_info.part[PARTITION];
		foe_flash_log("part name: %s\n", partition_info.part[PARTITION].name);
	}else{
		cur_part = NULL;
		return NULL;
	}
	*/

	u8 temp_name[32];
	_memset(temp_name, 0, 32);
	for (u8 i = 0; i < BIN_INDEX_MAX; i++) {
		if (_strncmp(partition_info.part[i].name, file_name, nameSize) == 0) {
			cur_part = &partition_info.part[i];
			break;
		}

		if (_memcmp(partition_info.part[i].name, temp_name, 32) == 0) {
			cur_part = NULL;
			return NULL;
		}
	}
	return cur_part->name;
}

u32 ecat_foe_get_file_size(void)
{
	volatile u32 file_size = 0;
	if (cur_part != NULL) {
		flash_read_bank((u8*)&file_size, (cur_part->start + cur_part->size) - 4, 4);
		if (file_size > cur_part->size) {
			return cur_part->size;	//整个分区的大小
		} else {
			return file_size;
		}
	} else {
		return 0;
	}
}

char* ecat_foe_get_file_ptr(void)
{
	if(cur_part != NULL){
		return cur_part->name;
	}else{
		return NULL;
	}
}


u32 ecat_foe_erase_flash(void)
{

	if(cur_part != NULL){
		flash_program_start(cur_part);
		return 0;
	}else{
		return 1;	//整个分区的大小
	}
}

u32 ecat_foe_get_flash_size(void)
{
	if(cur_part != NULL){
		return cur_part->start + cur_part->size;
	}else{
		return 0;	//整个分区的大小
	}
}

u32 ecat_foe_write_flash(char *data, u32 addr_off, u32 size, BOOL bDataFollowing)
{
	if(size > 0){
		flash_write_bank(data, addr_off, size);
	}
	//memcpy(&test_file[addr_off], data, size);
	if(bDataFollowing){
		return 0;
	} else {
		volatile u32 this_size;
		volatile uint32_t file_size = (addr_off + size) - cur_part->start;
		flash_write_bank((u8 *)&file_size, (cur_part->start + cur_part->size) - 4, 4);
		flash_read_bank((u8*)&file_size, (cur_part->start + cur_part->size) - 4, 4);
		flash_program_done(cur_part);
		//下载完成，校验文件
		return 1; //1=校验通过 2=校验失败
	}
}
//#endif

/*Check the name and password and if the copy the first file segment to pData. The segment length has to be returned.*/
UINT16 AIC_FoE_Read(UINT16 MBXMEM * pName, UINT16 nameSize, UINT32 password, UINT16 maxBlockSize, UINT16 *pData)
{
    UINT16 read_size = 0;
    char *name = (char *)pName;
    char *data = (char *)pData;
    char file_name[FILE_NAME_MAX_LEN];

    printk("read file start\n");
    /*check name*/
    if(nameSize > FILE_NAME_MAX_LEN - 1)
    	return ECAT_FOE_ERRCODE_ACCESS;

    //memcpy(file_name, name, nameSize);


    if(memcmp(name, ecat_foe_get_file_name(name, nameSize), nameSize)){
    	return ECAT_FOE_ERRCODE_NOTFOUND;
    }
    foe_flash_log("name pass\n");

    if(cur_part == NULL){
    	foe_flash_log("cur_part is NULL\n");
    	return ECAT_FOE_ERRCODE_NOTFOUND;
    }

//    /*check password*/
//    if(cur_part->foe_password != password)
//    	return ECAT_FOE_ERRCODE_NORIGHTS;
    foe_flash_log("password pass\n");
    /*check file*/
    read_file_size = ecat_foe_get_file_size();
    printk("read_file_size=%d\n", read_file_size);
    read_file_ptr = ecat_foe_get_file_ptr();
    if(read_file_size == 0 || read_file_ptr == 0)
    	return ECAT_FOE_ERRCODE_NOTDEFINED;

    foe_flash_log("read_file_size read_file_ptr pass\n");

    if(maxBlockSize > read_file_size)
    	read_size = read_file_size;
    else
    	read_size = maxBlockSize;

    flash_read_bank(data, cur_part->start, read_size);
    /*copy file data*/
    //memcpy(data, read_file_ptr, read_size);

    return read_size;
}

/*Copy the file segment according the offset to pData. The segment length has to be returned.*/
UINT16 AIC_FoE_ReadData(UINT32 offset, UINT16 maxBlockSize, UINT16 *pData)
{
	char *data = (char *)pData;
	UINT16 read_size = 0;
	BOOL read_end = 0;
	if(offset >= read_file_size)
		return 0;	/*finished*/


	if (offset + maxBlockSize < read_file_size) {
		read_size = maxBlockSize;
	} else {
		read_size = read_file_size - offset;
		read_end = 1;
	}

	//foe_flash_log("ADDR= 0x%x, OFS=%d, S=%d\n", cur_part->start+offset, offset, read_size);
	/*copy file data*/
	//memcpy(data, read_file_ptr + offset, read_size);
	flash_read_bank(data, cur_part->start+offset, read_size);

    return read_size;
}

/*check the file name and password of the file to be written*/
UINT16 AIC_FoE_Write(UINT16 MBXMEM * pName, UINT16 nameSize, UINT32 password)
{
	char *name = (char *)pName;
	char file_name[FILE_NAME_MAX_LEN];
	printk("write file start\n");

	/*check name*/
	if(nameSize > FILE_NAME_MAX_LEN - 1)
		return ECAT_FOE_ERRCODE_ACCESS;

    /*check name*/
    if(nameSize > FILE_NAME_MAX_LEN - 1)
    	return ECAT_FOE_ERRCODE_ACCESS;

    if(memcmp(name, ecat_foe_get_file_name(name, nameSize), nameSize)){
    	return ECAT_FOE_ERRCODE_NOTFOUND;
    }
    foe_flash_log("[%s]: name pass\n", __func__);

    if(cur_part == NULL){
    	foe_flash_log("[%s]: cur_part is NULL\n", __func__);
    	return ECAT_FOE_ERRCODE_NOTFOUND;
    }

//    /*check password*/
//    if(cur_part->foe_password != password)
//    	return ECAT_FOE_ERRCODE_NORIGHTS;

    foe_flash_log("[%s]: password pass\n", __func__);

    if(ecat_foe_erase_flash())
    	return ECAT_FOE_ERRCODE_ACCESS;

    write_file_pos = cur_part->start;

    return 0;
}

/*copy the data block to the local file buffer*/
UINT16 AIC_FoE_WriteData(UINT16 MBXMEM * pData, UINT16 Size, BOOL bDataFollowing)
{
	u32 ret;
	char *data = (char *)pData;

    if(write_file_pos + Size > ecat_foe_get_flash_size())
    	return ECAT_FOE_ERRCODE_DISKFULL;

    //printk("FoE WD: FL=%d, S=%d\n", bDataFollowing, Size);
    if(data != 0)
    {
    	ret = ecat_foe_write_flash(data, write_file_pos, Size, bDataFollowing);
    	if(ret == 0) {				/*write success*/
    		write_file_pos+=Size;
    	} else if(ret == 1) {		/*finished and verify pass*/
    		write_file_pos = 0;
    	} else {					/*verify fail*/
    		return ECAT_FOE_ERRCODE_INVALID_CHECKSUM;
    	}
    } else {
    	return ECAT_FOE_ERRCODE_NOTDEFINED;
    }

    return 0;
}
#endif
