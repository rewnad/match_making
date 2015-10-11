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

#define MALE 1
#define FEMALE 2
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

struct bigNode_t * find_user(bpGraph_t* pGraph, int candidate, int sex)
{
	bigList_t * group = choose_sex(pGraph,sex);
	struct bigNode_t * current;

	current = group->pHead;
	while(current)
	{
		if(current->candidate == candidate)
		{
			return current;
		}
		current = current->pNext;
	}
	return NULL;
}

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


int check_preference_priority(bpGraph_t* pGraph, int current_female, struct bigNode_t * current_male)
{
	llNode_t * current_male_preference = current_male->preferences->pHead;
	while(current_male_preference)
	{
		/* return fail if top preference is taken */

		if(current_male_preference->candidate == current_female)
		{
			return MATCH;
		}
		/* point to the start of the preference LL if pointer points to current preference */
		if(current_male_preference->candidate == current_male->preferences->current_preference)
		{
			return NO_MATCH;
		}
		current_male_preference = current_male_preference->pNext;
	}

	return NO_MATCH;
}

void update_status(bpGraph_t* pGraph, int current_user, int status, int sex)
{
	struct bigNode_t * user = find_user(pGraph, current_user,sex);
	if(status == FREE)
	{
		user->status = FREE;
		user->preferences->current_preference = 0;
	}
}
int find_stable_matching(bpGraph_t* pGraph) 
{
	struct bigNode_t * current_male, *current_female;
	llNode_t * female_preference;
	/*set to true when all male status is set to TAKEN */
	int flag = false;

	// current_male = pGraph->males->pHead;
	current_female = pGraph->females->pHead;

	while(!flag)
	{
		while(current_female)
		{
			female_preference = current_female->preferences->pHead;
			for(int i = 0; i < pGraph->num_males; i++)
			{
				/* check if female is FREE */
				/* if not free, check female current preference + 1 using priority */
				/* if current_preference != priority preference + 1 */
				/* check priority preference + 2 until priority_preference */
				current_male = find_user(pGraph,female_preference->candidate,MALE);
				if(!current_male)
				{
					return NOT_FOUND;
				}
				else 
				{
					if(current_male->status == FREE)
					{
						current_female->preferences->current_preference = current_male->candidate;
						current_male->preferences->current_preference = current_female->candidate;
						current_female->status = TAKEN;
						current_male->status = TAKEN;
					}
					else if(current_male->status == TAKEN)
					{
						/* TODO: taken algorithm */
						if(check_preference_priority(pGraph, current_female->candidate, current_male))
						{
							current_male->preferences->current_preference = current_female->candidate;
							current_female->preferences->current_preference = current_male->candidate;
                            update_status(pGraph,current_male->preferences->current_preference, FREE, MALE);
                        }
    				}
    			}
    		}
    	}
    }
    return 0;
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

