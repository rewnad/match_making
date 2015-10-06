#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>

/* #include "bipartiteGraph.h"
 #include "commonDefs.h"
*/
int main(int argc, char *argv[])
{
    FILE* fp;
    char const* const fName = argv[1];
    fp = fopen(fName,"r");
    int males,females;

    if(argc != 2)
    {
        printf("Error! Incorrect number of inputs. \n");
        return 1;    	
    }
    if(!fp)
    {
        printf("Error! Can't open file. \n");
        return 1;
    }

	char line[256];
	const char delim[2] = " ";
	char *token;

	/* used to do get # males and females from  the
	   first line of file 
	 */
	char count = 0;
    while (fgets(line, sizeof(line), fp))
    {
    	if(count != 0)
    	{
	    	/* get id */
	   		token = strtok(line, delim);
	   		printf("Id: %s\n", token);
	   		token = strtok(NULL, delim);

	   		while(token)
	   		{
	   			/* user preferences */
	      		printf( "Preference: %s\n", token);
		        token = strtok(NULL, delim);
   			}
    	}
    	else
    	{
    		/* get number of males and females */
    		char * ptr;
			token = strtok(line, delim);
			males = strtol(token,&ptr,10);
	   		printf("# of males: %d\n", males);
	   		token = strtok(NULL, delim);    
	   		females = strtol(token,&ptr,10);		
	   		printf("# of females: %d\n", females);
    		count+=1;

    		/* ERROR HANDLE
    			if males != females 
    			< do something >
    			*/
    	}

        // printf("%s", line); 
    }



    printf("File opened successfully through fopen()\n");


    fclose(fp);

    printf("File stream closed through fclose()\n");

    return 0;
}