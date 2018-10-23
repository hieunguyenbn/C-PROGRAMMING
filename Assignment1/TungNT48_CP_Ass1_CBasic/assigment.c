#include "assigment.h"
#include <stdio.h>
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
void input( int a[MAX],int n)
{
	int i;
	for( i = 0;i < n;i++)

	{
		printf("Nhap vao gia tri phan tu thu %i : \n",i);
		scanf("%d",&a[i]);
	}
}

void output( int a[MAX],int n)
{
 	 int i;
	 printf("Mang da nhap vao : \n");
	for( i = 0;i < n;i++)
	{
		printf("%i \t",a[i]);
	}
}

int smallvsAvg(int arr[],int n)
{
 	 int i;
	 int count = 0;
	 float avg = avgArr(arr,n);
		for( i = 0;i < n;i++)
	{
			if(arr[i] < avg)
			{
			 	count++;
			}
	}
	return count;
}



float avgArr(int arr[MAX] , int n)
{
	int i;
	int sum = 0;
		for( i = 0;i < n;i++)
	{
		sum += arr[i];
	}

	return sum/(float)n ;
}


void swapEleament(int *eL1,int *eL2)
{
	int a = *eL1;
	*eL1 = *eL2;
	*eL2 = a;
}
void arrangeArr(int arr[MAX],int n)
{
	int startArr = 0;
	int endArr	 =  0;
	for (startArr = 0; startArr < n - 1;startArr++)
	{
		for(endArr = startArr+1; endArr < n;endArr++)
		{
			if(arr[startArr] % 2 == 0 && arr[endArr] % 2 != 0  )
			{
				swapEleament(&arr[startArr],&arr[endArr]);
			}

		}
	}
}

int main()
{
	int n;
	int i;
	do 
	{
		printf("Nhap vap so phan tu can tinh toan :\n" );
		scanf("%d",&n);
	}
	while(n <= 2 || n > 20);
	int arr[MAX];
	input(arr,n);
	output(arr,n);
	printf("\n Gia tri trung binh cua cac so da nhap vao : %f \n",avgArr(arr,n));
	printf("\n So phan tu nho hon gia tri trung binh : %d \n",smallvsAvg(arr,n));
	arrangeArr(arr,n);
	output(arr,n);
	return 0;
}
