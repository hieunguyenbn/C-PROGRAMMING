#include <stdio.h>
#include <stdint.h>
#include "intArr.h"

/*!
 * @brief Enter number of elements of the array
 *
 * @return Number of elements of the array
 */
uint8_t nElement(void)
{
    float n;
    uint8_t check;
    do
    {
        printf("Enter number of elements (unsigned integer less than 21): ");
        fflush(stdin);
        check = scanf("%f", &n);
        if (check == 0 || n != (uint8_t)n || n > 20)
        {
            printf(" The value inputs are not valid, please re-enter new input\n");
            check = 0;
        }
    }
    while (check == 0);
    return (uint8_t)n;
}

/*!
 * @brief Enter elements of the array
 *
 * @param [out] pArr Pointer of the array
 * @param [inp] nElement Number of elements of the array
 *
 * @return void
 */
void enter(int32_t *pArr, uint8_t nElement)
{
    uint8_t i;
    printf("\n Enter %d elements of the array: \n", nElement);
    for (i = 0; i < nElement; i++)
    {
        printf("Arr[%d]= ", i);
        scanf("%d", pArr+i);
    }
}

/*!
 * @brief Display elements of the array
 *
 * @param [inp] pArr Pointer of the array
 * @param [inp] nElement Number of elements of the array
 *
 * @return void
 */
void disp(int32_t *pArr, uint8_t nElement)
{
    uint8_t i;
    printf("\n %d elements of array Arr: \n", nElement);
    for (i = 0; i < nElement; i++)
    {
        printf("%12d ", *(pArr+i));
        if ((i + 1) % 5 == 0)
        {
            printf("\n");
        }
    }
}

/*!
 * @brief Calculate average of elements of the array
 *
 * @param [inp] pArr Pointer of the array
 * @param [inp] nElement Number of elements of the array
 *
 * @return Average of elements of the array
 */
float avgArr(int32_t *pArr, uint8_t nElement)
{
    uint8_t i;
    float temp = 0;
    for (i = 0; i < nElement; i++)
    {
        temp = temp + *(pArr+i);
    }
    return temp/nElement;
}

/*!
 * @brief Calculate number of elements less than one compared key
 *
 * @param [inp] keyComp Compared key
 * @param [inp] pArr Pointer of the array
 * @param [inp] nElement Number of elements of the array
 *
 * @return Number of elements less than the compared key
 */
uint8_t nLess(float keyComp, int32_t *pArr, uint8_t nElement)
{
    uint8_t i;
    uint8_t temp = 0;
    for (i = 0; i < nElement; i++)
    {
        if (*(pArr+i) < keyComp)
        {
            temp++;
        }
    }
    return temp;
}

/*!
 * @brief Arrange the array follow the rule: Odd elements are in the left of even elements
 *
 * @param [inp] pArr Pointer of the array
 * @param [inp] nElement Number of elements of the array
 *
 * @return void
 */
void arrOddEven(int32_t *pArr, uint8_t nElement)
{
    uint8_t i;
    uint8_t j;
    int32_t temp;
    i = 0;
    j = nElement;
    while (i < j)
    {
        while (*(pArr+i) % 2 != 0 && i < j)
        {
            i++;
        }
        while (*(pArr+j) % 2 == 0 && i < j)
        {
            j--;
        }
        if (i < j)
        {
            temp = *(pArr+i);
            *(pArr+i) = *(pArr+j);
            *(pArr+j) = temp;
        }
        i++;
        j--;
    }
}
