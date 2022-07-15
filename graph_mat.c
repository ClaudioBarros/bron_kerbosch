#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "graph_mat.h"

GraphM *newGraphM(uint32_t numVerts, bool isDirected)
{
	GraphM *g = (GraphM*) malloc(sizeof(*g));
	if(g == NULL)
	{
		return NULL;	
	}

	g->numVerts = numVerts;
	g->isDirected = isDirected;
	g->edges = (bool **) calloc(sizeof(bool*), g->numVerts);
	if(g->edges == NULL)
	{
		//cleanup//
		free(g);
		return NULL;	
	}
	
	for (int i = 0; i < g->numVerts; i++)
	{
		g->edges[i] = (bool *) calloc(sizeof(bool), g->numVerts);
		if (g->edges[i] == NULL)
		{
			//cleanup
			deleteGraphM(g);
			return NULL;
		}
	}
	
	return g;
}

void deleteGraphM(GraphM *g)
{
	if(g->edges == NULL)
	{
		free(g);
		return;
	}
	for(int i = 0; i < g->numVerts; i++)
	{
		if(g->edges[i] != NULL)	
		{
			free(g->edges[i]);
		}
	}
	free(g->edges);	
	free(g);
	
	return;
}

bool addEdgeM(GraphM *g, uint32_t v1, uint32_t v2)
{
	assert(g != NULL);
	assert(v1 < g->numVerts);
	assert(v2 < g->numVerts);

	if(hasEdgeM(g, v1, v2)) {return false;}
	
	g->edges[v1][v2] = true;
	if(g->isDirected)
	{
		g->edges[v2][v1] = true;
	}
	return true;
}

bool hasEdgeM(GraphM *g, uint32_t v1, uint32_t v2)
{
	assert(g != NULL);
	assert(v1 < g->numVerts);
	assert(v2 < g->numVerts);
	
	if(g->edges[v1][v2] == true)
	{
		return true;
	}
	return false;
}

