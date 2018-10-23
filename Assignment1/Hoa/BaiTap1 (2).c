#include<stdio.h>
#include<conio.h>
#include<stdlib.h>


/* check input number function*/ 
int clean_stdin() 
	{
    while (getchar() != '\n')  
	{
    }
    return 1; 
}
int check_number()
{
	int input; /* input value */
	int i =0 ; 
    char c;
    int count = 0;
    
	printf("N= ");
	while (((scanf("%d%c", &input, &c) != 2 || c != '\n'||input < 1) && clean_stdin()))/* check scanf || check c = enter ? || check input ? */
    {
    	printf("\n*Warning:Failed! Please enter an interger >0. N= ");
	}
	
	return input; 
}
/* insert element function */
void insert_element_array(int arr[], int array_length)
{
	int i;
	int input;
	char c;
	
	for(i=0;i<array_length;i++)
	{
		printf("\narr[%d]=",i);
		while (((scanf("%d%c", &input, &c) != 2 || c != '\n'||input < 1) && clean_stdin()))
		{
		    printf("Failed. arr[%d] must be an interger >0.\n", i);
		}	
		arr[i]=input;			
	}
}
/* sort function */
void sort_array(int arr[], int array_length) 
{
	/* running variable */
	int i;
	int j;
	int k; 
	k = array_length - 1;
	
	for(i = 0; i < array_length; i++ ) /* run from left to right*/
	{
		if(arr[i] %2 !=0) /* find the odd number */ 
		{
			for(j = k; j > i; j--) /* run form right to left*/ 
			{
				if(arr[j] %2 == 0)      /* find the even number */
				{
					/* swap them */
					int temp;
					temp = arr[i];
					arr[i] = arr[j];
					arr[j]= temp;
					break; /* after swapping a pair of numbers, break to find the next odd number is still on the left of the array */ 
				}
				k--; /* in the next loop j will only need to run from the previous even number we found */ 
			}
		}
		else continue; /* if not odd number, go to the next loop */
	}	
}

/* show output fucntion */
void show_data(int arr[], int array_length)
{
	int i;
	
	printf("\n ==========================");
	printf("\n ==========================");
	printf("\nYour Sorted Array: \n");
	for(i = 0; i < array_length; i++) 
	{
		printf("%d ",arr[i]);
	}
	printf("\nPress enter to continue");
}
/* main fucntion */
int main()
{
	int array_length;
	int *arr;
	
	array_length = check_number();
	arr = (int*) malloc(array_length*sizeof(int));
	insert_element_array(arr, array_length);
	sort_array(arr, array_length);
	show_data(arr, array_length);
	free(arr);
	
	return 0;
	
}



