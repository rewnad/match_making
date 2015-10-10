/*
 * linkedList.c
 *
 *  Created on: 01/07/2015
 *      Author: jkct440
 */

#include <stdio.h>
#include <stdlib.h>
#include "commonDefs.h"
#include "linkedList.h"
#include "memoryUtil.h"


linkedList_t* createList()
{
	linkedList_t *pNewList = (linkedList_t*) safeMalloc(sizeof(linkedList_t));
	pNewList->size = 0;
	pNewList->current_preference = 0;
	pNewList->pHead = NULL;


	return pNewList;
} /* end of createList() */

bigList_t* createBigList()
{
	bigList_t *pNewBigList = (bigList_t*) safeMalloc(sizeof(bigList_t));
	pNewBigList->size = 0;
	pNewBigList->pHead = NULL;

	return pNewBigList;
} /* end of createList() */


void destroyList(linkedList_t *pList)
{
	llNode_t *pCurrNode = pList->pHead;

	while (pCurrNode != NULL) {
		llNode_t *pTempNode = pCurrNode->pNext;
		safeFree(pCurrNode, sizeof(llNode_t));
		pCurrNode = NULL;
		pCurrNode = pTempNode;
	}

	pList->pHead = NULL;
	pList->size = 0;
	safeFree(pList, sizeof(linkedList_t));
} /* end of destroyList() */


void addNode(linkedList_t *pList, int candidate)
{
	llNode_t *pNewNode = (llNode_t*) safeMalloc(sizeof(llNode_t));
	pNewNode->candidate = candidate;
	pNewNode->priority = pList->size;
	/* if null, then first node.  If not null, then pNewNode becomes new head. */
	pNewNode->pNext = pList->pHead;
	pList->pHead = pNewNode;
	pList->size += 1;
} /** end of addNode() */

void addBigNode(bigList_t *pList, int candidate)
{
	struct bigNode_t *pNewNode = (struct bigNode_t*) safeMalloc(sizeof(struct bigNode_t));
	pNewNode->candidate= candidate;
	pNewNode->status = FREE;
	/* if null, then first node.  If not null, then pNewNode becomes new head. */
	pNewNode->preferences = createList();
	pNewNode->pNext = pList->pHead;
	pList->pHead = pNewNode;
	pList->size += 1;
}


int deleteNode(linkedList_t *pList, int candidate)
{
	llNode_t *pCurrNode = pList->pHead, *pPrevNode = NULL;

	if (pCurrNode != NULL) {
		/** If head is the deleted node. */
		if (pCurrNode->candidate== candidate) {
			pList->pHead = pCurrNode->pNext;
			safeFree(pCurrNode, sizeof(llNode_t));
			pList->size -= 1;
			return SUCCESS;
		}

		pPrevNode = pCurrNode;
		pCurrNode = pCurrNode->pNext;
	}

	while (pCurrNode != NULL) {
		if (pCurrNode->candidate== candidate) {
			pPrevNode->pNext = pCurrNode->pNext;
			safeFree(pCurrNode, sizeof(llNode_t));
			return SUCCESS;
		}
		pPrevNode = pCurrNode;
		pCurrNode = pCurrNode->pNext;
	}

	/* Can't find candidate. */
	return FAILED;
} /* end of deleteNode() */

int deleteBigNode(bigList_t *pList, int candidate)
{
	struct bigNode_t *pCurrNode = pList->pHead, *pPrevNode = NULL;

	if (pCurrNode != NULL) {
		/** If head is the deleted node. */
		if (pCurrNode->candidate== candidate) {
			pList->pHead = pCurrNode->pNext;
			safeFree(pCurrNode, sizeof(struct bigNode_t));
			pList->size -= 1;
			return SUCCESS;
		}
		pPrevNode = pCurrNode;
		pCurrNode = pCurrNode->pNext;
	}

	while (pCurrNode != NULL) 
	{
		if (pCurrNode->candidate== candidate) 
		{
			pPrevNode->pNext = pCurrNode->pNext;
			safeFree(pCurrNode, sizeof(struct bigNode_t));
			return SUCCESS;
		}
		pPrevNode = pCurrNode;
		pCurrNode = pCurrNode->pNext;
	}
	/* Can't find candidate. */
	return FAILED;
} /* end of deleteNode() */	

int findElement(linkedList_t *pList, int candidate)
{
	llNode_t *pCurrNode = pList->pHead;

	while (pCurrNode != NULL) {
		if (pCurrNode->candidate== candidate) {
			return FOUND;
		}
		pCurrNode = pCurrNode->pNext;
	}

	/** Can't find candidate. */
	return NOT_FOUND;
} /** end of findNode() */

int findBigElement(bigList_t *pList, int candidate)
{
	struct bigNode_t *pCurrNode = pList->pHead;

	while (pCurrNode != NULL) {
		if (pCurrNode->candidate== candidate) {
			return FOUND;
		}
		pCurrNode = pCurrNode->pNext;
	}

	/** Can't find candidate. */
	return NOT_FOUND;
}


void printList(linkedList_t *pList)
{
	llNode_t *pCurrNode = pList->pHead;

	while (pCurrNode != NULL) {
		printf("%d ", pCurrNode->candidate);
		pCurrNode = pCurrNode->pNext;
	}
	printf("\n");

} /* end of printList() */

