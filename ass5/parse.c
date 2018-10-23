#include <stdio.h>
#include <string.h>
#include "parse.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
 #define countByte 2
 #define startAddress 4
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

parse_status_t parseData(uint8_t pInput[], parse_data_struct_t *pOutput)
{
    uint8_t i = 0; /*increment*/
    uint8_t j = 0; /*increment*/
    uint8_t countValue = 0; /*saving value of the "count" section in srec line*/
    uint8_t typeValue = 0; /*value of the second character in "type" section*/
    uint8_t addressByteNumber = 0; /*number of bytes in the address section*/
    uint8_t finalIndexAddress = 0; /*save final position of the address value*/
    uint32_t addressValue = 0; /*Value of address (max is 4 bytes)*/
    uint8_t dataSrecLength = 0; /*saving the length of data section*/
    uint8_t sum = 0; /*save sum of bytes from "count" to "data" section*/
    uint8_t checksum = 0; /*value of checksum section in the srec line*/
    uint8_t srecLineLength = 0; /*srec line's length*/
    parse_status_t status; /*return variable, status of parsing process*/

    srecLineLength = strlen(pInput)-1;/*fgets function return a string including
                                        "\n", so string's length = strlen()-1*/

    /*Check the first, second characters and srecline's length*/

    if((pInput[0] != 'S') || (pInput[1] < '0') ||
       (pInput[1]>'9')||(srecLineLength%2!=0))
    {
        status = e_parseStatus_error;
    }

    typeValue = Hex_to_Dec(pInput[1]); /*type Value, from 0 to 9 except 4*/

    switch (typeValue) /*check type of srec line*/
    {
        case 0:
            status = e_parseStatus_start; /*Start - When parsing S0 line*/
            addressByteNumber = 2;
            /*check the address section value*/
            for (i = startAddress; i < startAddress+2*addressByteNumber; i++)
            {
                if (pInput[i] != '0')/*the address value of S0 type must be 0*/
                {
                    status = e_parseStatus_error;
                    break;
                }
            }
            break;
        case 1:
        case 2:
        case 3:
             addressByteNumber = typeValue + 1;
             status = e_parseStatus_inprogress;
             break;
        case 5:
             addressByteNumber = 2;
             status = e_parseStatus_inprogress;
             break; 
        case 6:
             addressByteNumber = 3; 
             status = e_parseStatus_inprogress;
             break;
        case 7:
        case 8:
        case 9:
             addressByteNumber = 11 - typeValue;
             status = e_parseStatus_done;
             break;
        default:
             status = e_parseStatus_error;
    }

    /*ADDRESS VALUE SAVING PROCESS*/

    /*save final index of address value*/
    finalIndexAddress = startAddress+2*addressByteNumber-1;
    /*calculate address value*/
    for (i = startAddress; i <= finalIndexAddress; i++)
    {
        addressValue = addressValue*16 + Hex_to_Dec(pInput[i]);
    }
    pOutput->address = addressValue;/*save to pOutput struct*/

    /*CHECKSUM CALCULATION AND CHECK*/
    
    /*convert each hex digit pair to a decimal number and save to "sum"*/
    for (i = countByte; i <= srecLineLength - 3; i += 2)
    {
        sum += 16*Hex_to_Dec(pInput[i]) + Hex_to_Dec(pInput[i+1]);
    }
    
    /*compute checksum value (final hex digit pair)*/
    checksum = 16*Hex_to_Dec(pInput[srecLineLength-2]) + 
               Hex_to_Dec(pInput[srecLineLength-1]);

    if (sum + checksum != 255)/*checksum value must be ones' complement of sum*/
    {
        status = e_parseStatus_error;
    }

    /*DATA SAVING PROCESS*/
    
    /*Data field is only valid in S0, S1, S2, S3 types*/
    if (typeValue == 0 || typeValue == 1 || typeValue == 2 || typeValue == 3)
    {
        /* convert hex digit pair of count section to a decimal number*/
        countValue = 16*Hex_to_Dec(pInput[2]) + Hex_to_Dec(pInput[3]);
        
        if (countValue > 0xFF)/*the Count Byte value can't be higher than 255*/
        {
            status = e_parseStatus_error;
        }
        
        dataSrecLength = countValue - addressByteNumber - 1; /*data's length*/
        pOutput->dataLength = dataSrecLength;/*Saving data's length to pOutput*/
        
        /*Save data to pOutput struct*/
        for (i=finalIndexAddress+1; i<=finalIndexAddress+dataSrecLength; i+=2)
        {
            pOutput->data[j++]=16*Hex_to_Dec(pInput[i])+Hex_to_Dec(pInput[i+1]);
        }

    }

    return status;
}

/*Convert a hex character to a decimal number*/
uint8_t Hex_to_Dec(uint8_t hexChar)
{
    uint8_t returnVal = 0; /*save value after convert*/

    if ('0' <= hexChar && hexChar <= '9')
    {
        returnVal = hexChar -'0';
    }
    if ('A' <= hexChar && hexChar <= 'F')
    {
        returnVal =  hexChar -'A'+ 10;
    }

    return returnVal;
}

