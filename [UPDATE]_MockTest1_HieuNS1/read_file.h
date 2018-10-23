#ifndef _READ_FILE_H_
#define _READ_FILE_H_
#include "HAL.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define OK                          0
#define NOT_OK                      1
#define FIRST_LOGIC_CLUSTER         2
/*define properties of the directory entry*/
#define DIR_ENTRY_SIZE             32
#define DIR_ENTRY_FREE           0x00
#define DIR_ENTRY_DELETED        0xE5
#define END_CLUSTER             0xFF8
#define BAD_CLUSTER             0xFF7
#define BELL                     0x07
#define START_CLUSTER_INDEX        26
/*define attribute values*/
#define ATTR_READ_ONLY           0x01
#define ATTR_HIDDEN              0x02
#define ATTR_SYSTEM              0x04
#define ATTR_VOLUME              0x08
#define ATTR_SUB_DIR             0x10
#define ATTR_ARCHIVE             0x20
#define ATTR_LFN                 0x0F
/*index of attribute field in the entry*/
#define ATTRIBUTE_INDEX            11
/*the starting index of file's size field in the directory entry*/
#define FILE_SIZE_INDEX            28
/*size of a fat12 entry*/
#define FAT12_ENTRY_SIZE          1.5

typedef struct directory_entry {
    uint8_t file_name[ATTRIBUTE_INDEX]; /*first 11 bytes (0-10)*/
    uint8_t attribute; /*byte 11th*/
    uint16_t start_cluster; /*byte 26th in an entry*/
    uint32_t file_size; /*4 last bytes*/
}dir_entry;
/*******************************************************************************
 * API
 ******************************************************************************/
  /*!
 * @brief <convert two continuous bytes in fat table to a 12 bit integer number">
 *
 * @param index [input] <index of the fat entry>.
 *
 * @param low_byte [input] <low byte in the two bytes need to convert>.
 *
 * @param high_byte [input] <high byte in the two bytes need to convert>.
 *
 * @return <an integer of 12 bits>.
 */
uint16_t fatfs_convert_fat12_entry(uint32_t index, uint8_t low_byte, uint8_t high_byte);
 /*!
 * @brief <get the next cluster of a file/folder>
 *
 * @param index [input] <fat entry index needs to read>.
 *
 * @return <value of the current fat entry (or the next cluster of the file)>.
 */
uint16_t fatfs_get_next_cluster(uint32_t index);
   /*!
 * @brief <Read data of each directory entry (32 bytes) in the cluster>
 *
 * @param index [input] <entry index need to read>.
 *
 * @param start_sector [input] <the start sector of directory>.
 *
 * @param entry_buff [output] <save the data of the current entry (file name, file size, start cluster>.
 *
 * @return <OK if the entry is read successfully, NOT_OK if it has errors>.
 */
uint16_t fatfs_read_dir_entry(uint16_t start_sector, dir_entry entry_buff[]);
 /*!
 * @brief <show content of a file>
 *
 * @param startcluster [input] <the starting cluster of the file>.
 *
 * @return <no return>.
 */
void fatfs_show_file(uint16_t start_cluster);
 /*!
 * @brief <show content of a folder starting at the "start sector">
 *
 * @param start_sector [input] <the starting sector>.
 *
 * @param cluster_index [output] <save index of the starting cluster of files/folders>.
 *
 * @param folder_recognize [output] <save index of the children folder>.
 *
 * @return <the number of files in the current folder>.
 */
uint16_t fatfs_show_folder(uint16_t start_sector, uint16_t cluster_index[], uint16_t folder_recognize[]);
 /*!
 * @brief <processing fat file system and print out content of the disk>
 *
 * @return <no return>.
 */
void fatfs_processing (void);
#endif
