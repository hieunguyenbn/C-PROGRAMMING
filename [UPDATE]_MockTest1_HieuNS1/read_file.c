#include "read_file.h"
#include "HAL.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define INPROCESS            1
#define MAX_CLUSTER_FAT12 2850
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void check_audio(uint8_t *buff);
/*******************************************************************************
 * Variables
 ******************************************************************************/
static fat_boot_sector g_boot_sector;
/*******************************************************************************
 * Code
 ******************************************************************************/
uint16_t fatfs_convert_fat12_entry(uint32_t index, uint8_t low_byte, uint8_t high_byte)
{
    uint16_t returnval = 0; /*return value*/

    if (index % 2 == 0) /*even fat entry element*/
    {
        returnval = (high_byte & 0x0F)<<8;
        returnval |= low_byte;
    }
    else /*odd fat entry element*/
    {
        returnval = high_byte;
        returnval = (returnval << 4) | (low_byte >> 4);
    }
        return returnval;
}

uint16_t fatfs_get_next_cluster(uint32_t index)
{
    uint16_t next_cluster = 0; /*return value*/
    uint16_t sector_index = 0; /*the sector index of the fat entry need to read*/
    uint32_t byte_position = 0; /*starting byte of fat entry index*/
    uint8_t buff[g_boot_sector.bytes_per_sector]; /*save data*/
    uint16_t first_byte_index = 0; /*index of first bte of the fat entry*/
    uint8_t first_byte_val = 0; /*save value of first byte of the fat entry*/
    uint8_t second_byte_val = 0; /*save value of second byte of the fat entry*/

    byte_position = index*FAT12_ENTRY_SIZE;
    
    first_byte_index = byte_position%g_boot_sector.bytes_per_sector;
    sector_index = byte_position/g_boot_sector.bytes_per_sector+g_boot_sector.reserved_sector_count;
    
    kmc_read_sector(sector_index,buff); /*read the sector index*/
    first_byte_val = buff[first_byte_index];

    if (first_byte_index < g_boot_sector.bytes_per_sector-1) /*the starting byte of fat entry index is not the final byte of current sector*/
    {
        second_byte_val = buff[first_byte_index+1];
    }
    else
    {
        kmc_read_sector(sector_index+1,buff); /*read the next sector*/
        second_byte_val = buff[0];
    }

    next_cluster = fatfs_convert_fat12_entry(index, first_byte_val, second_byte_val);
    return next_cluster;
}

uint16_t fatfs_read_dir_entry(uint16_t start_sector, dir_entry entry_buff[])
{
    uint8_t j = 0; /*increment*/
    uint16_t entry_index = 0; /*index of each entry, also the return value*/
    uint16_t i = 0; /*offset of each entry*/
    uint8_t buff[g_boot_sector.bytes_per_sector*g_boot_sector.sectors_per_cluster]; /*save data of the read sector*/
    uint32_t file_size = 0; /*save file size value*/
    uint16_t start_cluster = 0; /*save starting cluster of file*/
    
    if (g_boot_sector.sectors_per_cluster == 1)/*sector size = cluster size*/
    {
        kmc_read_sector(start_sector,buff);
    }
    else /*cluster size = n*sector size (n = g_boot_sector.sectors_per_cluster) */
    {
        kmc_read_multi_sector(start_sector,g_boot_sector.sectors_per_cluster, buff);
    }
    while (i < g_boot_sector.bytes_per_sector*g_boot_sector.sectors_per_cluster)
    {
    /* Directory entry structure
       if filename[0] == 0xe5, this is a free dir entry
       if filename[0] == 0x00, this is a free entry and all subsequent entries are free
       if the attribute value = 0x0F => it's a long file name*/
        if (buff[i] != DIR_ENTRY_FREE && buff[i] != DIR_ENTRY_DELETED && buff[i+ATTRIBUTE_INDEX] != ATTR_LFN)
        {
            for (j = 0; j < ATTRIBUTE_INDEX; j++)
            {
                 entry_buff[entry_index].file_name[j] = buff[i+j]; /*save file name*/
            }
            for (j = DIR_ENTRY_SIZE-1; j >= FILE_SIZE_INDEX; j--)
            {
                file_size = file_size<<8 | buff[i+j]; /*save size of file*/
            }
            start_cluster = buff[i+FILE_SIZE_INDEX-1];
            start_cluster = (start_cluster<<8) | buff[i+FILE_SIZE_INDEX-2];
            
            entry_buff[entry_index].start_cluster = start_cluster;
            entry_buff[entry_index].file_size = file_size;
            entry_buff[entry_index].attribute = buff[i+ATTRIBUTE_INDEX]; /*the file attribute*/
            entry_index++;
        }
        i += DIR_ENTRY_SIZE; /*go to the next entry*/
    }
    return entry_index;
}

