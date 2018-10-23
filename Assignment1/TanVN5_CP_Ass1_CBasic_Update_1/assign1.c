#include "assign1.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
int * nhapSo(int soLuong);
int tinhTong(int * mangSN, int soLuong);
void tinhTBvaSoNhoHonTB(int tong, int * mangSN, int soLuong);
void sapXepMang(int * mangSN, int soLuong);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
int * nhapSo(int soLuong)
{
    /*Nhap so*/
    int * mangSN;
    char i;
    printf("Nhap vao %d so nguyen\n\n", soLuong);
    for(i = 0; i < soLuong; i++)
    {
        printf("Nhap so thu %d: ", i + 1);
        scanf("%d", &mangSN[i]);
    }  
    return mangSN;
}
 
int tinhTong(int * mangSN, int soLuong)
{
    /*Tinh tong*/
    int tong = 0;
    char i;
    for(i = 0; i < soLuong; i++)
    {
        tong += mangSN[i];    
    }
    return tong;
}

void tinhTBvaSoNhoHonTB(int tong, int * mangSN, int soLuong)
{
    /*Tinh trung binh*/
    char i = 0;
    char dem = 0;
    float trungBinh = (float)tong / soLuong;    
    printf("\nSo trung binh la: %f\n", trungBinh);
    
    /*Dem so luong*/
    for(i = 0; i < soLuong; i++)
    {
        if(mangSN[i] < trungBinh)
        {
            dem++;
        }
    }
    printf("So luong so co gia tri nho hon gia tri trung binh la: %d\n\n", dem);
}

void sapXepMang(int * mangSN, int soLuong)
{
    /*Doi cho cac so trong mang*/
    char i = 0;
    int tam;
    char le = 0;
    char chan = soLuong - 1;
    while(le < chan)
    {
        while(mangSN[le] % 2 != 0)
        {
            le++;
        }
        while(mangSN[chan] % 2 == 0)
        {
            chan--;
        }
        if(le >= chan)
        {
            break;
        }
        tam = mangSN[le];
        mangSN[le] = mangSN[chan];
        mangSN[chan] = tam;
    }
    
    printf("Mang sau khi doi cho:\n");
    for(i = 0; i < soLuong; i++)
    {
        printf("%d ", mangSN[i]);
    }
}
  
