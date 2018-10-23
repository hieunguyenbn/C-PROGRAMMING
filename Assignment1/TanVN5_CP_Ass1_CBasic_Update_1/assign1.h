#ifndef _ASSIGN1_H_
#define _ASSIGN1_H_
#include <stdio.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * API
 ******************************************************************************/
/*!
 * @brief Nhap so vao mang so nguyen
 *
 * @param soLuong so luong phan tu co trong mang
 * 
 * @return tra ve mang so nguyen
 */
int * nhapSo(int soLuong);

/*!
 * @brief Tinh tong cua mang so nguyen
 *
 * @param mangSN mang so nguyen can tinh tong
 * @param soLuong so luong phan tu co trong mang
 * 
 * @return tong cua mang so nguyen
 */
int tinhTong(int * mangSN, int soLuong);

/*!
 * @brief Tinh gia tri trung binh va so luong so nho hon gia tri trung binh
 *
 * @param tong tong cua mang so nguyen
 * @param soLuong so luong phan tu co trong mang
 * @param mangSN mang so nguyen
 * 
 */
void tinhTBvaSoNhoHonTB(int tong, int * mangSN, int soLuong);

/*!
 * @brief Sap xep mang so nguyen so le ve ben trai va so chan ve ben phai
 *
 * @param mangSN mang so nguyen can sap xep
 * @param soLuong so luong phan tu co trong mang
 * 
 */
void sapXepMang(int * mangSN, int soLuong);

#endif /* _ASSIGN1_H_ */

