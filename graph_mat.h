#ifndef GRAPH_MAT_H
#define GRAPH_MAT_H

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

//graph using an ajacencey matrix representation

typedef struct GraphM
{
	uint32_t numVerts;
	bool isDirected;
	bool **edges;
} GraphM;

GraphM *newGraphM(uint32_t numVerts, bool isDirected);
void deleteGraphM(GraphM *g);

bool addEdgeM(GraphM *g, uint32_t v1, uint32_t v2);
bool hasEdgeM(GraphM *g, uint32_t v1, uint32_t v2);

#endif