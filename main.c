#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

#include "bipartiteGraph.h"
#include "commonDefs.h"
int main(int argc, char *argv[])
{
    FILE* fp;
    char const* const fName = argv[1];
    fp = fopen(fName,"r");
    int males,females;
    bpGraph_t *pGraph = NULL;    

    /* Arg error handling */
    if(argc != 2)
    {
        printf("Error! Incorrect number of inputs. \n");
        return 1;    	
    }
    /* File error handling */
    if(!fp)
    {
        printf("Error! Can't open file. \n");
        return 1;
    }

	char line[256];
	const char delim[2] = " ";
	char *token;

	/* Count used to get # males and females from  the
	   first line of file 
	 */
	int count = 0, sex = MALE;
    while (fgets(line, sizeof(line), fp))
    {
        char * ptr;
        if(count == 0)
        {
            /* get number of males and females */
            token = strtok(line, delim);
            males = strtol(token,&ptr,10);
            token = strtok(NULL, delim);    
            females = strtol(token,&ptr,10);        
            pGraph = bipartGraphCreate(males, females);
            /* ERROR HANDLE
                if males != females 
                < do something >
                */
        }    
    	if(count > 0)
    	{
            int user,preference;            
	    	/* get id */
	   		token = strtok(line, delim);
            user = strtol(token,&ptr,10);
            token = strtok(NULL, delim);

	   		while(token)
	   		{
	   			/* user preferences */
                preference = strtol(token,&ptr,10);
                add_preferences_to_user(pGraph,user,preference,sex);
		        token = strtok(NULL, delim);
   			}
        }
        /* sex doesn't matter for male == female */
        count++;
        if (count > males)
        {
            sex = FEMALE;
        }
    }
    printf("File opened successfully through fopen()\n");
    bipartGraphPrint(pGraph);

    fclose(fp);

    printf("File stream closed through fclose()\n");

    return 0;
}