/* This is an auto generated file, please don't modify it. */

#ifndef _AIC_IMAGE_CFG_JSON_PARTITION_TABLE_H_
#define _AIC_IMAGE_CFG_JSON_PARTITION_TABLE_H_

#define IMAGE_CFG_JSON_PARTS_MTD "spi0x100.0:64k(spl),4k(pdata),256K(uploader),1m(app1)"


#ifdef FAL_PART_HAS_TABLE_CFG
#define FAL_PART_TABLE \
{ \
    {FAL_PART_MAGIC_WORD, "spl",FAL_USING_NOR_FLASH_DEV_NAME, 0,65536,0}, \
    {FAL_PART_MAGIC_WORD, "pdata",FAL_USING_NOR_FLASH_DEV_NAME, 65536,4096,0}, \
    {FAL_PART_MAGIC_WORD, "uploader",FAL_USING_NOR_FLASH_DEV_NAME, 69632,262144,0}, \
    {FAL_PART_MAGIC_WORD, "app1",FAL_USING_NOR_FLASH_DEV_NAME, 331776,1048576,0}, \
}
#endif

#endif
