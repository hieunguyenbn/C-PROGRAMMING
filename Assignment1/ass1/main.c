#include <stdio.h>
#include "assignment1.h"


/*******************************************************************************
 * Variables:
 g_array: mang chua toi da nmax phan tu
 g_num: so phan tu nguoi dung muon nhap vao
 ******************************************************************************/
int g_array[nmax];
int g_num;


int main(int argc, char *argv[]) {
	
	printf("\nNhap vao so phan tu cua mang (toi da la 20): ");
    scanf("%d", &g_num);
	
    Average(g_array,g_num);
	ChanLe(g_array,g_num);
	
	return 0;
}

