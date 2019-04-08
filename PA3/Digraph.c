#include <stdlib.h>
#include "Digraph.h"

Digraph newDigraph(int numVertices)
{
    const size_t size = sizeof(struct DigraphObj);
    Digraph G = (struct DigraphObj *) calloc(1024,size);
    G->numv=numVertices;
    G->nume=0;
    for(int i=1;i<=numVertices;i++)
    {
        G->adj[i]=newList();
        G->vis[i]=0;
    }
    return G;
}

void freeDigraph(Digraph* pG)
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

int getOrder(Digraph G)
{
    return G->numv;
}

int getSize(Digraph G)
{
    return G->nume;
}

int getOutDegree(Digraph G, int u)
{
    if(u<=G->numv)
    {
        List temp=getNeighbors(G,u);
        return length(temp);
    }
    return -1;
}

List getNeighbors(Digraph G, int u)
{
    if(u<=G->numv)
    {
        return G->adj[u];
    }
    return NULL;
}

int addEdge(Digraph G, int u, int v)
{
    if(u<=G->numv && v<=G->numv)
    {
        Node temp=getFront(getNeighbors(G,u));
        while(temp!=NULL)
        {
            if(getValue(temp)==v)
            {
                return 1;
            }
            temp=getNextNode(temp);
        }
        temp=getFront(getNeighbors(G,u));
        while(getValue(temp)<v && temp!=NULL)
        {
            temp=getNextNode(temp);
        }
        if(temp==NULL)
        {
            append(getNeighbors(G,u),v);
            G->nume++;
        }
        else
        {
            insertBefore(getNeighbors(G,u), temp, v);
            G->nume++;
        }
        return 0;
    }
    return -1;
}

int deleteEdge(Digraph G, int u, int v)
{
    if(u<=G->numv && v<=G->numv)
    {
        Node temp=getFront(getNeighbors(G,u));
        while(temp!=NULL)
        {
            if(getValue(temp)==v)
            {
            	deleteNode(getNeighbors(G,u),temp); 
		G->nume--;
                return 0;
            }
            temp=getNextNode(temp);
        }
        return 1;
    }
    return -1;
}
//////
void printDigraph(FILE* out,Digraph G)
{
	fprintf(out,"%d",getOrder(G));
	for(int i=1;i<=getOrder(G);i++)
	{
		Node temp=getFront(getNeighbors(G,i));
		while(temp!=NULL)
		{
			fprintf(out,", %d %d",i,getValue(temp));
			temp=getNextNode(temp);
		}
	}
	fprintf(out,"\n");
}
//////
////
void distance(FILE* out,Digraph G, int u, int v)
{
	int num=getOrder(G); 
	if(u==v && u<=num)
	{
		fprintf(out,"0\n");
		return;
	}
	List a[num+1];
	for(int j=0;j<=num;j++)
	{
		G->vis[j]=0;
		a[j]=newList(); 
	}
	append(a[0],u);
	int max=999;
	for(int i=0;i<num;i++)
	{
		for(Node t=getFront(a[i]);t!=NULL;t=getNextNode(t))
		{
			for(Node temp=getFront(getNeighbors(G,getValue(t)));temp!=NULL;temp=getNextNode(temp))
			{
				if(G->vis[getValue(temp)]==0)
				{
					G->vis[getValue(temp)]=1;
					if(getValue(temp)==v)
					{
						if(max>=i+1)
						{
						    max=i+1;
						}
					}
					append(a[i+1],getValue(temp));
					
				}
			}
		}
	}
	for(int j=0;j<=num;j++)
	{
		freeList(&a[j]); 
	}	
	if(max!=999)
	{
	    fprintf(out,"%d\n",max);
	}
	else
	{
	    fprintf(out,"INF\n");
	}
}

/////
void acyclic(FILE* out,Digraph G)
{
	int num=getOrder(G); 
	List a[num+1];
	for(int i=0;i<=num;i++)
	{
		a[i]=newList(); 
	}
	for(int u=1;u<=getOrder(G);u++)
	{	
	
		for(int j=1;j<=num;j++)
		{
			G->vis[j]=0;
		}
	    for(int i=0;i<=num;i++)
	    {
		    clear(a[i]); 
	    }
		int v=u;
		append(a[0],u);
		for(int i=0;i<num;i++)
		{
			for(Node t=getFront(a[i]);t!=NULL;t=getNextNode(t))
			{
				for(Node temp=getFront(getNeighbors(G,getValue(t)));temp!=NULL;temp=getNextNode(temp))
				{
					if(G->vis[getValue(temp)]==0)
					{
						G->vis[getValue(temp)]=1;
						append(a[i+1],getValue(temp));
						if(getValue(temp)==v)
						{
							fprintf(out,"NO\n");
							for(int j=0;j<=num;j++)
							{
								freeList(&a[j]); 
							}	
							return;
						}
					}
				}
			}
		}
			
		
	}
	for(int j=0;j<=num;j++)
		{
			freeList(&a[j]); 
		}
	fprintf(out,"YES\n");
}

void dfs(Digraph G,int w,List L)
{
    G->vis[w]=1;
    for(Node t=getFront(getNeighbors(G,w));t!=NULL;t=getNextNode(t))
    {
        if(G->vis[getValue(t)]==0)
        {
            
            dfs(G,getValue(t),L);
        }
    }
    G->vis[w]=2;
    prepend(L,w);
}
/////

void topoSort(FILE* out,Digraph G)
{
	int num=getOrder(G);
	List a[num+1];
	for(int i=0;i<=num;i++)
	{
		a[i]=newList(); 
	}
	for(int u=1;u<=getOrder(G);u++)
	{	
	
		for(int j=1;j<=num;j++)
		{
			G->vis[j]=0;
		}
	    for(int i=0;i<=num;i++)
	    {
		    clear(a[i]); 
	    }
		int v=u;
		append(a[0],u);
		for(int i=0;i<num;i++)
		{
			for(Node t=getFront(a[i]);t!=NULL;t=getNextNode(t))
			{
				for(Node temp=getFront(getNeighbors(G,getValue(t)));temp!=NULL;temp=getNextNode(temp))
				{
					if(G->vis[getValue(temp)]==0)
					{
						G->vis[getValue(temp)]=1;
						append(a[i+1],getValue(temp));
						if(getValue(temp)==v)
						{
							fprintf(out,"IMPOSSIBLE\n");
							for(int j=0;j<=num;j++)
							{
								freeList(&a[j]); 
							}	
							return;
						}
					}
				}
			}
		}
			
		
	}
	for(int j=0;j<=num;j++)
							{
								freeList(&a[j]); 
							}	
	for(int j=1;j<=num;j++)
	{
			G->vis[j]=0;
	}
	List re=newList();
	for(int j=1;j<=num;j++)
	{
			if(G->vis[j]==0)
			{
			    dfs(G,j,re);
			}
	}
	printList(out,re);
	freeList(&re);
}
