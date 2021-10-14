#include <stdio.h>
#include <stdlib.h>

typedef struct statistic *Statistic;

struct statistic
{
	int highestValue;
	int brocotLength;
	double *probability;
	int *ranges;
	int maxRange;
	int minRange;
};

Statistic CreateStats(int highestValue, int brocotLength);
void UpdateStatistics(Statistic stat, int *values, int arrayLength);
void UpdateStatistics2(Statistic stat, int *values, int arrayLength);
void FillRanges(Statistic stat, int depth);
void SumAndDivide(Statistic stat);
void PrintStatistics(Statistic stat);
void DestroyStats(Statistic stat);
