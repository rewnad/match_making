/*
 * bipartiteGraph.h
 *
 *  Created on: 01/07/2015
 *      Author: jkct440
 */

#ifndef BIpartiteGRAPH_H_
#define BIpartiteGRAPH_H_


/* Forward declaration.  Actual definition is up to each individual data structure implementation. */
typedef struct implBipartGraph_t bpGraph_t;







/* ******************************************************************************************* */
/* Functions declarations for the bipartite graph abstract data type, that you will implement the definitions of in the source files. */


/*
 * Creates a bipartite graph with 'vertNumPart1' number of vertices in partite 1 and 'vertNumPart2' number of vertices in partite 2.
 *
 * vertNumPart1 - Number of vertices in partite 1.
 * vertNumPart1 - Number of vertices in partite 2.
 *
 * returns - pointer to newly created graph (or NULL if operation failed).
 */


extern
void add_preferences_to_user(bpGraph_t* pGraph, int user,int preference,int sex);

extern
int find_stable_matching(bpGraph_t* pGraph);

extern
struct bigNode_t * find_user(bpGraph_t* pGraph, int candidate, int sex);

extern
int check_preference_priority(bpGraph_t* pGraph, struct bigNode_t * current_female, struct bigNode_t * current_male);

extern
bpGraph_t* bipartGraphCreate(int num_males, int num_females);

extern 
int check_status(bpGraph_t* pGraph);

/*
 * Destroys bipartite graph 'pGraph'.
 *
 * pGraph - pointer to bipartite graph.
 */
extern
void bipartGraphDestroy(bpGraph_t *pGraph);

/*
 * Prints to stdout the contents of the bipartite graph 'pGraph'.
 *
 * pGraph - pointer to bipartite graph.
 *
 * returns - status code whether vertex was successfully printed or not.
 */
extern
void print_graph(bpGraph_t *pGraph);



#endif /* BIpartiteGRAPH_H_ */
