#include <stddef.h>
#include <stdio.h>
#include "bipartiteGraph.h"
#include "linkedList.h"
#include "memoryUtil.h"
#include "commonDefs.h"

#define MALE 1
#define FEMALE 2
bigList_t * choose_sex(bpGraph_t* pList, int sex);

struct implBipartGraph_t
{
	int num_males;
	int num_females;

	bigList_t * males;
	bigList_t * females;
};

/* Find a user given an integer id */
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

int find_preference(struct bigNode_t * current_user, int preference)
{
	llNode_t * current = current_user->preferences->pHead;
	while(current)
	{
		if(current->candidate == preference)
		{
			return FOUND;
		}
		current = current->pNext;
	}
	return NOT_FOUND;
}
/* Initialise user preferences */
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

/* Check preference priority of a given user */
int check_preference_priority(bpGraph_t* pGraph, struct bigNode_t * current_female, struct bigNode_t * current_male)
{
	llNode_t * current_male_preference, *current_female_preference;
	int female_priority, found;
	current_male_preference = current_male->preferences->pHead;
	current_female_preference = current_female->preferences->pHead;
	/* current_female is returning NULL when accessing candidate.... think ! */
	/*get female preference priority */
	found = 0;
	while(current_male_preference)
	{
		/* female HAS to be found otherwise found returns 0 */
		if(current_male_preference->candidate == current_female->candidate)
		{
			female_priority = current_male_preference->priority;
			found +=1;
		}
		current_male_preference = current_male_preference->pNext;
	}
	

	current_male_preference = current_male->preferences->pHead;
	while(current_male_preference)
	{
		/* return fail if top preference is taken */
		/*female doesn't exist in male table*/
		if(!found)
		{
			return NO_MATCH;
		}
		if(current_male_preference->priority > female_priority)
		{
			return MATCH;
		}
		/* point to the start of the preference LL if pointer points to current preference */
		else if(current_male_preference->priority < female_priority)
		{
			return NO_MATCH;
		}
		current_male_preference = current_male_preference->pNext;
	}
	return NO_MATCH;
}

/* Traverses through list and returns true if all female 
   status' are TAKEN */
int check_status(bpGraph_t* pGraph)
{
	struct bigNode_t * current = pGraph->females->pHead;
	while(current)
	{
		if(current->status == FREE)
		{
			return NOT_STABLE;
		}
		current = current->pNext;
	}
	return STABLE;
}

/* Adapted implementation of Gale Shapely Algorithm */
void find_stable_matching(bpGraph_t* pGraph, int max_comparisons) 
{
	struct bigNode_t * current_male, *current_female;
	llNode_t * female_preference;
	/*set to true when all male status is set to TAKEN */
	int flag = false;
	int comparison_count=0;

	while(!check_status(pGraph))
	{
		current_female = pGraph->females->pHead;
		while(current_female)
		{
		// if(current_female->status == FREE)
		// {
			female_preference = current_female->preferences->pHead;
			flag = false;
			while(!flag)
			{
				current_male = find_user(pGraph,female_preference->candidate,MALE);
				if(current_male)
				{
					if(current_female->status == FREE && current_male->status == FREE)
					{
						if(find_preference(current_male,current_female->candidate) == 1)
						{
							current_female->preferences->current_preference = current_male->candidate;
							current_male->preferences->current_preference = current_female->candidate;
							current_female->status = TAKEN;
							current_male->status = TAKEN;
							flag = true;
						}
					}
					else if(current_male->status == TAKEN)
					{
						/* ERROR IS HERE FOR TEST CASE #5*/
						if(check_preference_priority(pGraph, current_female, current_male))
						{
							struct bigNode_t * user = find_user(pGraph, current_male->preferences->current_preference,FEMALE);
							user->status = FREE;
							current_male->preferences->current_preference = current_female->candidate;
							current_female->preferences->current_preference = current_male->candidate;
							current_female->status = TAKEN;
							flag = true;
	                    }
					}
				}
				female_preference = female_preference->pNext;
				if(!female_preference)
				{
					flag = true;
				}
			}
		// }
    		current_female = current_female->pNext;
    	}
    	/* breaks if max comparisons have been reached */
    	comparison_count +=1;
    	if(comparison_count == max_comparisons*max_comparisons)
    	{
    		break;
    	}
    }
}

/* Select a bigList_t depending on input sex */
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

/* Initialise graph */
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
	
} 

/* Free graph */
void bipartGraphDestroy(bpGraph_t* pGraph)
{
	/* TODO: Implement me! */
} /* end of bipartGraphDestroy() */

/*Print graph */
void print_graph(bpGraph_t *pGraph)
{
	struct bigNode_t * current = pGraph->males->pHead;
	while(current)
	{	
		if(current->status == TAKEN)
		{
			printf("%d %d\n", current->candidate, current->preferences->current_preference);
		}
		current = current->pNext;
	}
} 

