/*
 * linkedList.h
 *
 *  Created on: 01/07/2015
 *      Author: Jeffrey Chan
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_


/*
 * Linked list node type.
 */
struct linkedListNode_t;
struct bigNode_t;
struct bigList_t;
struct linkedListNode_t
{
	int lucky_person;
	struct linkedListNode_t *pNext;
};

typedef struct linkedListNode_t llNode_t;

/*
 * Linked list type.  Only has head pointer - implement tail pointer if you like.
 */
typedef struct
{
	/* pointer to head of list. */
	llNode_t *pHead;
	/* count of number of elements in list */
	int size;
} linkedList_t;

typedef struct bigList_t bigNode_t;

struct bigNode_t 
{
	/* pointer to head of list. */
	struct bigNode_t *pNext;
	linkedList_t *preferences;
	/* count of number of elements in list */
	int current_pref;
}; 

typedef struct
{
	/* pointer to head of list. */
	struct bigNode_t *pHead;
	/* count of number of elements in list */
	int size;
} bigList_t;





/* ************************************************************************************** */
/* Function declarations */


/*
 * Create an empty node.
 */
extern
linkedList_t* createList();

extern
bigList_t* createBigList();
/*
 * Destroy the list, assuming all memory is dynamically allocated.
 * pList - point to head of list.
 */
extern
void destroyList(linkedList_t *pList);


/*
 * Creates a node with value 'element' and adds the newly created node to 'pList', which points to the head of the list.
 * pList - point to head of list.
 * element - the element you want to insert into the list.
 */
extern
void addNode(linkedList_t *pList, int element);

extern
void addBigNode(bigList_t *pList, int element);
/*
 * Deletes a node containing element from list 'pList'.
 * pList - point to head of list.
 * element - the element you want to remove from the list.
 * status - the status of the deletion operation.
 *
 * returns - pointer to the (new) head of the list.
 */
extern
int deleteNode(linkedList_t *pList, int element);
extern
int deleteBigNode(bigList_t *pList, int element);


/*
 * Searches if element is in the list 'pList'.
 * pList - point to head of list.
 * element - the element you want to search for in the list.
 */
extern
int findElement(linkedList_t *pList, int element);
extern
int findBigElement(bigList_t *pList, int element);

/*
 * Print the elements in the list to stdout.
 * pList - point to head of list.
 */
extern
void printList(linkedList_t *pList);



#endif /* LINKEDLIST_H_ */
