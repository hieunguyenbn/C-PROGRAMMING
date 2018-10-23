#include <stdio.h>
#include <string.h>
#include "parse.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
 #define MAX_SREC_LINE_LENGTH  0xFF
 #define FIRST_LINE_ERROR      0x01
 #define OPTIONAL_TYPE_ERROR   0x02
 #define FINAL_SREC_LINE_ERROR 0x03
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
 static void LineParser(uint8_t pLine[]);
 static void FileParser(FILE *file);
/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

int main()
{
    FILE *fileSrec;
    fileSrec = fopen("filehandling.srec","r"); /*open the srec file*/

    if (!fileSrec) /*check if it is not able to open the file*/
    {
        printf("\nCannot open this file!\n");
    }

    FileParser(fileSrec);

    fclose(fileSrec);
    return 0;
}

static void FileParser(FILE *file) /*parsing srec file*/
{

    uint8_t i = 1; /*increment to show the number of line*/
    uint8_t j = 0; /*increment*/
    uint8_t srecLine[MAX_SREC_LINE_LENGTH]; /*save srec line's characters*/  
    static parse_data_struct_t pInfo; /*print out data of srec line*/
    parse_status_t LineStatus; /*get status of parsing process*/
    uint8_t countType = 0; /*number of types (max is 9 (0 to 9 except 4))*/
    uint8_t type = 0; /*save type of the reading srec line*/
    uint8_t secondRegion_Type = 0; /*type of the second srec lines region*/
    uint8_t error = 0; /*getting error to identify style of srec file*/

    while (!feof(file))  /*START READING AND PARSING*/
    {
       /*get characters of line from the stream "file", save to "srecLine"*/
       fgets(srecLine,MAX_SREC_LINE_LENGTH,file);
       
       if (feof(file))
       {
            break; /*break out of the loop when get the end of file value-EOF*/
       }
        /*CHECKING ERRORS ON SREC STYLES*/
       /*srec structure: S0 -> S1/2/3 -> S5/S6(Optional) -> S9/8/7)*/
       if (i == 1 && Hex_to_Dec(srecLine[1]) != 0)
       {
           error = FIRST_LINE_ERROR;/*the first line must be S0*/
       }

       if (i == 2)/*the second type -  the first type (the first must 0)*/
       {
           secondRegion_Type = Hex_to_Dec(srecLine[1]) - type;
       }
       /*if changes in type or type of first line is 0*/
       if (type != Hex_to_Dec(srecLine[1]) || Hex_to_Dec(srecLine[1]) == 0)
       {
           countType++; /*increase number of types*/
       }
       
       type = Hex_to_Dec(srecLine[1]); /*Save type of srecline */
       
       if ((countType == 3 && type < 5) || (countType == 3 && type > 6))
       {
           error = OPTIONAL_TYPE_ERROR; /*the third type must be S5/S6*/
       }

       /*START PRINT OUT THE LINE AND IT'S INFOMATION*/
       printf("================================================================================");
       printf("\nLine %d: %s\n", i++, srecLine); /*print the srec line*/

       LineStatus = parseData(srecLine,&pInfo);

       if (LineStatus != e_parseStatus_error) /*if the parsing process is OK*/
       {
           LineParser(srecLine);
           printf("Address: %d in DEC or 0x%x in HEX\n", pInfo.address, pInfo.address);
           if (LineStatus == e_parseStatus_start) /*start parsing*/
           {
               printf("Data: ");
               for (j = 0; j < pInfo.dataLength; j++)
               {
                    printf(" %d", pInfo.data[j]);
               }
               printf("\nStatus: START\n");
           }
           else if (LineStatus == e_parseStatus_inprogress) /*in parsing progress*/
           {
               if (type == 5)
               {
                    printf("This optional record contains a 16-bit count of S1/S2/S3 records\n");
               }
               if (type == 6)
               {
                    printf("This optional record contains a 24-bit count of S1/S2/S3 records\n");
               }
               printf("Data: ");
               for (j = 0; j < pInfo.dataLength; j++)
               {
                    printf(" %d", pInfo.data[j]);
               }
               printf("\nStatus: IN PROGRESS\n");
           }
           else if (LineStatus == e_parseStatus_done) /*finish parsing progress*/
           {
               printf("Status: DONE\n");
           }

       }
       else /*If the parsing progess is not OK*/
       {

           if (type == 4) /*S4 is not available !*/
           {
               printf("THIS RECORD IS REVERSED\n");
           }
           else
           {
               printf("THIS LINE HAS ERROR !\n");
               error = e_parseStatus_error;
           }
       }
    }
    /*STYLE OF SREC FILE*/
    /*check type of final srec line (after breaking out of the while loop)*/
    if (type != 9 && type != 8 && type != 7)
    {
        error = FINAL_SREC_LINE_ERROR;
    }

    printf("\n========================IDENTIFY SREC RECORD STYLE==============================\n");
    printf("\n============================SUPPORT ALL STYLES==================================\n");

    /*srec structure: S0 -> S1/2/3 -> S5/S6(Optional) -> S9/8/7)*/
    if (error == 0 && countType <= 4)/*If no error and the number of types <= 4*/
    {
        /*Check the final and second type of srec file to define it's style*/
        if (type == 9 && secondRegion_Type == 1)
        {
            printf("\nOK! This is S19 style record!\n");
        }
        else if (type == 8 && secondRegion_Type == 2)
        {
            printf("\nOK! This is S28 style record!\n");
        }
        else if (type == 7 && secondRegion_Type == 3)
        {
            printf("\nOK! This is S37 style record!\n");
        }
        else
        {
            printf("\nERROR, CANNOT DEFINE STYLE !\nThe start line must be S0\nThe third type must be S5/6\n");
            printf("The final line must be S7/8/9 and the second region must be S3/2/1 respectively\n");
        }
    }
    else
    {
         printf("\nCANNOT DEFINE STYLE because ERROR OCCUR!\n");
    }
}

static void LineParser(uint8_t pLine[]) /*parsing a srec line in the file*/
{

    uint8_t i = 0; /*increment*/

    printf("Parse: ");
    printf("%c", pLine[0]); /*The first character of a srec line*/
    printf("%d ", Hex_to_Dec (pLine[1]));  /*The second character of a srec line (type)*/
    
    for (i = 2; i <= strlen(pLine)-2; i += 2)
    {   /*print out each hex digits pair in decimal number*/
        printf("%d ", 16*Hex_to_Dec(pLine[i]) + Hex_to_Dec(pLine[i+1]));
    }
    printf("\n");
}

