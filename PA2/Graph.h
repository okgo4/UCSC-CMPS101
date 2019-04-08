//#Roy Wang #1636195 hwang167 PA2#
//################################ 
#ifndef GRAPH_H_CMPS101
#define GRAPH_H_CMPS101
#include <stdio.h>
#include "List.h"
typedef struct GraphObj *Graph;


Graph newGraph(int num);

void freeGraph(Graph *pG); 

int getOrder(Graph G);

int getSize(Graph G);

int getNeighborCount(Graph G, int v);

List getNeighbors(Graph G, int v);

int addEdge(Graph G, int u, int v);

void unvisitAll(Graph G);

int getMark(Graph G, int u);

void setMark(Graph G, int u, int theMark);

int PathExistsRecursive(Graph G, int w, int v);

void printGraph(FILE* out, Graph G);
//void printGraph(Graph G);
#endif
