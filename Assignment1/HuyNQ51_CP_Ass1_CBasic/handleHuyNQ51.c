#include <stdio.h>
#include "handleHuyNQ51.h"

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
void enterInput(int *arrIn, unsigned char *sizeArrIn)
{
    unsigned char i;
    /*Enter number of data*/
    do
    {
        printf("%d is the maximum data number!\n", SIZE_MAX);
        printf("Number of data = ");
        scanf("%d", sizeArrIn);
    }while(!((*sizeArrIn <= SIZE_MAX)&&(*sizeArrIn > 0)));
    
    /*Data entry*/
    for(i = 0; i < *sizeArrIn; i++)
    {
        scanf("%d", &arrIn[i]);
    }
}

int sumArr(int *arrIn, unsigned char sizeArrIn)
{
    unsigned char i;
    int sumArrIn = 0;
    for(i = 0; i < sizeArrIn; i++)
    {
        sumArrIn += arrIn[i];
    }
    return sumArrIn;
}

float averageArr(int sumArr, unsigned char sizeArrIn)
{
    return (float)sumArr/(float)sizeArrIn;
}

int nbSmallerAverage(int *arrIn, unsigned char sizeArrIn, float averArrIn)
{
    unsigned char i;
    unsigned int nbOfSmaller = 0;
    for(i = 0; i < sizeArrIn; i++)
    {
        if(arrIn[i] < averArrIn) 
        {
            nbOfSmaller++;
        }
    }
    return nbOfSmaller;
}

void arrangeEvenOdd(int *arrIn, unsigned char sizeArrIn)
{
    unsigned char i = 0;
    unsigned char j = sizeArrIn - 1;
    int temp;
    
    for(; (i - j) < 1; )
    {
        if(arrIn[i]%2 == 0)
        {
            if(arrIn[j]%2 == 1)
            {
                /*Doi cho*/
                temp = arrIn[i];
                arrIn[i] = arrIn[j];
                arrIn[j] = temp;
                i++;
                j--;
            }
            else
            {
                j--;
            }
        }
        else
        {
            i++;
        }
    }
}

void showArr(int *arrIn, unsigned char sizeArrIn)
{
    unsigned char i;
    for(i = 0; i < sizeArrIn - 1; i++)
    {
        printf("%d, ", arrIn[i]);
    }
    printf("%d", arrIn[i]);
}

