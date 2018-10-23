#ifndef _HANDLEHUYNQ51_H_
#define _HANDLEHUYNQ51_H_

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#ifndef SIZE_MAX
    #define SIZE_MAX          20
#endif /* SIZE_MAX */

/*******************************************************************************
 * API
 ******************************************************************************/
/*!
 * @brief Enter number to array
 *
 * @param [in] *arrIn: Address of array which need to process
 * @param [in] *sizeArrIn: Address of sizeArrIn, it is size of array
 * @param [out] *arrIn: Array is entered by user
 * @param [out] *sizeArrIn: Size of arrway is enter by user
 *
 * @return nothing
 */
void enterInput(int *arrIn, unsigned char *sizeArrIn);

/*!
 * @brief Commute sum of array
 *
 * @param [in] *arrIn: Address of array which need to process
 * @param [in] sizeArrIn: Size of arrway
 *
 * @return sum of array
 */
int sumArr(int *arrIn, unsigned char sizeArrIn);

/*!
 * @brief Commute average of array
 *
 * @param [in] sumArr: Sum of arrway
 * @param [in] sizeArrIn: Size of arrway
 *
 * @return average of array
 */
float averageArr(int sumArr, unsigned char sizeArrIn);

/*!
 * @brief Find amount of number which is smaller than average value of array
 *
 * @param [in] *arrIn: Address of array which need to process
 * @param [in] sizeArrIn: Size of arrway
 * @param [in] averArrIn: Average of arrway
 *
 * @return amount of number which is smaller than average value of array
 */
int nbSmallerAverage(int *arrIn, unsigned char sizeArrIn, float averArrIn);

/*!
 * @brief Arrange array: Even number - right, Odd number - left
 *
 * @param [in] *arrIn: Address of array which need to process
 * @param [in] sizeArrIn: Size of arrway
 *
 * @return nothing
 */
void arrangeEvenOdd(int *arrIn, unsigned char sizeArrIn);

/*!
 * @brief Show array
 *
 * @param [in] *arrIn: Address of array which need to process
 * @param [in] sizeArrIn: Size of arrway
 *
 * @return nothing
 */
void showArr(int *arrIn, unsigned char sizeArrIn);

#endif /* _HANDLEHUYNQ51_H_ */
