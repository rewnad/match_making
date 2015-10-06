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

    if(!fp)
    {
        printf("Error! Can't open file. \n");
        return 1;
    }

	char line[256];
    while (fgets(line, sizeof(line), fp)) {
        /* note that fgets don't strip the terminating \n, checking its
           presence would allow to handle lines longer that sizeof(line) */
        printf("%s", line); 
    }



    printf("\n File opened successfully through fopen()\n");


    fclose(fp);

    printf("\n File stream closed through fclose()\n");

    return 0;
}