static void check_audio(uint8_t *buff)/*check whether each byte in the cluster of file is the audible bell character*/
{
    uint16_t i = 0; /*increment*/
    for (i = 0; i < g_boot_sector.bytes_per_sector*g_boot_sector.sectors_per_cluster; i++)
    {
        if (buff[i] == BELL)
        {
            buff[i] = '0';
        }
    }
}

void fatfs_show_file(uint16_t start_cluster)
{
    uint16_t i = 0; /*increment*/
    uint8_t buff[g_boot_sector.bytes_per_sector*g_boot_sector.sectors_per_cluster];
    uint16_t start_sector = 0;
    uint16_t next_cluster = 0;
    uint16_t root_start_sector = 0;
    uint16_t data_start_sector = 0; 

    root_start_sector = g_boot_sector.reserved_sector_count+g_boot_sector.sectors_per_fat*g_boot_sector.fat_count;
    data_start_sector = root_start_sector + g_boot_sector.max_root_entries*DIR_ENTRY_SIZE/g_boot_sector.bytes_per_sector;
    
    next_cluster = start_cluster;
    /*reading and print out file content until the next cluster is the ending value (0XFF8) and ignore if it is a bad cluster*/
    while (next_cluster < END_CLUSTER)
    {
        if (next_cluster != BAD_CLUSTER)
        {
            start_sector = data_start_sector + (next_cluster - FIRST_LOGIC_CLUSTER)/g_boot_sector.sectors_per_cluster; /*the start data field is at sector 33 and the logical start cluster is 2*/
            
            if (g_boot_sector.sectors_per_cluster == 1)/*sector size = cluster size*/
            {
                kmc_read_sector(start_sector,buff); /*read sector, save to buff*/
            }
            else /*cluster size = n*sector size (n = g_boot_sector.sectors_per_cluster) */
            {
                kmc_read_multi_sector(start_sector,g_boot_sector.sectors_per_cluster, buff); /*read n sectors*/
            }
            check_audio(buff); /*check audio character*/
            
            for (i = 0; i < g_boot_sector.bytes_per_sector*g_boot_sector.sectors_per_cluster; i++)
            {
                printf("%c", buff[i]); /*print out content*/
            }
        }
        next_cluster = fatfs_get_next_cluster(next_cluster); /*get the next cluster of the file*/
    }
}

