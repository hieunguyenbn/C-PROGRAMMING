#ifndef _ASSIGNMENT_6_H_
#define _ASSIGNMENT_6_H_
#include <stdint.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define NMAX 20
#define CLASS_A 1
#define CLASS_B 0
#define OK 0
#define NOT_OK 1
#define ERROR -1
#define UNINIT_VAR8 0xFF
#define UNINIT_VAR32 0xFFFFFFFF

typedef enum {

    e_done = 0x00U,
    e_full = 0x01U,
    e_conflict_ID = 0xFFU,

} add_status_t;

typedef struct fresher
{
    uint32_t ID;
    int8_t classname;
    int8_t GPA;
    struct fresher *next;  /*pointer point to the next fresher*/  
} FRESHER;

/*define STAFF data type*/
typedef struct staff
{
    uint32_t ID; /*(4 bytes) identification number of a staff*/
    uint8_t ClassName; /* (1 byte) name of class*/
    uint8_t GPA; /*(1 byte) average point of a staff*/
} STAFF;

/*define a fresher node*/
typedef struct FresherNode
{
    STAFF FresherInfo; /*save data of fresher*/
    struct FresherNode *FresherNext;  /*pointer point to the next fresher*/
}FRESHER_NODE;

/*******************************************************************************
 * API
 ******************************************************************************/
/*!
 * @brief <Inserts new staff to staff list>
 * @param Head [output] <The pointer points to first node of list>.
 * @param newcode [input] <The new staff's code>.
 * @param newname [input] <The new staff's name>.
 * @param newacc [input] <The new staff's acc>.
 * @param newgpa [input] <The new staff's gpa>.
 * @return <OK: Funcion runs successfully, NOT_OK: Funcion runs fail>.
 */
add_status_t AddStaff(FRESHER fresher[], uint32_t id, int8_t classname, int8_t gpa);

/*!
 * @brief <Inserts new staff to staff list>
 * @param Head [intput] <The pointer points to first node of the list>.
 * @return <OK: Funcion runs successfully, NOT_OK: Funcion runs fail>.
 */
/*int showslist(staff *head);

/*!
 * @brief <Deletes ola staff to staff list>
 * @param Head [intput] <The pointer points to first node of list>.
 * @param name [input] <The name of old staff have to delete>.
 * @param acc [input] <The acc of old staff have to delete>.
 * @return <OK: Funcion runs successfully, NOT_OK: Funcion runs fail>.
 */
 uint8_t deleteStaff(FRESHER fresher[], uint32_t id);

/*!
 * @brief <Inserts new staff to staff list>
 * @param Head [intput] <The pointer points to first node of the list>.
 * @return <Length of list or NOT_OK: Funcion runs fail>.
 */
int8_t checkID(FRESHER fresher[], uint32_t id);


#endif
