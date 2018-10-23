#ifndef _PARSE_H_
#define _PARSE_H_
#include <stdint.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MAX_LINE_DATA_SIZE   510

typedef enum {

    e_parseStatus_done = 0x00U,
    e_parseStatus_start = 0x01U,
    e_parseStatus_inprogress = 0x02U,
    e_parseStatus_error = 0xFFU,

} parse_status_t;

typedef struct {

    uint32_t address;
    uint8_t data[MAX_LINE_DATA_SIZE];
    uint8_t dataLength;

} parse_data_struct_t;

/*******************************************************************************
 * API
 ******************************************************************************/
  /*!
 * @brief <Parsing a line of srec file>
 *
 * @param pInput[] [input] <srec line>.
 *
 * @param pOutput [output] <output of parsed data>.
 *
 * @return <Return: Start - When parsing S0 line;
 * Inprogress - when parsing S1 or 2,3,5 or 6 line;
 * Done - when parsing S7 or 8, 9 line Error - When error>.
 */
parse_status_t parseData(uint8_t pInput[], parse_data_struct_t *pOutput);
 /*!
 * @brief <Convert a hex character to a decimal number (use ACII table)>
 *
 * @param hexChar [in] <a hex digit>.
 *
 * @return <an integer value in decimal system>.
 */
uint8_t Hex_to_Dec(uint8_t hexChar);

#endif