uint16_t fatfs_show_folder(uint16_t start_sector, uint16_t cluster_index[], uint16_t folder_recognize[])
{
    uint16_t i = 0; /*increment*/
    uint8_t j = 0; /*increment*/
    uint8_t status = 0; /*status of reading entries*/
    uint16_t number_of_entries = 0; /*save number of entries*/
    uint8_t entries_per_cluster = 0; /*number of entries per cluster*/
    uint16_t numbef_of_files = 0; /*number of files in the folder*/
    dir_entry entry[g_boot_sector.bytes_per_sector*g_boot_sector.sectors_per_cluster/DIR_ENTRY_SIZE]; /*array of entries in cluster*/
    uint16_t root_start_sector = 0;
    uint16_t data_start_sector = 0; 

    system("cls"); /*clear output screen*/
    
    entries_per_cluster = g_boot_sector.bytes_per_sector*g_boot_sector.sectors_per_cluster/DIR_ENTRY_SIZE;
    
    number_of_entries = fatfs_read_dir_entry(start_sector,entry);

    printf("\nFILE\t\t\t  ATTRIBUTE\t\tSTART CLUSTER\tSIZE (BYTES)\n\n");
    printf("===========================================================================\n");
    while (status == OK)
    {
        numbef_of_files += number_of_entries;
        while (i < number_of_entries)    
        {
            cluster_index[i+1] = entry[i].start_cluster; /*save the starting cluster index*/

            printf("%d. ", i+1);
            for (j = 0; j < ATTRIBUTE_INDEX; j++) /*print out file/foler name*/
            {
                printf("%c", entry[i].file_name[j]);
            }
            printf("\t\t");
            switch(entry[i].attribute) /*check attribute*/
            {
                case ATTR_READ_ONLY:
                    printf("READ ONLY\t");
                    break;
                case ATTR_HIDDEN:
                    printf("HIDDEN\t");
                    break;
                case ATTR_SYSTEM:
                    printf("SYSTEM\t");
                    break;
                case ATTR_VOLUME:
                    printf("VOLUME\t");
                    break;
                case ATTR_SUB_DIR:
                    printf("  FOLDER\t");
                    folder_recognize[i+1] = i+1; /*save the folder index*/
                    break;
                case ATTR_ARCHIVE:
                    printf("  FILE ARCHIVE\t");
                    break;
                default:
                    printf("  FILE DOCUMENT\t");
                    break;
            }
            printf("\t%d\t\t", entry[i].start_cluster); /*print out the starting cluster*/
            printf("%d\n\n", entry[i].file_size); /*print out the file'size*/
            i++;
        }
            if (number_of_entries < entries_per_cluster)
            {
                status = NOT_OK;
            }
            else /*if number of entries in the directory = max entries number of a sector*/
            {
                
                root_start_sector = g_boot_sector.reserved_sector_count+g_boot_sector.sectors_per_fat*g_boot_sector.fat_count;
                data_start_sector = root_start_sector + g_boot_sector.max_root_entries*DIR_ENTRY_SIZE/g_boot_sector.bytes_per_sector;
                entry[number_of_entries-1].start_cluster = fatfs_get_next_cluster(entry[number_of_entries-1].start_cluster);
                start_sector = data_start_sector + (entry[number_of_entries-1].start_cluster - FIRST_LOGIC_CLUSTER)/g_boot_sector.sectors_per_cluster; /*the start data field is at sector 33 and the logical start cluster is 2*/
                number_of_entries = fatfs_read_dir_entry(start_sector,entry);
                status = OK;
            }
    }
    return numbef_of_files;
}

