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
#include "commonDefs.h"


/* select partite */
bigList_t * choose_sex(bpGraph_t* pList, int sex);
struct implBipartGraph_t
{
	/** Vertex number of partite 1. */
	int num_males;
	/** Vertex number of partite 2. */
	int num_females;

	/* Dynamically allocated array of linked lists of neighbours for partite 1. */
	bigList_t * males;
	bigList_t * females;
};


void add_preferences_to_user(bpGraph_t* pGraph, int user,int preference,int sex)
{
	bigList_t* current = choose_sex(pGraph,sex);
	struct bigNode_t * node = current->pHead;
	while(node)
	{
		if(node->candidate == user)
		{
			addNode(node->preferences, preference);
			return;
		}
		node = node->pNext;
	}

	return;
}
/* ************************************************************************* */
/* Function implementations */

bigList_t * choose_sex(bpGraph_t* pList, int sex)
{
	if(sex == 1)
	{
		return pList->males;
	}
	if(sex == 2)
	{
		return pList->females;
	}
	return NULL;
}


bpGraph_t* bipartGraphCreate(int num_males, int num_females)
{
	/* TODO: Implement me! */
	bpGraph_t* pGraph;
	pGraph = (bpGraph_t*)safeMalloc(sizeof(bpGraph_t));

	pGraph->num_males = num_males;
	pGraph->num_females = num_females;

	pGraph->males = createBigList();
	pGraph->females = createBigList();
	for(int i=0;i<num_males;i++)
	{
		addBigNode(pGraph->males, i);

	}
	for(int i=0;i<num_females;i++)
	{
		addBigNode(pGraph->females, i);
	}
	return pGraph;
	
} /* end of bipartGraphDestroy() */


void bipartGraphDestroy(bpGraph_t* pGraph)
{
	/* TODO: Implement me! */
} /* end of bipartGraphDestroy() */


int bipartGraphInsertVertex(bpGraph_t* pGraph, int vertId, int partite )
{
	bigList_t * current = choose_sex(pGraph, partite);
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


int bipartGraphInsertEdge(bpGraph_t* pGraph, int srcVertId, int tarVertId, int srcpartite)
{
	bigList_t * bigList = choose_sex(pGraph, srcpartite);
	struct bigNode_t * bigNode = bigList->pHead;

	if(bipartGraphFindEdge(pGraph, srcVertId, tarVertId, srcpartite))
	{
		return EXISTING_EDGE;
	}
	else if(bipartGraphFindVertex(pGraph, tarVertId, srcpartite))
	{

	}
	else
	{
		while(bigNode)
		{
			if(bigNode->candidate== srcVertId)
			{
				addNode(bigNode->preferences, tarVertId);
				return NEW_EDGE;
			}
			bigNode = bigNode->pNext;
		}
	}
	return ERROR_VALUE;
} /* end of bipartGraphInsertEdge() */


int bipartGraphDeleteVertex(bpGraph_t* graph, int vertId, int partite)
{
	bigList_t * bigList = choose_sex(graph,partite);
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


int bipartGraphDeleteEdge(bpGraph_t* pGraph,  int srcVertId, int tarVertId, int srcpartite)
{
	bigList_t * bigList = choose_sex(pGraph, srcpartite);
	struct bigNode_t * bigNode = bigList->pHead;
	if(!bipartGraphFindEdge( pGraph, srcVertId, tarVertId, srcpartite))
	{
		return FAILED;
	}
	else
	{
		while(bigNode)
		{
			if(bigNode->candidate== srcVertId)
			{
				deleteNode(bigNode->preferences, tarVertId);
				return SUCCESS;
			}
			bigNode = bigNode->pNext;
		}	
	}
	return ERROR_VALUE;
} /** end of bipartGraphDeleteEdge() */


int bipartGraphFindVertex(bpGraph_t *pGraph, int vertId, int partite)
{
	bigList_t * current = choose_sex(pGraph,partite);
	if(findBigcandidate(current, vertId))
	{
		return FOUND;
	}
	else
	{
		return NOT_FOUND;
	}
	return NOT_FOUND;
} /* end of bipartGraphFindVertex() */


int bipartGraphFindEdge(bpGraph_t* graph, int srcVertId, int tarVertId, int srcpartite)
{
	bigList_t * bigList = choose_sex(graph, srcpartite);
	struct bigNode_t * bigNode = bigList->pHead;
	while(bigNode)
	{
		if(bigNode->candidate== srcVertId)
		{
			if(findcandidate(bigNode->preferences, tarVertId))
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
	struct bigNode_t * bigNode = pGraph->males->pHead;
	while(bigNode)
	{	
		printf("%d ", bigNode->candidate);
		bigNode = bigNode->pNext;
	}

	printf("\n");

	printf("Vertices\n");
	printf("Part 2\n");
	bigNode = pGraph->females->pHead;
	while(bigNode)
	{	
		printf("%d ", bigNode->candidate);
		bigNode = bigNode->pNext;
	}
	printf("\n");
	printf("preferences 1 to 2\n");
	bigNode = pGraph->males->pHead;
	while(bigNode)
	{	
		llNode_t *pCurrNode = bigNode->preferences->pHead;
		while (pCurrNode) 
		{

			printf("%d %d\n",bigNode->candidate, pCurrNode->candidate);
			pCurrNode = pCurrNode->pNext;
		}
		bigNode = bigNode->pNext;
	}
	printf("preferences 2 to 1\n");
	bigNode = pGraph->females->pHead;
	while(bigNode)
	{	
		llNode_t *pCurrNode = bigNode->preferences->pHead;
		while (pCurrNode) 
		{

			printf("%d %d\n",bigNode->candidate, pCurrNode->candidate);
			pCurrNode = pCurrNode->pNext;
		}
		bigNode = bigNode->pNext;
	}
} /* end of bipartGraphPrint() */

