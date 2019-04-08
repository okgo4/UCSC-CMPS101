/**
 * Author: Abhishek Alfred Singh
 * Email:  abasingh@ucsc.edu
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include "Digraph.h"
char *parseVertex(char *buffer, int *numOfVertices);

int parseEdges(char *buf, Digraph g);

void getIntsBetween(char *buf, char *tmp, int *u, int *v);

char *getNumber(const char *buffer, int *numOfVertices, char **found);

FILE *openFileOrExitOnFailure(char *filename, char *mode);


int main(int argc, char **argv) {
   if (argc != 3) {
      exit(EXIT_FAILURE);
   }
    char *infileName = argv[1];
    char *outfileName = argv[2];
    FILE *in = openFileOrExitOnFailure(infileName, "r");
    FILE *out = openFileOrExitOnFailure(outfileName, "w");

    int n = 2000; // large graph. You may even allocate 1000000 bytes to read a line. But for PA3, line length will be restricted to 1000 bytes.
    char *buffer = calloc(n, 1);  
    fgets(buffer,n,in); // Alternatively, instead of fgets() you can use getline() on Linux machines only as: char *buffer; int n; getline(&buffer, &n, in);

    // Setup graph data.
    int vcount=0;
    char* restOfTheBuffer = parseVertex(buffer, &vcount);
    Digraph g=newDigraph(vcount);
    int result=parseEdges(restOfTheBuffer+1,g);
	if(result==0)
	{
		fprintf(out,"%s",buffer);
		fprintf(out,"ERROR\n");
		freeDigraph(&g);
    free(g);
    free(buffer);
	fclose(in);
	fclose(out);
		return 0;
	}
	

    // Read next set of lines and perform actions
    while(fgets(buffer,n,in)!=NULL) {
        fprintf(out,"%s",buffer);
        if(strcmp(buffer,"GetOrder\n")==0)
        {
        	fprintf(out,"%d\n",getOrder(g));
		}
		else if(strcmp(buffer,"GetSize\n")==0)
		{
			fprintf(out,"%d\n",getSize(g));
		}
		else if(strcmp(buffer,"PrintDigraph\n")==0)
		{
			printDigraph(out,g);
		}
		else if(strcmp(buffer,"Acyclic\n")==0)
		{
			acyclic(out, g);
		}
		else if(strcmp(buffer,"TopoSort\n")==0)
		{
			topoSort(out,g);
		}
		else
		{
			char parts[10][50]; 
            int sume=0,t=0;
            int i=0;
            while(buffer[i]!=0)
            {
    	        if(buffer[i]==' ')
    	         {
    	            parts[sume][t]=0;
    		        sume++;
    		        t=0;
		        }
		        else
		        {
			        parts[sume][t]=buffer[i];
			        t++; 
		        }
    	        i++;
	        }
	        ////////////////////////////////////////
	        if(strcmp(parts[0],"GetOutDegree")==0)
	        {
	            if(sume!=1)
	            {
	                fprintf(out,"ERROR\n");
	            }
	            else
	            {
	                int a=(int) strtol(parts[1], (char **)NULL, 10);
	                if(a<=0 || a>getOrder(g))
	                {
	                    fprintf(out,"ERROR\n");
	                }
	                else
	                {
	                    fprintf(out,"%d\n",length(getNeighbors(g,a)));
	                }
	                
	            }
	        }
	        /////////////////////////////////////
	        else if(strcmp(parts[0],"AddEdge")==0)
	        {
	            if(sume!=2)
	            {
	                fprintf(out,"ERROR\n");
	            }
	            else
	            {
	                int a=(int) strtol(parts[1], (char **)NULL, 10);
	                int b=(int) strtol(parts[2], (char **)NULL, 10);
	                if(a<=0 || a>getOrder(g) || b<=0 || b>getOrder(g))
	                {
	                    fprintf(out,"ERROR\n");
	                }
	                else
	                {
	                    fprintf(out,"%d\n",addEdge(g,a,b));
	                }
	                
	            }
	        }
	        /////////////////////////////////////
	        else if(strcmp(parts[0],"DeleteEdge")==0)
	        {
	            if(sume!=2)
	            {
	                fprintf(out,"ERROR\n");
	            }
	            else
	            {
	                int a=(int) strtol(parts[1], (char **)NULL, 10);
	                int b=(int) strtol(parts[2], (char **)NULL, 10);
	                if(a<=0 || a>getOrder(g) || b<=0 || b>getOrder(g))
	                {
	                    fprintf(out,"ERROR\n");
	                }
	                else
	                {
	                    fprintf(out,"%d\n",deleteEdge(g,a,b));
	                }
	                
	            }
	        }
	        //////////////////////////////////////
	        else if(strcmp(parts[0],"Distance")==0)
	        {
	            if(sume!=2)
	            {
	                fprintf(out,"ERROR\n");
	            }
	            else
	            {
	                int a=(int) strtol(parts[1], (char **)NULL, 10);
	                int b=(int) strtol(parts[2], (char **)NULL, 10);
	                if(a<=0 || a>getOrder(g) || b<=0 || b>getOrder(g))
	                {
	                    fprintf(out,"ERROR\n");
	                }
	                else
	                {
	                    distance(out,g,a,b);
	                }
	                
	            }
	        }
	        else
	        {
	            fprintf(out,"ERROR\n");
	        }
	    //
	    //int b=(int) strtol(parts[2], (char **)NULL, 10);
		}
    }

    // Free all allocated data.
    freeDigraph(&g);
    //free(g);
    free(buffer);
	fclose(in);
fclose(out);
    return 0;
}

FILE *openFileOrExitOnFailure(char *filename, char *mode) {
    FILE *in = fopen(filename, mode);
    if (in == NULL) {
        fprintf(stderr,"unable to open file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    return in;
}

int parseEdges(char *buf, Digraph g) {
    char* tmp=buf;
    char* start=buf;
    int u,v,n;
    n=getOrder(g);
    while (tmp!=NULL) {
        tmp = strchr(start, ',');
        getIntsBetween(start,tmp,&u,&v);
        if(u>n || v>n || n<=0)
        {
        	return 0;
		}
        addEdge(g,u,v);
        start=tmp+1;
    }
	return 1;
}

void getIntsBetween(char *buf, char *tmp, int *u, int *v) {
    while (*buf == ' ')
        buf++;
    char* found = strchr(buf,' ');
    getNumber(buf,u,&found);
    getNumber(found,v,&tmp);
}

char *parseVertex(char *buffer, int *numOfVertices) {
    char* found = strchr(buffer,',');
    return getNumber(buffer, numOfVertices, &found);
}

char *getNumber(const char *buffer, int *numOfVertices, char **found) {
    errno =0;
    *numOfVertices = (int) strtol(buffer, found, 10);
    if (errno == ERANGE) {
        *numOfVertices=-1;
        (*found) =NULL;
        fprintf(stderr,"Error occurred while parsing vertex.");
        exit(EXIT_FAILURE);
    }
    return (*found);
}



