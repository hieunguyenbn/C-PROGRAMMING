#include <stdio.h>
#include <stdint.h>
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
 FRESHER *g_head; /*head of the list*/
/*******************************************************************************
 * Code
 ******************************************************************************/

int8_t checkID(FRESHER fresher[], uint32_t id)
{
	uint8_t i = 0;/*increment*/
	int8_t returnVal = 0; /*return value*/

	if (id > UNINIT_VAR32) /*if user enter an ID value out of the type range*/
	{
	    returnVal = ERROR;
	}
	for (i = 0; i < NMAX; i++) /*finding suitable position*/
	{
	    if (id == fresher[i].ID) /*conflict ID*/
	    {
            returnVal = ERROR;
	    	break;
	    }
	    if (fresher[i].ID == UNINIT_VAR32) /*empty position*/
	    {
	        returnVal = i;
	    	break;
	    }
    }
	return returnVal;
}

add_status_t AddStaff(FRESHER fresher[], uint32_t id, int8_t classname, int8_t gpa)
{
	int8_t index = 0; /*find position to add*/
	FRESHER *current = g_head; /*save the current node*/
    FRESHER *previous =  NULL; /*save the previous node*/  
	
    index = checkID(fresher,id); /*check ID input to find suitable position*/

    if (index == ERROR)
    {
        return e_conflict_ID; /*conflict ID*/
    }     
    if (index == NMAX)
	{
		return e_full; /*This list is full*/
	} 
	
    fresher[index].ID = id;
    fresher[index].classname = classname;
    fresher[index].GPA = gpa;
    if (g_head == NULL) /*there hasnt had any fresher yet*/
    {
        fresher[index].next = NULL;	
        g_head = &fresher[index];
        return e_done;
    }
    
    while (1)
    {
    
        if ((fresher[index].GPA > current->GPA) || /*The fresher need to add have GPA > current fresher*/
        (fresher[index].GPA == current->GPA && fresher[index].classname < current->classname)) /*fresher have gpa = current and in class A*/
        {
            if (current == g_head)
            {
                fresher[index].next = current;
                g_head = &fresher[index];
                return e_done;
            }
            fresher[index].next = current;
            previous->next = &fresher[index];
            return e_done;
        }
        else
        {
                previous = current;
                current = current->next;
                if (current->next == NULL)
                {
                    current->next = &fresher[index];
                    return e_done;
                }
                return e_done;
        }

    }

}


uint8_t deleteStaff(FRESHER fresher[], uint32_t id)
{
	FRESHER *current = g_head; /*save the current node*/
    FRESHER *previous = NULL; /*save the previous node*/ 
	uint8_t i = 0; /*increment*/
	
    if (g_head == NULL)
    {
      return OK;
	}
    
    while(current->ID != id)
    {
		if(current->next == NULL)
		{
            return NOT_OK;
		}
        else 
		{
			previous = current;
			current = current->next;             
		}
	}
    if (current == g_head) 
    {
		g_head = g_head->next;
	}
    else 
    {
		previous->next = current->next;
	}    
	for(i = 0; i < NMAX; i ++)
	{
		if(fresher[i].ID == id)
		{
			fresher[i].ID = UNINIT_VAR32;
			fresher[i].GPA = UNINIT_VAR8;
			fresher[i].classname = UNINIT_VAR8;
			fresher[i].next = NULL;
			break;
		}
	}
	 
	return OK;
}
