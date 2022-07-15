#ifndef BRON_KERBOSCH_H
#define BRON_KERBOSCH_H

#include <stdint.h> 

struct GraphL;

void bk(uint32_t *R, uint32_t *P, uint32_t *X, 
		struct GraphL *g, uint32_t **maximalCliques);
//void bkP();

void printMaximalCliques(uint32_t **maximalCliques);

#endif