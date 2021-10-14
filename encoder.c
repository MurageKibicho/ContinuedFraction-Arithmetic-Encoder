#include <stdio.h>
#include <stdlib.h>
#include "encoder.h"
#include "brocot.h"


Statistic CreateStats(int highestValue, int brocotLength)
{
	Statistic stat;
	stat = malloc(sizeof(*stat));
	stat->highestValue = highestValue + 1;
	stat->brocotLength = brocotLength;
	stat->maxRange = brocotLength;
	stat->minRange = 0;
	stat->probability = calloc(highestValue + 1, sizeof(double));
	stat->ranges = calloc(highestValue + 1, sizeof(int));
	return stat;
}

void UpdateStatistics(Statistic stat, int *values, int arrayLength)
{
	//Start from second
	//Encode this separately
	/*
	if(values[0] == 15)
	{
		printf("(1) ");
	}
	else if(values[0] == 14)
	{
		printf("(0) ");
	}*/
	for(int i = 1; i < arrayLength; i++)
	{
		stat->probability[values[i]] = stat->probability[values[i]] + 1;
	}
}

void UpdateStatistics2(Statistic stat, int *values, int arrayLength)
{
	for(int i = 0; i < arrayLength - 1; i++)
	{
		stat->probability[(values[i] - values[i+1])] = stat->probability[(values[i] - values[i+1])] + 1;
	}
}

void FillRanges(Statistic stat, int depth)
{
	double sum = 0;
	int maxValue = Powerof(2, depth);
	for(int i = 0; i < stat->highestValue; i++)
	{
		sum += stat->probability[i];
		stat->ranges[i] = (int) (sum * maxValue);
		//printf("(%d %d)",i, stat->ranges[i]);
	}
	//putchar('\n');
}

void SumAndDivide(Statistic stat)
{
	int sum = 0;
	for(int i = 0; i < stat->highestValue; i++)
	{
		sum += stat->probability[i];
	}
	for(int i = 0; i < stat->highestValue; i++)
	{
		stat->probability[i] = (stat->probability[i] / sum);
	}
	//printf("%d", sum);
}

void PrintStatistics(Statistic stat)
{
	for(int i = 0; i < stat->highestValue; i++)
	{
		printf("(%d %1f)",i, stat->probability[i]);
	}
	putchar('\n');
}
void DestroyStats(Statistic stat)
{
	free(stat->probability);
	free(stat->ranges);
	free(stat);
}



/*
int main()
{
	Statistic stat = CreateStats(15, 10);
	int arr[]={1,2,3,4,5};
	int arr2[]={1,2,3,1,5};
	UpdateStatistics(stat, arr, 5);
	UpdateStatistics(stat, arr2, 5);
	
	
	DestroyStats(stat);
	return 0;
}*/
