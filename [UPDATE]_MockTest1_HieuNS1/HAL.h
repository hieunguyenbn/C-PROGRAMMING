#ifndef _HAL_H_
#define _HAL_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
/*******************************************************************************
 * Definitions
 ******************************************************************************/
typedef struct bootSector {
    uint16_t bytes_per_sector; /*byte 11+12th, boot sector has commonly 512 bytes*/
    uint8_t sectors_per_cluster; /*byte 13th, powers of 2, 1 ~ 128 */
    uint16_t reserved_sector_count; /*byte 14+15th, sectors before first FAT*/
    uint8_t fat_count; /*byte 16th, number of fats (almost always 2)*/
    uint16_t max_root_entries; /*byte 17+18th, maximum number of root directory entries*/
    uint16_t total_sectors; /*byte 19+20th, total sectors of the volume*/
    uint16_t sectors_per_fat; /*byte 22+23th, number of sectors per fat*/
}fat_boot_sector;

/*******************************************************************************
 * API
 ******************************************************************************/
 /*!
 * @brief <Open the fat disk>
 *
 * @param path[] [input] <path to the fat disk in operating system>.
 *
 * @return <true if the opening process is OK, false if error occurs>.
 */
bool kmc_open_fat_disk(uint8_t path[]);
 /*!
 * @brief <close fat disk>
 *
 * @return <no return>.
 */
void kmc_close_fat_disk();
 /*!
 * @brief <convert to big endian type of a little endian number having "num" bytes, starting at index byte of data array>
 *
 * @param index [input] <the starting byte in data>.
 *
 * @param num [input] <number of bytes in data>.
 *
 * @param buff[] [input] <data array>.
 *
 * @return <value of the number in big endian type>.
 */
uint32_t kmc_convert_to_big_endian(uint8_t index, uint8_t num, uint8_t buff[]);
 /*!
 * @brief <parsing data in boot sector region to get necessary info>
 *
 * @param boot_sector [output] <save data from boot sector region>.
 *
 * @return <no return>.
 */
void kmc_parse_boot_sector(fat_boot_sector boot_sector;);
 /*!
 * @brief <Read the "index" sector into buffer>
 *
 * @param index [input] <sector index need to read>.
 *
 * @param buff [output] <point to address saving data read from the sector>.
 *
 * @return <the number of read bytes>.
 */
int32_t kmc_read_sector(uint32_t index, uint8_t *buff);
 /*!
 * @brief <Read "num" sectors continously, start at the "index" sector>
 *
 * @param index [input] <the start sector>.
 *
 * @param buff [output] <point to an array to save data read from "num" sectors>.
 *
 * @return <the number of read bytes>.
 */
int32_t kmc_read_multi_sector(uint32_t index, uint32_t num, uint8_t *buff);

#endif
