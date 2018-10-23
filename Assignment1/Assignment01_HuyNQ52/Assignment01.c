#include <stdio.h>
#include <stdint.h>
#include "intArr.h"

/* Assignment 1*/

#define NMAX 20

extern float avgArr(int32_t *pArr, uint8_t nElement);
extern uint8_t nLess(float keyComp, int32_t *pArr, uint8_t nElement);

int main(void)
{
    int32_t Arr[NMAX];
    uint8_t nE;
    float avg;
    
    nE = nElement();
    enter(Arr, nE);
    disp(Arr, nE);
    avg = avgArr(Arr, nE);
    printf("\n\n Average: %.9f", avg);
    printf("\n Number of elements lower than average: %d", nLess(avg, Arr, nE));
    printf("\n\n Arrange the array. The rule: Odd elements are in the left of even elements:");
    arrOddEven(Arr, nE);
    disp(Arr, nE);
    getch();
    return 0;
}
