#ifdef _INT_ARRAY_H_
#define _INT_ARRAY_H_

#include <stdint.h>

/*******************************************************************************
 * Library for 
 * Enter number of elements, elements of array
 * Display elements of array, 
 * Calculate average of elements,
 * Calculate number of elements lower than average
 * Arrange the array follow the rule: Odd elements are in the left of even elements
 ******************************************************************************/
 
/******************************************************************************* 
 * API
 ******************************************************************************/
/*!
 * @brief Enter number of elements of the array
 *
 * @return Number of elements of the array
 */
uint8_t nElement(void);

/*!
 * @brief Enter elements of the array
 *
 * @param [out] pArr Pointer of the array
 * @param [inp] nElement Number of elements of the array
 *
 * @return void
 */
void enter(int32_t *pArr, uint8_t nElement);

/*!
 * @brief Display elements of the array
 *
 * @param [inp] pArr Pointer of the array
 * @param [inp] nElement Number of elements of the array
 *
 * @return void
 */
void disp(int32_t *pArr, uint8_t nElement);

/*!
 * @brief Calculate average of elements of the array
 *
 * @param [inp] pArr Pointer of the array
 * @param [inp] nElement Number of elements of the array
 *
 * @return Average of elements of the array
 */
float avgArr(int32_t *pArr, uint8_t nElement);

/*!
 * @brief Calculate number of elements less than one compared key
 *
 * @param [inp] keyComp Compared key
 * @param [inp] pArr Pointer of the array
 * @param [inp] nElement Number of elements of the array
 *
 * @return Number of elements less than the compared key
 */
uint8_t nLess(float keyComp, int32_t *pArr, uint8_t nElement);

/*!
 * @brief Arrange the array follow the rule: Odd elements are in the left of even elements
 *
 * @param [inp] pArr Pointer of the array
 * @param [inp] nElement Number of elements of the array
 *
 * @return void
 */
void arrOddEven(int32_t *pArr, uint8_t Element);

#endif /* _INT_ARRAY_H_*/
