#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "io.h"
#include "graph_mat.h"

GraphM *parseMtxFile(const char *filename)
{
	FILE *filePtr = fopen(filename, "r");

	char lineBuffer[128] = {};

	//read first line and skip lines until data starts 
	
	fgets(lineBuffer, sizeof(lineBuffer), filePtr);

	while(lineBuffer[0] == '%')
	{
		fgets(lineBuffer, sizeof(lineBuffer), filePtr);
	}
	
	//get matrix info	

	int matrixDimensions[2] = {0, 0};
	int	numEntries = 0; 
	const char *infoFormat = "%d%d%d";

	int ret = sscanf(lineBuffer, infoFormat, &matrixDimensions[0], &matrixDimensions[1], &numEntries);
	
	assert(matrixDimensions[0] != 0);
	assert(matrixDimensions[1] == matrixDimensions[0]);
	assert(numEntries != 0);

	//printf("matrixDimensions[0] = %d\n", matrixDimensions[0]);
	//printf("matrixDimensions[1] = %d\n", matrixDimensions[1]);
	//printf("numEntries = %d\n", numEntries);
	
	GraphM *g = newGraphM(matrixDimensions[0], false);

	assert(g);
	
	const char *entryFormat = "%d%d";
	
	uint32_t vert1 = 0;
	uint32_t vert2 = 0;

	while(fgets(lineBuffer, sizeof(lineBuffer), filePtr) != NULL)
	{
		//printf(lineBuffer);
		int ret = sscanf(lineBuffer, entryFormat, &vert1, &vert2);
		addEdgeM(g, (vert1 - 1), (vert2 - 1));
	}
	
	return g;

	/*
	printf("Sparse Matrix: \n");
	ptrMatrixBegin = mat.beginPtr;
	int i;
	for(i = 0; i < mat.size; i++)
	{
		printf("\t%d, %d\n", ptrMatrixBegin->x, ptrMatrixBegin->y);	
		ptrMatrixBegin++;
	}
	*/
}