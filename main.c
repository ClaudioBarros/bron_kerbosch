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
	GraphM *adjMat = parseMtxFile(".//data//soc-dolphins.mtx");
	assert(adjMat);

	GraphL *g = newGraphL(adjMat);

	assert(g);
	assert(g->vertexList);

	
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
	
	//printf("Number of Maximal Cliques: %ld\n",arrlen(maximalCliques));

	//printMaximalCliques(maximalCliques);

	arrfree(R);
	arrfree(P);
	arrfree(X);
	
	deleteGraphL(g);
}