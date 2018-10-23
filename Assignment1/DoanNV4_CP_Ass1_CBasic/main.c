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
int main()
{
    int arr[MAX];
	int elementArr;
	float mediumLocal;
	do
	{
		printf("Enter elenemt of array: ");
		scanf("%d",&elementArr); /*enter element of array*/
	}
	while(elementArr <= 0 | elementArr > MAX); /*check element*/

	inputArr(arr,elementArr);
	
	printfArr(arr,elementArr);
    
	mediumLocal = functionMedium(arr,elementArr);
    printf("medium = %f\n",mediumLocal);
	printf ("less medium = %d\n", lessgMedium(arr,mediumLocal,elementArr));
    
	parityArrangement(arr,elementArr);
	
	printfArr(arr,elementArr);
    scanf("%d",&elementArr);
	return 0;
}