//
//  ListClient.c
//  
//
//  Created by Jayanth Yetukuri on 1/21/19.
// Email me(jyetukur@ucsc.edu) if you have any concerns on this file
//

#include<stdio.h>
#include<stdlib.h>
#include"List.h"

int main(int argc, char* argv[]){
    FILE* in=fopen(argv[1], "r");
    FILE* out=fopen(argv[2], "w");
    List A[20];
    for(int j=0;j<20;j++)
    {
    	A[j]=newList();
	}
    int temp,i=0;
    char temps;
    while(fscanf(in,"%d",&temp)!=EOF)
	{
    	
		append(A[i],temp);
		fscanf(in,"%c",&temps);
		if(temps!=32)
		{
			i++;
		}
		
	}
	for(int q=0;q<=i;q++)
	{
	    int ma=length(A[q]);
		for(int m=2;m<=ma;m++)
		{
		    int n=m-1;
		    int val=getValue(getnumNode(A[q],m));
		    while(n>0 && val<getValue(getnumNode(A[q],n)))
		    {
		        n--;
		    }
		    if(n==0)
		    {
		        prepend(A[q],val);
		        deleten(A[q],getnumNode(A[q],m+1));
		    }
		    else
		    {
		        insertAfter(A[q],getnumNode(A[q],n),val);
		         deleten(A[q],getnumNode(A[q],m+1));
		    }
		    
		}
	
	}
	
	for(int v=0;v<=i;v++)
	{
		printList(out,A[v]);
		fprintf(out,"\n");
	}
	for(int q=0;q<20;q++)
		freeList(&A[q]);
   	fclose(in);
   	fclose(out);
    
    return(0);
}
