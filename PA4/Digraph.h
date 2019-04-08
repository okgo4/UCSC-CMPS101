#ifndef DIGRAPH_H_CMPS101
#define DIGRAPH_H_CMPS101

#include <stdio.h>
#include "List.h"
struct DigraphObj {
    int numv;
    int nume;
    List adj[20000];
    int vis[20000];
};

// private Node type
typedef struct DigraphObj *Digraph;


/*** Constructors-Destructors ***/
Digraph newDigraph(int numVertices);
// Returns a Digraph that points to a newly created DigraphObj representing a digraph which has
// n vertices and no edges.
void freeDigraph(Digraph* pG);
// Frees all dynamic memory associated with its Digraph* argument, and sets
// *pG to NULL.
/*** Access functions ***/
int getOrder(Digraph G);
// Returns the order of G, the number of vertices in G.
int getSize(Digraph G);
// Returns the size of G, the number of edges in G.
int getOutDegree(Digraph G, int u);
// Returns the number of outgoing neighbors that vertex u has in G, the number of vertices v such
// that (u, v) is an edge in G. Returns -1 if v is not a legal vertex.
List getNeighbors(Digraph G, int u);
// Returns a list that has all the vertices that are outgoing neighbors of vertex u, i.e.,
// a list that has all the vertices v such that (u, v) is an edge in G.
// There is no input operation that corresponds to getNeighbors.
/*** Manipulation procedures ***/
int addEdge(Digraph G, int u, int v);
// Adds v to the adjacency list of u, if that edge doesnbt already exist.
// If the edge does already exist, does nothing. Used when edges are entered or added.
// Returns 0 if (u, v) is a legal edge, and the edge didnbt already exist.
// Returns 1 if (u, v) is a legal edge and the edge did already exist.
// Returns -1 if (u, v) is not a legal edge.
int deleteEdge(Digraph G, int u, int v);
// Deletes v from the adjacency list of u, if that edge exists.
// If the edge doesnbt exist, does nothing. Used when edges are deleted.
// Returns 0 if (u, v) is a legal edge, and the edge did already exist.
// Returns 1 if (u, v) is a legal edge and the edge didnbt already exist.
// Returns -1 if (u, v) is not a legal edge.

/*** Other operations ***/
void printDigraph(FILE* out,Digraph G);
// Outputs the digraph G in the same format as an input line, including the number of vertices
// and the edges. The edges should be in sorted order, as described above.

int getCountSCC(Digraph G);

int getNumSCCVertices(Digraph G, int u);

int inSameSCC (Digraph G, int u, int v);

#endif
