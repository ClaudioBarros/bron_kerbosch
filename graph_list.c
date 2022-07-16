#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "stb_ds.h"
#include "graph_mat.h"
#include "graph_list.h"


GraphL *newGraphL(GraphM *adjMat)
{	
	assert(adjMat != NULL);
	assert(adjMat->edges != NULL);
	assert(adjMat->isDirected == false);
	
	GraphL *g = malloc(sizeof(GraphL));

	if(!g)
	{
		return NULL;
	}

	g->numVerts = adjMat->numVerts;	
	g->vertexList = (Vertex *) calloc(adjMat->numVerts, sizeof(Vertex));
	assert(g->vertexList);

	for(int i = 0; i < adjMat->numVerts; i++)
	{
		g->vertexList[i].index = i;
		for(int j = 0; j < adjMat->numVerts; j++)	
		{
			if(hasEdgeM(adjMat, i, j))
			{
				addEdgeL(g, i, j);
			}
		}
	}
	
	return g;
}

void deleteGraphL(GraphL *g)
{
	if(!g->vertexList)
	{
		return;
	}
	
	Vertex *temp, *ptr;
	for (int i = 0; i < g->numVerts; i++)
	{
		ptr = &g->vertexList[i];
		while(ptr != NULL)
		{
			temp = ptr;
			ptr = ptr->next;
			if(temp)
			{
				free(temp);
			}
		}
		free(&(g->vertexList[i]));
	}
}

bool addEdgeToVertex(Vertex *v, uint32_t vertToAdd)
{
	assert(v);
	
	Vertex *ptr = v;
	
	while(ptr)
	{
		if(!ptr->next)
		{
			ptr->next = (Vertex *) calloc(1, sizeof(Vertex));
			if(ptr->next == NULL)
			{
				return false;
			}
			ptr->next->index = vertToAdd;
			ptr->next->next = NULL;
			
			break;
		}
		
		ptr = ptr->next;
	}
	
	return true;
}

bool addEdgeL(GraphL *g, uint32_t v1, uint32_t v2)
{
	assert(g != NULL);
	assert(v1 < g->numVerts);
	assert(v2 < g->numVerts);

	if(hasEdgeL(g, v1, v2)) 
	{
		return false;
	}

	return  addEdgeToVertex(&g->vertexList[v1], v2) && 
	        addEdgeToVertex(&g->vertexList[v2], v1);
	
	//TODO: if malloc for v2 fails, but it succeeds for v1,
	//then cleanup newly allocated vertex for v1
	//before returning false
}

bool hasEdgeL(GraphL *g, uint32_t v1, uint32_t v2)
{
	assert(g);
	assert(g->vertexList);
	assert(v1 < g->numVerts);
	assert(v2 < g->numVerts);
	
	Vertex *ptr = &g->vertexList[v1];

	if(!ptr->next)
	{
		return false;
	}

	ptr = ptr->next;
	while(1)
	{
		if(ptr->index == v2)
		{
			return true;
		}

		if(!ptr->next)	
		{
			break;
		}
		ptr = ptr->next;
	}
	return false;
}

uint32_t *getVertexNeighbors(GraphL *g, uint32_t vertIndex)
{
	assert(g != NULL);
	
	uint32_t *neighborList = NULL;
	
	Vertex *vertexPtr = &g->vertexList[vertIndex];;
	if(!vertexPtr)
	{
		return neighborList;
	}

	vertexPtr = vertexPtr->next;
	while(vertexPtr)
	{
		//skip the first index, since it refers to the vertex that we
		//want to get the neighbors of 
		arrput(neighborList, vertexPtr->index);
		vertexPtr = vertexPtr->next;
	}
	
	return neighborList;
}