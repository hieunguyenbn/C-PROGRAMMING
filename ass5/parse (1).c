#include <stdio.h>
#include <string.h>
#include "parse.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
 #define ERROR              0xFF
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
    uint8_t i = 0; /*increment, starting at the first character of srec line*/
    uint8_t j = 0; /*increment*/
    uint8_t countValue = 0; /*saving value of the "count" section in srec line*/
    uint8_t typeValue = 0; /*value of the second character in "type" section*/
    uint8_t addressByteNumber = 0; /*number of bytes in the address section*/
    uint8_t addressFinalIndex = 0; /*save final byte position of the address section*/
    uint32_t addressValue = 0; /*Value of address (max is 4 bytes)*/
    uint8_t dataSrecLength = 0; /*saving the length of data section*/
    uint8_t bytes_sum = 0; /*save sum of bytes from "count" to "data" section to check the "checksum" value */
    uint8_t checksum = 0; /*value of checksum section in the srec line*/
    uint8_t srecLineLength = 0; /*srec line's length*/
    parse_status_t status; /*return variable, status of parsing process*/

    /*Check the first character and srecline's length*/

    if(pInput[i++] != 'S')
    {
        status = e_parseStatus_error;
    }

    typeValue = Hex_to_Dec(pInput[i++]); /*type Value, from 0 to 9 except 4*/

    switch (typeValue) /*check type of srec line*/
    {
        case 0:
            status = e_parseStatus_start; /*Start - When parsing S0 line*/
            addressByteNumber = 2;
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
    /*  Calculating value of count section in srec line */ 
    countValue = Hex_to_Dec(pInput[i++])<<4 | Hex_to_Dec(pInput[i++]);/*convert hex digit pair of count section to a decimal number*/
    bytes_sum += countValue; /* save value of this digit pair */
    /* Calculating line's length */
    srecLineLength = i + 2*countValue; /* length =  First two bytes (S-record type) + two count byte section + value of count byte section */

    /*check srec line's length by comparing values calculated from count byte section and from the C function strlen*/
    if (srecLineLength != (strlen((char *)pInput) - 1))
    {
        status = e_parseStatus_error;
    }
    else
    {
        /*save final index of address value*/
        addressFinalIndex = i+2*addressByteNumber-1;

        while (i <= addressFinalIndex)
        {
            addressValue = addressValue<<4 | Hex_to_Dec(pInput[i]); /* shift left in byte */
            if (!(i % 2))
            {
                bytes_sum += Hex_to_Dec(pInput[i])<<4 | Hex_to_Dec(pInput[i+1]); /* save value of each digit pair in address section*/
            }
            i++;
        }
        if ((typeValue == 0) && (addressValue != 0))
        {
            /*the address value of S0 type must be 0*/
            status = e_parseStatus_error;
        }
        else
        {
            pOutput->address = addressValue;/*save to pOutput struct*/

            if (typeValue == 0 || typeValue == 1 || typeValue == 2 || typeValue == 3) /*Data field is only valid in S0, S1, S2, S3 types*/
            {
                dataSrecLength = countValue - addressByteNumber - 1; /*data's length*/
                pOutput->dataLength = dataSrecLength;/*Saving data's length to pOutput*/
                /*Save data to pOutput struct*/

                while (i <= (srecLineLength - 3)) /* final data section index = line's length - 3 (two final bytes is checksum) */
                {
                    pOutput->data[j] = Hex_to_Dec(pInput[i])<<4 | Hex_to_Dec(pInput[i+1]);
                    bytes_sum += pOutput->data[j];/* save value of each digit pair in data section*/
                    i += 2;
                    j++;
                }
            }
            /*compute checksum value (final hex digit pair)*/
            checksum = Hex_to_Dec(pInput[srecLineLength-2])<<4 | Hex_to_Dec(pInput[srecLineLength-1]);
            if (bytes_sum + checksum != 0xFF)/*checksum value must be ones' complement of sum*/
            {
                status = e_parseStatus_error;
            }
        }
    }

    return status;
}

/*Convert a hex character to a decimal number*/
uint8_t Hex_to_Dec(uint8_t hexChar)
{
    uint8_t returnVal; /*save value after convert*/

    if ('0' <= hexChar && hexChar <= '9')
    {
        returnVal = hexChar -'0';
    }
    else if ('A' <= hexChar && hexChar <= 'F')
    { 
        returnVal =  hexChar -'A'+ 10;
    }
    else
    {
        returnVal = ERROR;
    }
    return returnVal;
}

