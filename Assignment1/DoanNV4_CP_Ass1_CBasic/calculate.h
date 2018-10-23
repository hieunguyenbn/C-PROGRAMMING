#ifndef _HEADER_CALCULATE_H_
#define _HEADER_CALCULATE_H_

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MAX 20 /*max element of array*/
/*******************************************************************************
 * API
 ******************************************************************************/
/*!
 * @brief :input array from user.
 *
 * @param arr: array need input
 *
 * @param element: element user enter.
 *
 * @return: void.
 */
void inputArr(int arr[], int element);
/*!
 * @brief :return medium of array input.
 *
 * @param arr: array user input
 *
 * @param element: element user enter.
 *
 * @return: return medium type float.
 */
float functionMedium(int arr[], int element);
/*!
 * @brief: find number of elements less medium.
 *
 * @param arr: array user input .
 *
 * @param element: element user enter.
 *
 * @return: return number of elements less medium type int.
 */
int lessgMedium(int arr[], int medium, int element);
/*!
 * @brief: sort and print elements of array even number and odd.
 *
 * @param arr: array user input.
 *
 * @return: void.
 */
void parityArrangement(int arr[], int element);
/*!
 * @brief :print array after sort.
 *
 * @param arr: array after sort.
 *
 * @param element: element user enter.
 *
 * @return: void.
 */
void printfArr(int arr[], int element);

#endif /* _HEADER_CALCULATE_H_ */
