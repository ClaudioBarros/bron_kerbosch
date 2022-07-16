#include "bron_kerbosch.h"
#include "graph_list.h"
#include "stb_ds.h"
#include "stdio.h"

void printList(uint32_t *list)
{
	printf("{");
	for(int i = 0; i < arrlen(list); i++)
	{
		printf(" %d ", list[i]);
	}
	printf("}");
}

void printMaximalCliques(uint32_t **maximalCliques)
{
	for(int i = 0; i < arrlen(maximalCliques); i++)
	{
		printf("Maximal Cliques:\n\n");
		printf("\t");
		printList(maximalCliques[i]);
		printf("\n");
	}
}


uint32_t *getIntersection(uint32_t *a1, uint32_t *a2)
{
	//TODO

	uint32_t *intersectionSet = NULL;	
	
	if(arrlen(a1) == 0 || arrlen(a2) == 0)
	{
		return intersectionSet;
	}
	
	for(int i = 0; i < arrlen(a1); i++)
	{
		for(int j = 0; j < arrlen(a2); j++)
		{
			if(a1[i] == a2[j])
			{
				bool wasAdded = false;
				for(int k = 0; k < arrlen(intersectionSet); k++)
				{
					if(intersectionSet[k] == a1[i])
					{
						wasAdded = true;	
						break;
					}
				}	
				if(wasAdded)
				{
					continue;
				}
				arrput(intersectionSet, a1[i]);
			}
		}
	}
	
	return intersectionSet;
}

void bk(uint32_t *R, uint32_t *P, uint32_t *X, 
        GraphL *g, uint32_t **maximalCliques)
{
	printf("bk() with parameters:\n");
	printf("R = ");
	printList(R);
	printf("\n");
	printf("P = ");
	printList(P);
	printf("\n");
	printf("X = ");
	printList(X);
	printf("\n");

	//printf("arrlen(R): %d\n", (int) arrlen(R));
	//printf("arrlen(P): %d\n", (int) arrlen(P));
	//printf("arrlen(X): %d\n", (int) arrlen(X));

	if(!arrlen(P) && !arrlen(X))
	{

		//report maximal clique
		uint32_t *clique = NULL;
		for(int i = 0; i < arrlen(R); i++)
		{
			arrput(clique, R[i]);
		}
		arrput(maximalCliques, clique);

		printf("\n**** MAXIMAL CLIQUE : ");
		printList(clique);
		printf(" **** \n\n");
		return;
	}
	
	
	uint32_t *newR = NULL;
	uint32_t *newP = NULL;
	uint32_t *newX = NULL;

	for(int i = 0; i < arrlen(P); i++)
	{
		printf("current vertex: %d \n", P[i]);

		//R U {v}
		for(int indexOfR = 0; indexOfR < arrlen(R); indexOfR++)
		{
			arrput(newR, R[indexOfR]);
		}
		arrput(newR, P[i]);

		//P intersection N(v)
		uint32_t *neighbors = getVertexNeighbors(g, P[i]);
		
		printf("vertex neighbors: ");
		printList(neighbors);
		printf("\n\n");

		newP = getIntersection(P, neighbors);

		//X intersection N(v)
		newX = getIntersection(X, neighbors);

		//recursive call
		bk(newR, newP, newX, g, maximalCliques);
		
		arrfree(newR);
		arrfree(newP);
		arrfree(newX);

		//P = P \ {v}
		arrdel(P, i);

		//X = X U {v}
		arrput(X, P[i]);
	}
	
	//arrfree(newR);
	//arrfree(newP);
	//arrfree(newX);
}