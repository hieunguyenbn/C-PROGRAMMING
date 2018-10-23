#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include "header_template.h"

 
/* main function */
int main()
{
    /* saving size of matrixs array */
    
    int *p;
    do
    {
        p = Matrix_configure_size();
    }
    while(Check_size() == false);
	float *arrA = NULL; 
	float *arrB = NULL;
	float *arrC = NULL;
	float *arrD = NULL;
	
	Allocate_memo(&arrA, p, p+1);
	Allocate_memo(&arrB, p+2,p+3);
	Allocate_memo(&arrC, p, p+3);
	Allocate_memo(&arrD, p+1, p+2);
    Enter_element(arrA,arrB);
    Multi_matrix(arrA, arrB, arrC, arrD);
    Print_inputmatrix(arrA, arrB);
    Print_outputmatrix(arrC, arrD);
    Del_memo(arrA, arrB, arrC, arrD);

    return 0;
}
