#include <stdio.h>
#include <stdlib.h>
#include "handleHuyNQ51.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define SIZE_MAX          20

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/
int main(void)
{
    int arrProcess[SIZE_MAX];
    unsigned char sizeArrProcess;
    int sumArrProcess = 0;
    float averArrProcess;
    
    enterInput(arrProcess, &sizeArrProcess);
    
    sumArrProcess = sumArr(arrProcess, sizeArrProcess);
    
    /*Show average of array on screen*/
    averArrProcess = averageArr(sumArrProcess, sizeArrProcess);
    printf("Average of array = %.2f", averArrProcess);
    
    /*Show amount of number which is smaller than average value*/
    printf("\nAmount of number which is smaller than average value = %d", 
                   nbSmallerAverage(arrProcess, sizeArrProcess, averArrProcess));
    
    /*Show array after arrange: Even number - right, Odd number - left*/
    printf("\nNumbers after average even and odd: ");
    arrangeEvenOdd(arrProcess, sizeArrProcess);
    showArr(arrProcess, sizeArrProcess);
    
    return 0;
}
