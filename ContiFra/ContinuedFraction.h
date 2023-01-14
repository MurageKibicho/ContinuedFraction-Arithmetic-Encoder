#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct fractionmodel *ContinuedFractionModel;

struct fractionmodel
{
	unsigned long oneCount;
	unsigned long totalCount;
	
	unsigned long minimumNumerator;
	unsigned long minimumDenominator;
	
	unsigned long maximumNumerator;
	unsigned long maximumDenominator;
	
	unsigned long splitNumerator;
	unsigned long splitDenominator;
	
	unsigned long *previous;
	int previousCount;
}; 
