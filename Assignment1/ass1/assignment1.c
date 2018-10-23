#include <stdio.h>
#include "assignment1.h"

void Average(int a[nmax], int n) {
    /*Additional ariables
        sum: tong cac phan tu trong mang
        av: trung binh cua cac phan tu do
        count: dem so phan tu nho hon gia tri trung binh
        i: bien chay
	*/
    int sum = 0;
    float av = 0;
    char count = 0;
    char i;
    
    printf("\nNhap vao cac phan tu cua mang: ");
  
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        sum += a[i];
		
   } 
	
    av = (float) sum/n;     	
    printf("\nGia tri trung binh cua cac so vua nhap la %.2f", av);
	
    for (i = 0; i < n; i++) {
	    if (a[i] < av) {
	        count++;
	   }
    }
	
    printf("\nSo luong cac so nho hon trung binh la %d", count);	
}

void ChanLe(int a[nmax], int n) {
	/*Additional ariables
        chan: bien luu vi tri phan tu chan trong mang
        che: bien luu vi tri phan tu le
        temp: bien tam de trao doi hai phan tu
        i: bien chay
	*/
	char chan = 0;
	char le = 0;
	int temp = 0;
	char i = 0;
	chan = n - 1;
    
	while (le < chan) {
        
	    while ((a[le]%2) && (le < chan)) {
	    	le++;
	    }
	    while (!(a[chan]%2) && (le < chan)) {
	    	chan--;
	    }
	    
	    if (le < chan) {
	    	temp = a[le];
	    	a[le] = a[chan];
	    	a[chan] = temp;
	    	le++;
	    	chan--;
	    }
	
    }

    printf("\nMang sau khi sap xep so le, so chan la: \n");
    for (i = 0; i < n; i++) {
	    printf("%d\t", a[i]);  
    }
}


