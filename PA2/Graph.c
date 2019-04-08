//#Roy Wang #1636195 hwang167 PA2#
//################################

#include <stdlib.h>
#include<assert.h>
#include "Graph.h"

struct GraphObj {
    int numv;
    int nume;
    List adj[101];
    int vis[101];
};

Graph newGraph(int num)
{
    Graph G = (Graph) calloc(128,sizeof(Graph));
    G->numv=num;
    G->nume=0;
    for(int i=1;i<=num;i++)
    {
        G->adj[i]=newList();
        G->vis[i]=0;
    }
    return G;
}


void freeGraph(Graph *pG)
{
    	if( pG!=NULL && *pG!=NULL ){
		for(int i=1;i<=getOrder(*pG);i++)
        {
            List t=getNeighbors(*pG,i);
            freeList(&t);
        }
      	free(*pG);
      	*pG = NULL;
   }
   
}

int getOrder(Graph G)
{
    return G->numv;
}

int getSize(Graph G)
{
    return G->nume;
}

int getNeighborCount(Graph G, int v)
{
    if(G->adj[v]==NULL)
    {
        return -1;
    }
    else
    {
        return length(G->adj[v]);
    }
}

List getNeighbors(Graph G, int v)
{
    return G->adj[v];
}

int addEdge(Graph G, int u, int v)
{
    if(u<=G->numv && v<=G->numv)
    {
        Node t1=getFront(getNeighbors(G,u));
        while(t1!=NULL)
        {
            if(getValue(t1)==v)
            {
                return 0;
            }
            t1=getNextNode(t1);
        }
        
            append(getNeighbors(G, u),v);
            append(getNeighbors(G, v),u);
            G->nume++;
            return 0;
    }
    return -1;
}

void unvisitAll(Graph G)
{
    for(int i=1;i<=G->numv;i++)
    {
        G->vis[i]=0;
    }
}

int getMark(Graph G, int u)
{
    
     return G->vis[u];
}

void setMark(Graph G, int u, int theMark)
{
    G->vis[u]=theMark;
}

int PathExistsRecursive(Graph G, int w, int v)
{
    if(w==v)
    {
        return 1;
    }
    setMark(G,w,1);
    
    Node temp=getFront(getNeighbors(G,w));
    while(temp!=NULL)
    {
        int theMark = getMark(G,getValue(temp));
        int theFoundValue=0;
        if(theMark==0 && getValue(temp)!=0)
        {
            theFoundValue = PathExistsRecursive(G,getValue(temp),v);
        }
        if(theFoundValue==1)
        {
            return(1);
        }
        temp=getNextNode(temp);
    }
   
    setMark(G,w,2);
    return(0);
}

void printGraph( FILE* out,Graph G)
{
    Node N;
    fprintf(out,"%d",getOrder(G));
    for(int i=1;i<=G->numv;i++)
    {
        N=getFront(G->adj[i]);
       
        while(N!=NULL)
        {   
            
            if(getValue(N)>i && getValue(N)<=getOrder(G))
            {
                fprintf(out,", %d %d",i,getValue(N));
            }
            N=getNextNode(N);
           
            
        }
    }
}
