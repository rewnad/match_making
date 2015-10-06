/*
 * bpGraphAdjMat_AA.c
 *
 *  Created on: 01/07/2015
 *      Author: Jeffrey Chan
 */


#include <stddef.h>
#include <stdio.h>
#include "bipartiteGraph.h"
#include "linkedList.h"
#include "memoryUtil.h"

/* select partite */
bigList_t * choose_partite(bpGraph_t* pList, int partite);
struct implBipartGraph_t
{
	/** Vertex number of partite 1. */
	int vertNum1;
	/** Vertex number of partite 2. */
	int vertNum2;

	/* Dynamically allocated array of linked lists of neighbours for partite 1. */
	bigList_t * males;
	bigList_t * females;
};



/* ************************************************************************* */
/* Function implementations */

bigList_t * choose_partite(bpGraph_t* pList, int partite)
{
	if(partite == 1)
	{
		return pList->list1;
	}
	if(partite == 2)
	{
		return pList->list2;
	}
	return NULL;
}


bpGraph_t* bipartGraphCreate(int part1VertNum, int part2VertNum)
{
	/* TODO: Implement me! */
	bpGraph_t* pGraph;
	pGraph = (bpGraph_t*)safeMalloc(sizeof(bpGraph_t));

	pGraph->vertNum1 = part1VertNum;
	pGraph->vertNum2 = part2VertNum;

	pGraph->list1 = createBigList();
	pGraph->list2 = createBigList();
	for(int i=0;i<part1VertNum;i++)
	{
		addBigNode(pGraph->list1, i);

	}
	for(int i=0;i<part2VertNum;i++)
	{
		addBigNode(pGraph->list2, i);
	}
	return pGraph;
	
} /* end of bipartGraphDestroy() */


void bipartGraphDestroy(bpGraph_t* pGraph)
{
	/* TODO: Implement me! */
} /* end of bipartGraphDestroy() */


int bipartGraphInsertVertex(bpGraph_t* pGraph, int vertId, int partite)
{
	bigList_t * current = choose_partite(pGraph,partite);
	if(bipartGraphFindVertex(pGraph, vertId, partite))	
	{	
		return EXISTING_VERTEX;
	}
	else
	{
		addBigNode(current, vertId);
		return NEW_VERTEX;
	}
	return FAILED;
} /* end of bipartGraphInsertVertex() */


int bipartGraphInsertEdge(bpGraph_t* pGraph, int srcVertId, int tarVertId, int srcPartite)
{
	bigList_t * bigList = choose_partite(pGraph, srcPartite);
	struct bigNode_t * bigNode = bigList->pHead;

	if(bipartGraphFindEdge(pGraph, srcVertId, tarVertId, srcPartite))
	{
		return EXISTING_EDGE;
	}
	else if(bipartGraphFindVertex(pGraph, tarVertId, partite))
	{

	}
	else
	{
		while(bigNode)
		{
			if(bigNode->element == srcVertId)
			{
				addNode(bigNode->edges, tarVertId);
				return NEW_EDGE;
			}
			bigNode = bigNode->pNext;
		}
	}
	return ERROR_VALUE;
} /* end of bipartGraphInsertEdge() */


int bipartGraphDeleteVertex(bpGraph_t* graph, int vertId, int partite)
{
	bigList_t * bigList = choose_partite(graph,partite);
	if(!bipartGraphFindVertex(graph, vertId, partite))
	{
		return FAILED;
	}
	else
	{
		deleteBigNode(bigList, vertId);
		return SUCCESS;
	}

	return ERROR_VALUE;
} /* end of bipartGraphDeleteVertex() */


int bipartGraphDeleteEdge(bpGraph_t* pGraph,  int srcVertId, int tarVertId, int srcPartite)
{
	bigList_t * bigList = choose_partite(pGraph, srcPartite);
	struct bigNode_t * bigNode = bigList->pHead;
	if(!bipartGraphFindEdge( pGraph, srcVertId, tarVertId, srcPartite))
	{
		return FAILED;
	}
	else
	{
		while(bigNode)
		{
			if(bigNode->element == srcVertId)
			{
				deleteNode(bigNode->edges, tarVertId);
				return SUCCESS;
			}
			bigNode = bigNode->pNext;
		}	
	}
	return ERROR_VALUE;
} /** end of bipartGraphDeleteEdge() */


int bipartGraphFindVertex(bpGraph_t *pGraph, int vertId, int partite)
{
	bigList_t * current = choose_partite(pGraph,partite);
	if(findBigElement(current, vertId))
	{
		return FOUND;
	}
	else
	{
		return NOT_FOUND;
	}
	return NOT_FOUND;
} /* end of bipartGraphFindVertex() */


int bipartGraphFindEdge(bpGraph_t* graph, int srcVertId, int tarVertId, int srcPartite)
{
	bigList_t * bigList = choose_partite(graph, srcPartite);
	struct bigNode_t * bigNode = bigList->pHead;
	while(bigNode)
	{
		if(bigNode->element == srcVertId)
		{
			if(findElement(bigNode->edges, tarVertId))
			{
				return FOUND;
			}
			else
			{
				return NOT_FOUND;
			}
		}
		bigNode = bigNode->pNext;
	}
	
	return NOT_FOUND;
} /* end of bipartGraphFindEdge() */


void bipartGraphPrint(bpGraph_t *pGraph)
{
	printf("Vertices\n");
	printf("Part 1\n");
	struct bigNode_t * bigNode = pGraph->list1->pHead;
	while(bigNode)
	{	
		printf("%d ", bigNode->element);
		bigNode = bigNode->pNext;
	}

	printf("\n");

	printf("Vertices\n");
	printf("Part 2\n");
	bigNode = pGraph->list2->pHead;
	while(bigNode)
	{	
		printf("%d ", bigNode->element);
		bigNode = bigNode->pNext;
	}
	printf("\n");
	printf("Edges 1 to 2\n");
	bigNode = pGraph->list1->pHead;
	while(bigNode)
	{	
		llNode_t *pCurrNode = bigNode->edges->pHead;
		while (pCurrNode) 
		{

			printf("%d %d\n",bigNode->element, pCurrNode->element);
			pCurrNode = pCurrNode->pNext;
		}
		bigNode = bigNode->pNext;
	}
	printf("Edges 2 to 1\n");
	bigNode = pGraph->list2->pHead;
	while(bigNode)
	{	
		llNode_t *pCurrNode = bigNode->edges->pHead;
		while (pCurrNode) 
		{

			printf("%d %d\n",bigNode->element, pCurrNode->element);
			pCurrNode = pCurrNode->pNext;
		}
		bigNode = bigNode->pNext;
	}
} /* end of bipartGraphPrint() */

