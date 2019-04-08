//#Roy Wang #1636195 hwang167 PA2#
//################################ 
#include <stdio.h>
#include <string.h>
#include "Graph.h"
void PathExists (FILE *out,Graph G, int u, int v)
{
  unvisitAll (G);
  int re = PathExistsRecursive (G, u, v);
  if (re == 0)
    {
      fprintf (out,"NO\n");
    }
  else if (re == 1)
    {
      fprintf (out,"YES\n");
    }
}

int main(int argc, char* argv[])
{
	FILE *in=fopen(argv[1], "r");;
	FILE *out=fopen(argv[2], "w");;
    int n=0;
 	fscanf(in,"%d",&n);
    Graph G=newGraph(n);
    char t1=0;
    char s[600]={0};
    char sa[600]={0};
    int coun=0;
    if(n<=0)
	{
		fgets(s,200,in);
		fprintf(out,"%d%sERROR",n,s);
		fclose(in);
   		fclose(out);
		freeGraph(&G);
		return 0;
	} 
    fscanf(in,"%c",&t1);
    sa[coun]=t1;
    while(t1==',')
    {	
        int a,b;
        fscanf(in,"%c",&t1);
        coun++;
        sa[coun]=t1;
        fscanf(in,"%d%d",&a,&b);
        if(a>=10)
        {
        	coun++;
        	sa[coun]=a/10+48;
        	coun++;
        	sa[coun]=a%10+48;
		}
		else
		{
			coun++;
        	sa[coun]=a+48;
		}
        coun++;
        sa[coun]=' ';
        if(b>=10)
        {
        	coun++;
        	sa[coun]=b/10+48;
        	coun++;
        	sa[coun]=b%10+48;
		}
		else
		{
			coun++;
        	sa[coun]=b+48;
		}
		if(a>n || b>n || a<=0 || b<=0)
		{
			fgets(s,600,in);
			fprintf(out,"%d%s%sERROR",n,sa,s);
			fclose(in);
   			fclose(out);
			freeGraph(&G);
    		return 0;
		}

        addEdge(G,a,b);
        fscanf(in,"%c",&t1);
        coun++;
        sa[coun]=t1;
    	}
    	if(t1==' ')
    	{
    		fgets(s,600,in);
    		fprintf(out,"%d%s%sERROR",n,sa,s);
    		fclose(in);
   			fclose(out);
			freeGraph(&G);
    		return 0;
		}
    while(fscanf(in,"%s",s)!=EOF)
    {
        if(strcmp(s,"PrintGraph")==0)
        { 
            fprintf(out,"PrintGraph\n");
            printGraph(out,G);
            fprintf(out,"\n");
        }
        else if(strcmp(s,"GetSize")==0)
        {
            fprintf(out,"GetSize\n");
            fprintf(out,"%d\n",getSize(G));
        }
        else if(strcmp(s,"GetOrder")==0)
        {
            fprintf(out,"GetOrder\n");
            fprintf(out,"%d\n",getOrder(G));
        }
        else if(strcmp(s,"PathExists")==0)
        {
           
            int tempa=0,tempb=0;
            fscanf(in,"%c",&t1);
            fscanf(in,"%d%d",&tempa,&tempb);
            //fprintf(out,"%d %d\n",tempa,tempb);
            if(tempb==0 || tempa==0)
            {
                fprintf(out,"PathExists %d\n",tempa);
                fprintf(out,"ERROR\n");
            }
            else
            {
                fprintf(out,"PathExists %d %d\n",tempa,tempb);
                PathExists(out,G,tempa,tempb);
            }
        }
        else if(strcmp(s,"GetNeighborCount")==0)
            {
            int temp=0,re=0;
            fscanf(in,"%c",&t1);
            fscanf(in,"%d",&temp);
            re=getNeighborCount(G,temp);
            {
                fprintf(out,"GetNeighborCount %d\n",temp);
                if(re==-1)
                {
                    fprintf(out,"ERROR\n");
                }
                else
                {
                    fprintf(out,"%d\n",re);
                }
            }
            
        }
        else
        {
            fprintf(out,"%s",s);
            char c;
            fscanf(in,"%c",&c);
            if(c==32)
            {
                while(c!='\n')
                {
                    fprintf(out,"%c",c);
                    fscanf(in,"%c",&c);
                }
            }
            
            fprintf(out,"\nERROR\n");
        }
           
    
    }
	fclose(in);
   	fclose(out);
	freeGraph(&G);
    return 0;
}
