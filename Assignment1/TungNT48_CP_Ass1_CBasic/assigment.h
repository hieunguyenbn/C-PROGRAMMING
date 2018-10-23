#ifndef assigment.h
#define assigment.h

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define MAX 20

/*******************************************************************************
 * API
 ******************************************************************************/
/*!
 * @brief Lay gia tri nguoi dung nhap vao
 * @param arr mang gia tri da duoc khoi tao voi mot size nao do chua co phan tu nao
 * @param n so phan tu cua mang duoc phep nhap vao
 * @return void
 */
void input (int a[] , int n);


/*!
*@brief In ra gia tri ma nguoi dung da nhap vao
*@param arr mang gia tri da duoc khoi tao voi cac gia tri cu the
*@param n so phan tu cua mang
*@return void
*/
void output(int a[MAX],int n);

/*!
 *@brief Doi vi tri 2 phan tu trong mang
 *@param eL1 phan tu thu  i cua mang
 *@param eL2 phan tu thu 2 khac i cua mang
 *@return void
 */
void swapEleament(int  *eL1, int * eL2);

/*!
 *@brief Tinh gia tri trung binh cua cac gia tri da nhap
 *@param arr mang gia tri da duoc khoi tao voi cac gia tri cu the
 *@param n so phan tu cua mang
 *@return float
 */
float avgArr(int a[MAX],int n);


/*!
 *@brief Sap xep chan le ve hai dau mang cho cac phan tu
 *@param arr Mang gia tri nguoi dung da nhap
 *@return void
 */
 
void arrangeArr(int arr[MAX],int n);

/*!
 *@brief In ra so gia tri ma nho hon gia tri trung binh cua mang
 *@param arr mang gia tri da duoc khoi tao voi cac gia tri cu the
 *@param n so phan tu cua mang
 *@return int 
 */
int smallvsAvg(int arr[MAX],int n);

#endif /* _HEADER_FILENAME_H_ */
