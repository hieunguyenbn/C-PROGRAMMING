/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
/**
 * @page misra_violations MISRA-C:2012 violations
 *
 *
 * @section [global]
 * Violates MISRA 2012 Required Rule 11.6, A cast shall not be performed
 * between pointer to void and an arithmetic type.
 * The base address parameter from HAL functions is provided as integer so
 * it needs to be cast to pointer.
 *
 * @section [global]
 * Violates MISRA 2012 Advisory Rule 11.4, A conversion should not be performed
 * between a pointer to object and an integer type.
 * The base address parameter from HAL functions is provided as integer so
 * a conversion between a pointer and an integer has to be performed
 */
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "header_template.h"
int size[4];
/*******************************************************************************
 * Variable
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : Clean_stdin
 * Description   : This function checks if anything except '\n' is entered or not
 * Implements    : The While loop will read all lefted character in the buffer 
 * until that character is Enter
 *END**************************************************************************/
int Clean_stdin()
{
    while (getchar() != '\n')
    {
    }

    return 1; 
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Check_number_rc
 * Description   : This function checks if the input number is interger > 0 or not 
 * because the amout of the column and the row must be interger > 0
 * Implements    : scanf("%d%c", &input, &c) != 2 || c != '\n' guarantee that 
 * the number of data which scanf read is not 2 or the entered character is not '\n'
 *END**************************************************************************/
int Check_number_rc()
{
    int input;
    unsigned int i =0 ;
    char c;

    while (((scanf("%d%c", &input, &c) != 2 || c != '\n'||input < 1) && Clean_stdin()))
    {
        printf("\n*Warning:Failed! The amount of the row and column must be interger type >0.\nEnter again:  ");
    }
    return input;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Check_number_el
 * Description   : This function checks if the number is float or not
 * because the request of the math is all elements of matrices must be any number. 
 *
 * Implements    : as same as Check_number_rc, but the difference is the entered 
 * numbers are float
 *END**************************************************************************/
float Check_number_el()
{
    float input;
    unsigned int i =0 ;
    char c;
    /* check scanf || check c = enter ? || check input ? */
    while (((scanf("%f%c", &input, &c) != 2 || c != '\n') && Clean_stdin()))
    {
        printf("\n*Warning:Failed! This value must be float type >0.\nEnter again:  ");
    }
    return input; 
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Matrix_configure_size
 * Description   : This function initializes the sizes of matrices
 * the values will be put in an array.
 * Implements    : At first, it will checks the input then if the input is acceptable
 * it will be saved into array size[].
 *END**************************************************************************/
int* Matrix_configure_size() 
{   
	int *address; 
    printf("Please enter the amout of row of the Matrix A ");
    /* size[0] = MatrixA_row */
    size[0] = Check_number_rc();
    printf("Please enter the amout of column of the Matrix A ");
    /* size[1] = MatrixA_col  */
    size[1] = Check_number_rc();
    printf("Please enter the amout of row of the Matrix B ");
    /* size[0] = MatrixB_raw */
    size[2] = Check_number_rc();
    printf("Please enter the amout of column of the Matrix B ");
    /* size[0] = MatrixB_col */
    size[3] = Check_number_rc();
    address = (int*)&size[0];
    return address;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Check_size
 * Description   : This function checks the size of matrices and return a value 
 * Implements    : This function will compare the sizes of two matrices then 
 * return a value.
 *END**************************************************************************/
bool Check_size()
{
	bool check;
    if (size[0] == size[3] || size[1] == size[2])
    {
        if(size[1] == size[2])
        {
            printf("[A] * [B] is feasible!\n");
        }

        if(size[0] == size[3])
        {
            printf("[B] * [A] is feasible\n");
        }
        check = true;
    }

    else if(size[0] != size[3] && size[1] != size[2])
    {
        printf("Wrong size!\n");
        printf("[A] * [B] and [B] * [A] are not feasible!\n");
        check = false;

    }
    return check;
    
}

void Allocate_memo(float **arr, int *x, int *y)
{
	*arr = (float *)malloc((*x) * (*y) * sizeof(float));
}
/*FUNCTION**********************************************************************
 *
 * Function Name : Enter_element
 * Description   : This function enters values for input matrices
 * Implements    : 
 *END**************************************************************************/
void Enter_element(float *matrixA, float *matrixB)
{
    unsigned int i;
    unsigned int j;
    
    for(i = 0; i < size[0]; i++)
    {
        float element;
        for(j = 0; j < size[1]; j++)
        {
            printf("A[%d][%d] = ",i, j);
            (*(matrixA + i * size[1] + j)) = Check_number_el();
        }
    }
    printf("\n==========*===============*===========\n");
    for(i = 0; i < size[2]; i++)
    {
        float element;
        for(j = 0; j < size[3]; j++)
        {
            printf("B[%d][%d] = ",i, j);
            (*(matrixB + i * size[3] + j)) = Check_number_el();
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Multi_matrix
 * Description   : This function processes multiplication between two matrices
 * Implements    : 
 *END**************************************************************************/
void Multi_matrix(float *matrixA,float *matrixB, float *matrixC, float *matrixD)
{
    unsigned int i;
    unsigned int j;
    unsigned int k;

    if(size[1] == size[2])
    {
        for(i = 0 ; i < size[0] ; i++)
        {
            for(j = 0; j < size[3]; j++)
            {
                float sum = 0;
                for(k = 0; k < size[1]; k++)
                {
                    sum += (*(matrixA + i * size[1] + k)) * (*(matrixB + k * size[3] + j));
                }
                *(matrixC + i * size[3] + j) = sum; 
            }
        }
    }

    if(size[0] == size[3])
    {
        for(i = 0 ; i < size[2] ; i++)
        {
            for(j = 0; j < size[1]; j++)
            {
                float sum = 0;
                for(k = 0; k < size[0]; k++)
                {
                    sum += (*(matrixB + i * size[3] + k)) * (*(matrixA + k * size[1] + j));
                }
                *(matrixD + i * size[1] + j) = sum; 
            }
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Print_outputmatrix
 * Description   : This function prints the result
 * Implements    : 
 *END**************************************************************************/
void Print_outputmatrix(float *matrixC, float *matrixD)
{
    unsigned int i;
    unsigned int j;

    if (size[1] == size [2])
    {
        printf("\n");
        printf("\n==========*===============*===========\n");
        printf("\n[A] * [B] = [C]:\n\n");
        for(i = 0; i < size[0]; i++) 
        {
            for(j = 0; j < size[3]; j++)
            {
                /* print matrixC out */
                printf("%7.1f", *(matrixC + i * size[3] + j));
            }
            printf("\n");
        }
    }

    if (size[0] == size [3])
    {
        printf("\n");
        printf("\n==========*===============*===========\n");
        printf("\n[B] * [A] = [D]:\n\n");
        for(i = 0; i < size[2]; i++) 
        {
            for(j = 0; j < size[1]; j++)
            {
                /* print matrixC out */
                printf("%7.1f", *(matrixD + i * size[1] + j));
            }
            printf("\n");
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Print_inputmatrix
 * Description   : This function prints two input matrices
 * Implements    : This function prints matrix [A] first then prints matrix [B]
 *END**************************************************************************/
void Print_inputmatrix(float *matrixA, float *matrixB)
{
    unsigned int i;
    unsigned int j;
    unsigned int k;

    printf("\nMatrix [A]:\n");
    for(i = 0; i < size[0]; i++) 
    {
        for(j = 0; j < size[1]; j++)
        {
            /* print matrixA out */
             printf("%7.1f", (*(matrixA + i * size[1] + j)));
        }
        printf("\n");
    }

    printf("\n");

    printf("\nMatrix [B]:\n");
    for(i = 0; i < size[2]; i++) 
    {
        for(j = 0; j < size[3]; j++)
        {
            /* print matrixB out */
            printf("%7.1f", (*(matrixB + i * size[3] + j))); 
        }
        printf("\n");
    }
}
/*
void Print_text(float *matrix, int row, int col)
{
	FILE *f;
	f = fopen("DATA.txt","w+");
	for(i = 0; i < row; i++) 
    {
        for(j = 0; j < col; j++)
        {
            /* print matrixA out 
             fprintf(f,"%7.1f", (*(matrixA + i * col + j)));
        }
        
    }
    fclose(f);
	
}*/

/*FUNCTION**********************************************************************
 *
 * Function Name : Del_memo
 * Description   : This function frees all aloccated memories 
 * Implements    : 
 *END**************************************************************************/
void Del_memo(float *arrA, float *arrB, float *arrC, float *arrD)
{
    free(arrA);
    free(arrB);
    free(arrC);
    free(arrD);
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
