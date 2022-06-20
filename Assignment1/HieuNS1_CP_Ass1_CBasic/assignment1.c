#include <stdio.h>
#include "assignment1.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*******************************************************************************
 * Variables
 ******************************************************************************/
int g_sum = 0;
int g_array[NMAX];
int g_num = 0;
/*******************************************************************************
 * Code
 ******************************************************************************/
void Input(int arr[NMAX], int n)
{
    char i = 0; /*incrementing or decrementing variable*/
    
    printf("\nEnter array's elements: ");
    for (i = 0; i < n; i++)
    {
        printf("arr[%d] = ", i);
        scanf("%d", &arr[i]);
        g_sum += arr[i]; /*add array's elements*/
    }

}

char Average(int arr[NMAX], int n)
{
    float av = 0; /*Average value of array's elements*/
    char count = 0; /*Counting the number of elements that are less than the average value*/
    char i = 0; /*incrementing or decrementing variable*/
    
    av = (float) g_sum/n;
    printf("\nThe average value of array is %.2f", av);
    
    for (i = 0; i < n; i++)
    {
        if (arr[i] < av)
        {
        	count++;
        }
    }
    printf("\nThe number of elements that are less than the average value is %d", count);
	return count;
}


void OddEvenArray(int arr[NMAX], int n)
{

    char EvenNum = 0; /*Updating index of even elements in the array*/
    char OddNum = 0; /*Updating index of odd elements*/
    int temp = 0; /*temporary variable*/
    char i = 0; /*incrementing or decrementing variable*/
    
    EvenNum = n - 1; /*Assign the even index as the end index of array*/ 
    
    while (OddNum < EvenNum)
    {
        
        while ((arr[OddNum]%2) && (OddNum < EvenNum))
        {
            OddNum++; /*Increasing the odd index variable if value of array at "OddNum" location is an odd number*/
        }
        while (!(arr[EvenNum]%2) && (OddNum < EvenNum))
        {
            EvenNum--; /*Decreasing the even index variable if value of array at "EvenNum" location is an even number*/
        }

        if (OddNum < EvenNum)
        {
            temp = arr[OddNum];
            arr[OddNum] = arr[EvenNum];
            arr[EvenNum] = temp;
            OddNum++;
            EvenNum--;
        }

    }

}

void Output(int arr[NMAX], int n)
{
    char i = 0; /*incrementing or decrementing variable*/
    for (i = 0; i < n; i++)
    {
        printf("%d\t", arr[i]);  
    }
}

int main(int argc, char *argv[])
{

    do 
    {
         printf("\nEnter the number of elements (Max is 20): ");
         scanf("%d", &g_num);
    } while (g_num <= 0 || g_num > 20);
    Input(g_array,g_num);
    Average(g_array,g_num);
    OddEvenArray(g_array,g_num);
    printf("\nArray after sorting odd and even number is: \n");
    Output(g_array,g_num);
    return 0;
}



