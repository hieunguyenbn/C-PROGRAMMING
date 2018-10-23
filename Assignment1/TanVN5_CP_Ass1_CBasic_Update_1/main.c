#include "assign1.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
int main() {
    /*Nhap so luong phan tu cua mang*/
    char soLuong;
    int * mangSN;
    int tong;
    char i = 0;
    while(1)
    {
        printf("Nhap so luong phan tu cua mang: ");
        scanf("%d", &soLuong);
        if(soLuong > 0 && soLuong < 20)
        {
            break;
        }
        else
        {
            printf("So luong phan tu khong thoa man yeu cau de bai\n");
        }
    }
    mangSN = nhapSo(soLuong);
    tong = tinhTong(mangSN, soLuong);
    tinhTBvaSoNhoHonTB(tong, mangSN, soLuong);
    sapXepMang(mangSN, soLuong);
    return 0;
}

