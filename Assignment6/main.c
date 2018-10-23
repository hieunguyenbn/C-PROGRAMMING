#include <stdio.h>
#include <stdlib.h>
#include "assignment6.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/
extern FRESHER *g_head; /*head of the list*/
/*******************************************************************************
 * Code
 ******************************************************************************/

/*Initialize list of freshers*/
void InitList(FRESHER fresher[])
{
    uint8_t i = 0; /*increment*/
    for(i = 0; i < NMAX; i++)
	{
	    fresher[i].ID = UNINIT_VAR32;
	    fresher[i].classname = UNINIT_VAR8;
	    fresher[i].GPA = UNINIT_VAR8;
	    fresher[i].next = NULL;
	}
}

/*Print out information of a list of staffs*/
void PrintList(void)
{
    uint8_t i = 1; /*increment*/
    if (g_head == NULL)
    {
        printf("NO STAFF IN LIST\n");
    }
    else   
    {  
        while (g_head->next != NULL)
        {
            printf("\n\nSTAFF %d\n", i++);
            printf("=================\n");
            printf("\nID: %d", g_head->ID);
            printf("\nGPA: %d", g_head->GPA);
            if (g_head->classname == 0)
            {
                 printf("\nClass: A");
            }
            else
            {
                printf("\nClass: B");
            }   
            
            g_head = g_head->next;
            
        }
//        printf("\n\nSTAFF %d", i++);
//        printf("\nID: %d", g_head->ID);
//        printf("\nGPA: %d", g_head->GPA);
//        if (g_head->classname == 0)
//        {
//            printf("\nClass: A");
//        }
//        else
//        {
//            printf("\nClass: B");
//        } 

    }   
}

int main() {
    
    FRESHER fresherStaff[NMAX];
    uint8_t stop = 1;
    uint8_t option = 0;
    static uint32_t id = 0;
    uint32_t delID = 0;
    int8_t classname = 0;
    int8_t gpa = 0;
    
    InitList(fresherStaff);
    
    while (stop)
    {
        printf("\nPleas select options:\n");
        printf("Press 1 for Add staff\n");
        printf("Press 2 for Print out the list\n");
        printf("Press 3 for Delete staff\n");
        printf("Press 4 for Exit\n");
        scanf("%d", &option);
        switch(option)
        {
        case 1:
            printf("\nEnter fresher's ID: ");
        	scanf("%d", &id);

            do {
                    printf("\nEnter fresher's class name (press 0 for class A, press 1 for class B): ");
                    scanf("%d", &classname);
            } while (classname > 1 || classname < 0);
            do {
                    printf("\nEnter fresher's GPA (from 0 to 100): ");
        	        scanf("%d", &gpa);
            } while (gpa > UNINIT_VAR8 || gpa < 0);
            
            if (AddStaff(fresherStaff, id, classname, gpa) == e_done)
            {
                printf("\nAdd new staff successfully!\n");
            }
            else if (AddStaff(fresherStaff, id, classname, gpa) == e_full)
            {
                printf("\nThe List is FULL\n");
            }
            else
            {
                printf("\nCONFLICT ID!\n");
            }
            break;
        case 2:
            PrintList();
            break;
        case 3:
            printf("\nWhich ID do you want to delete?: ");
            scanf("%d", &delID);
            if (deleteStaff(fresherStaff,delID))
            {
                printf("\nCannot delete!\n");
            }
            else 
            {
                printf("\nDELETE SUCCESSFULLY!\n");   
            }
            break;
        default:
            stop = 0;
            break;
        }
    }

	return 0;
}
