#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "graph_mat.h"
#include "graph_list.h"
#include "bron_kerbosch.h"
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

int main()
{
	/*
	GraphM *adjMat = parseMtxFile(".//data//soc-dolphins.mtx");
	assert(adjMat);

	GraphL *g = newGraphL(adjMat);
	*/

	GraphL *g = (GraphL *) calloc(1, sizeof(GraphL));
	g->numVerts = 5;
	g->vertexList = (Vertex *) calloc(g->numVerts, sizeof(Vertex));

	assert(g);
	assert(g->vertexList);

	for(int i = 0; i < g->numVerts;i++)
	{
		g->vertexList[i].index = i;
	}
	
	addEdgeL(g, 0, 1);
	addEdgeL(g, 0, 2);
	addEdgeL(g, 1, 2);
	addEdgeL(g, 2, 3);

	assert(g);
	
	uint32_t *R = NULL;
	arrsetlen(R, 0);
	uint32_t *P = NULL;
	arrsetlen(P, 0);
	uint32_t *X = NULL;
	arrsetlen(X, 0);
	
	for(uint32_t i = 0; i < g->numVerts; i++)
	{
		arrput(P, i);
	}
	
	uint32_t **maximalCliques = NULL;

	bk(R, P, X, g, maximalCliques);
	
	printf("Number of Maximal Cliques: %ld\n",arrlen(maximalCliques));

	printMaximalCliques(maximalCliques);

	arrfree(R);
	arrfree(P);
	arrfree(X);
	
	deleteGraphL(g);
}