void fatfs_processing (void) {

    uint8_t i; /*increment*/
    uint8_t input_char[1]; /*check user input*/
    uint8_t button; /*selecting button by users (choose file desired to open)*/
    uint8_t mode; /*selecting mode (open file/folder, exit) by users*/

    uint16_t start_sector = 0; /*save the starting sector of file/folder in the fat disk*/
    uint16_t root_start_sector = 0; /*save the starting sector of root directory*/
    uint16_t data_start_sector = 0; /*save the starting sector of data region*/

    uint16_t folder_recognize[MAX_CLUSTER_FAT12] = {0}; /*recognizing folder*/
    uint16_t parent_folder[MAX_CLUSTER_FAT12] = {0}; /*save the current parent folder of files/folders*/
    static uint16_t cluster_index[MAX_CLUSTER_FAT12] = {0}; /*save the starting cluster of file/folders*/

    uint8_t reading_file_status = 0; /*show that user is reading file content*/
    uint16_t number_of_files = 0; /*save the number of files in the current folder*/
    uint8_t path[12] = {0}; /*path to open files*/


    printf("Enter path to open your fat file: ");
    scanf("%s", &path);
    
    if (kmc_open_fat_disk(path) == true)
    {
        kmc_parse_boot_sector(&g_boot_sector); /*get info from boot sector region*/
        root_start_sector = g_boot_sector.reserved_sector_count + g_boot_sector.sectors_per_fat*g_boot_sector.fat_count;
        data_start_sector = root_start_sector + g_boot_sector.max_root_entries*DIR_ENTRY_SIZE/g_boot_sector.bytes_per_sector;
        while (1) {
            system("cls");
            printf("\nPRESS:\n1 TO OPEN ROOT DIRECTORY.\n0 TO EXIT\n");
            scanf("%c", &mode);
            if (mode <= '1' && mode >= '0')
            {
                break;
            }
        }

        while (mode != '0') { /*process is implemented until user enter the exit command (0)*/

            switch (mode)
            {
                case '1': /*user wants to open root directory*/
                    i = 0;
                    parent_folder[i] = root_start_sector; /*the first parent folder is always the root directory*/
                    number_of_files = fatfs_show_folder(root_start_sector,cluster_index,folder_recognize); /*show contents of root and save number of files!*/
                    reading_file_status = 0; /*user is reading folder/directory, not file content!*/
                    break;
                case '2': /*user wants to open files/folders*/

                    if (reading_file_status == INPROCESS) /*check if user is reading file content, back to the parent folder to open others*/
                    {

                        printf("\nPlease go back and choose other files!\n");
                        break;
                    }
                    do
                    {
                        printf("\nCHOOSE FILE/FOLDER YOU WANT TO OPEN (enter index): ");
                        fflush(stdin);
                        fgets(input_char, 255, stdin);
                        button = atoi(input_char);/*convert the input character to an integer number*/
                    } while (button > number_of_files || button < 1); /*button must < number of files and >= 1*/
                    
                    root_start_sector = g_boot_sector.reserved_sector_count + g_boot_sector.sectors_per_fat*g_boot_sector.fat_count;
                    data_start_sector = root_start_sector + g_boot_sector.max_root_entries*DIR_ENTRY_SIZE/g_boot_sector.bytes_per_sector;
                   
                    start_sector = data_start_sector + (cluster_index[button] - FIRST_LOGIC_CLUSTER);///g_boot_sector.sectors_per_cluster;/*the starting sector of file/folder content is*/
                    
                    parent_folder[++i] = start_sector; /*save the starting sector of this folder*/

                    if (button == folder_recognize[button]) /*check if user is opening a folder*/
                    {
                        if (cluster_index[button] == 0)
                        {
                            start_sector = root_start_sector;
                        }
                        number_of_files = fatfs_show_folder(start_sector,cluster_index,folder_recognize);
                        if (number_of_files <= 2 && cluster_index[2] == 0) /*check if the folder is empty*/
                        {
                            printf("\nThis folder is empty!\n");
                            break;
                        }
                        reading_file_status = 0;
                    }
                    else
                    {
                        fatfs_show_file(cluster_index[button]); /*showing file content*/
                        reading_file_status = INPROCESS; /*user are reading file content*/
                    }
                    break;
                case '3': /*user wants to back to the parent folder*/
                    reading_file_status = 0;
                    if (i < 1) /*check if user is reading the root, there is no parent folder of the root!*/
                    {
                        i = 1;
                    }
                    number_of_files = fatfs_show_folder(parent_folder[--i],cluster_index,folder_recognize); /*show the parent folder*/
                    break;
                default:
                    reading_file_status = 0;
                    break;
            }
            while (1) {
                printf("\n\n===========================================================================\n");
                printf("PRESS:\n1 TO OPEN ROOT DIRECTORY.\n2 TO OPEN FILE/FOLDER.\n3 TO BACK TO THE PARENT FOLDER.\n0 TO EXIT.\n");
                fflush(stdin);
                scanf("%c", &mode);
                if (mode <= '3' && mode >= '0')
                {
                    break;
                }
            }
        }
    }

    kmc_close_fat_disk();
}
