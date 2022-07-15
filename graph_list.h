#ifndef GRAPH_LIST_H
#define GRAPH_LIST_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

//undirected graph using adjacency list

struct GraphM;

typedef struct Vertex
{
	uint32_t index;
	struct Vertex *next;
} Vertex;

typedef struct GraphL
{
	uint32_t numVerts;
	Vertex *vertexList;
} GraphL;



GraphL *newGraphL(struct GraphM *adjMat);
void deleteGraphL(GraphL *g);

bool addEdgeL(GraphL *g, uint32_t v1, uint32_t v2);
bool hasEdgeL(GraphL *g, uint32_t v1, uint32_t v2);

uint32_t *getVertexNeighbors(GraphL *g, uint32_t vertIndex);

#endif