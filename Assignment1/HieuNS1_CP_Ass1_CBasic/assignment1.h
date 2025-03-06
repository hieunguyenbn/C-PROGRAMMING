#ifndef _ASSIGNMENT1_H_
#define _ASSIGNMENT1_H_

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define NMAX 20
/*******************************************************************************
 * API
 ******************************************************************************/
/*!
 * @brief <for inputting and simultaneously calculating sum of array's elements>
 *
 * @param arr <array user input>.
 *
 * @param n <the number of elements in array>.
 *
 * @return <no return>.
 */
void Input(int arr[NMAX], int n);
/*!
 * @brief <calculating average value of array's elements and counting the number of elements that are less than the average>
 *
 * @param arr <array user input>.
 *
 * @param n <the number of elements in array>.
 *
 * @return <no return>.
 */
char Average(int arr[NMAX], int n);
/*!
 * @brief <sort and print out elements of array even number and odd>
 *
 * @param arr <array users input>.
 *
 * @return <no return>.
 */
void OddEvenArray(int arr[NMAX], int n);
/*!
 * @brief <Print out all elements of array>
 *
 * @param arr <array users input>.
 *
 * @return <no return>.
 */
void Output(int arr[NMAX], int n);
#endif
