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

#ifndef FSL_HEADER_TEMPLATE_H
#define FSL_HEADER_TEMPLATE_H

/*! @file */

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

#include <stdint.h>
#include <stdbool.h>


/*!
 * @defgroup template_group
 * @brief Template Group
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Example enum selection*/

/*!
 * @brief Defines the example structure
 *
 * This structure is used as an example.
 */


/*******************************************************************************
 * API
 ******************************************************************************/
/*!
 * @name Subgroup One
 * @{
 */

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief Initializes the template structure
 *
 * This function initializes the template structure
 * to a known value.
 *
 *
 *
 * @param[in] instance the instance number
 * @param[in] config configuration struct pointer
 */

                  
int Clean_stdin();
int Check_number_rc();
float Check_number_el();
int* Matrix_configure_size(); 
void Allocate_memo(float **arr, int *x, int *y);
bool Check_size();
void Enter_element(float *matrixA, float *matrixB);
void Multi_matrix(float *matrixA,float *matrixB, float *matrixC, float *matrixD);
void Print_inputmatrix(float *matrixA, float *matrixB);
void Print_outputmatrix(float *matrixC, float *matrixD);
void Del_memo(float *arrA, float *arrB, float *arrC, float *arrD);


/*! @} */

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* FSL_HEADER_TEMPLATE_H */
/*******************************************************************************
 * EOF
 ******************************************************************************/
