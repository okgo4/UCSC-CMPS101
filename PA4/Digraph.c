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
void dfsr(Digraph G,int w,List L)
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
Digraph rev(Digraph G)
{
    int num=getOrder(G);
    Digraph re=newDigraph(num);
    for(int i=1;i<=num;i++)
    {
        List l=getNeighbors(G,i);
        for(Node t=getFront(l);t!=NULL;t=getNextNode(t))
        {
            addEdge(re,getValue(t),i);
        }
    }
    return re;
}
int getCountSCC(Digraph G)
{
	int num=getOrder(G);
    List a[num];
	for(int j=1;j<=num;j++)
	{
			G->vis[j]=0;
            a[j]=newList();
	}
	List re=newList();
	for(int j=1;j<=num;j++)
	{
			if(G->vis[j]==0)
			{
			    dfs(G,j,re);
			}
	}
    Digraph D=rev(G);
    int count=0;
    for(Node t=getFront(re);t!=NULL;t=getNextNode(t))
    {
            if(D->vis[getValue(t)]==0)
            {
                count++;
                dfsr(D,getValue(t),a[count]);
            }
    }
    freeList(&re);
    for(int j=1;j<=num;j++)
    {
        freeList(&a[j]);
    }
    freeDigraph(&D);
    return count;

    


	
}

int getNumSCCVertices(Digraph G, int u)
{
    int num=getOrder(G);
    if(u<=0 || u>num)
    {
        return -1;
    }
    List a[num];
    for(int j=1;j<=num;j++)
    {
            G->vis[j]=0;
            a[j]=newList();
    }
    List re=newList();
    for(int j=1;j<=num;j++)
    {
            if(G->vis[j]==0)
            {
                dfs(G,j,re);
            }
    }
    Digraph D=rev(G);
    int count=0,result=0;
    for(Node t=getFront(re);t!=NULL;t=getNextNode(t))
    {
            if(D->vis[getValue(t)]==0)
            {
                count++;
                dfsr(D,getValue(t),a[count]);
            }
    }
    for(int i=1;i<=count;i++)
    {
        for(Node t=getFront(a[i]);t!=NULL;t=getNextNode(t))
        {
            if(getValue(t)==u)
            {
                result=length(a[i]);
                break;
            }
        }
    }
    freeList(&re);
    for(int j=1;j<=num;j++)
    {
        freeList(&a[j]);
    }
    freeDigraph(&D);
    return result;
}

int inSameSCC (Digraph G, int u, int v)
{
    int num=getOrder(G);
    if(u<=0 || u>num || v<=0 || v>num)
    {
        return -1;
    }
    List a[num];
    for(int j=1;j<=num;j++)
    {
            G->vis[j]=0;
            a[j]=newList();
    }
    List re=newList();
    for(int j=1;j<=num;j++)
    {
            if(G->vis[j]==0)
            {
                dfs(G,j,re);
            }
    }
    Digraph D=rev(G);
    int count=0,result1=0,result2=999,result=0;
    for(Node t=getFront(re);t!=NULL;t=getNextNode(t))
    {
            if(D->vis[getValue(t)]==0)
            {
                count++;
                dfsr(D,getValue(t),a[count]);
            }
    }
    for(int i=1;i<=count;i++)
    {
        for(Node t=getFront(a[i]);t!=NULL;t=getNextNode(t))
        {
            if(getValue(t)==u)
            {
                result1=i;
                
            }
            if(getValue(t)==v)
            {
                result2=i;
                
            }
        }
    }
    freeList(&re);
    for(int j=1;j<=num;j++)
    {
        freeList(&a[j]);
    }
    freeDigraph(&D);
    if(result1==result2)
    {
        result=1;
    }
    else
    {
        result=0;
    }
    return result;
}