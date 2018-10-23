#include <stdio.h>
#include "calculate.h"
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
void inputArr(int arr[], int element)
{
	int i;
	for(i = 0; i < element;i++)
	{
		printf("Enter a[%d]: ",i);
		scanf("%d",&arr[i]);
	}
}

float functionMedium(int arr[],int element)
{
	int sum = 0;
	float medium;
	int i;
	for(i = 0; i < element;i++)
	{
		sum += arr[i];
	}
    medium = (float)(sum)/element;
    return medium;
}

int lessgMedium(int arr[], int medium, int element)
{
    int countLessMedium = 0;
    int i;
    for( i = 0;i < element;i++)
    {
        if(arr[i] < medium)
        {
            countLessMedium++;
        }
    }
    return countLessMedium;
}

void parityArrangement(int arr[], int element)
{
    int temp;
    int coutSort = 0;
    int i;
    int j;
    for ( i = 0; i < element; i++)
    {
        if(arr[i]%2 == 0)
        {
            temp = arr[i];
            arr[i] = arr[coutSort];
            arr[coutSort] = temp;
            coutSort++;
        }
    }
}

void printfArr(int arr[], int element)
{
	int i;
	for(i = 0; i < element; i++)
	{
		printf("%d ",arr[i]);
	}
}