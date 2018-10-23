#include "HAL.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MIN_SECTOR_SIZE 512 /*minimum number of bytes in a sector*/
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
static FILE *g_fatdisk;
/*******************************************************************************
 * Code
 ******************************************************************************/

bool kmc_open_fat_disk(uint8_t path[])
{
    g_fatdisk = fopen(path, "rb"); /*open FAT image file*/
    
    if (g_fatdisk == NULL) /*check if cannot open the file*/
    {
        return false;
    }
    return true;
}

void kmc_close_fat_disk()
{
    fclose(g_fatdisk);
}

uint32_t kmc_convert_to_big_endian(uint8_t index, uint8_t num, uint8_t buff[])
{
    uint8_t i = 0; /*increment*/
    uint32_t returnval = 0; /*return value*/
    
    for (i = index+num-1; i >= index; i--)
    {
        returnval = (returnval<<8) | buff[i];
    }

    return returnval;
}

void kmc_parse_boot_sector(fat_boot_sector *boot_sector)
{
    uint8_t buff[MIN_SECTOR_SIZE]; /*save the first 512 bytes to get necessary info */

    fseek(g_fatdisk,0,SEEK_SET); /*seek the first byte of disk (start boot region)*/
    fread(buff,MIN_SECTOR_SIZE,1,g_fatdisk); /*save data of the first 512 bytes in the boot sector region to buff*/

    boot_sector->bytes_per_sector = kmc_convert_to_big_endian(11,2,buff);/*byte 11th and 12th is number of bytes per sector*/
    boot_sector->sectors_per_cluster = buff[13]; /*byte 13th is number of sectors per cluster*/
    boot_sector->reserved_sector_count = kmc_convert_to_big_endian(14,2,buff); /*byte 14th and 15th is number of sectors before FAT TABLE*/
    boot_sector->fat_count = buff[16]; /*byte 16th is number of fat tables*/
    boot_sector->max_root_entries = kmc_convert_to_big_endian(17,2,buff); /*byte 17+18th is maximum entries of root directory (fat12 and 16 only)*/
    boot_sector->total_sectors = kmc_convert_to_big_endian(19,2,buff); /*byte 19+20th is total sectors of volume*/
    boot_sector->sectors_per_fat = kmc_convert_to_big_endian(22,2,buff); /*byte 22+23 is number of sectors per FAT table*/
}

int32_t kmc_read_sector(uint32_t index, uint8_t *buff)
{
    int32_t byte_read = 0; /*the number of read bytes*/
    fat_boot_sector boot_sector;
    
    kmc_parse_boot_sector(&boot_sector); /*get info from boot sector region*/

    fseek(g_fatdisk, boot_sector.bytes_per_sector*index, SEEK_SET); /*find position of the index sector*/
    byte_read = fread(buff, boot_sector.bytes_per_sector, 1, g_fatdisk); /*reading data from g_fatdisk stream into buffer*/

    return byte_read;
}

int32_t kmc_read_multi_sector(uint32_t index, uint32_t num, uint8_t *buff)
{
    uint8_t i = 0; /*increment*/
    int32_t byte_read_multi_sector = 0; /*return value, the number of read bytes in multi sectors*/
    fat_boot_sector boot_sector;

    kmc_parse_boot_sector(&boot_sector); /*get info from boot sector region*/

    for (i = 0; i < num; i++) /*read "num" sectors continuously, start at sector index*/
    {
        byte_read_multi_sector += kmc_read_sector(i+index, buff+i*boot_sector.bytes_per_sector);
    }

    return byte_read_multi_sector;
}
