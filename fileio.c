#include <stdio.h>
#include <stdlib.h>
#include "holder.h"
#include "encoder.h"
#include "brocot.h"

int CombineArray(int array[])
{
	int combined = 0; 
	combined = (array[0]<<8) | array[1];
	return combined;
}



void OpenFile(Data data, Statistic stat, int arrayLength)
{
	FILE *fp = fopen("sample.png", "rb");
	int ch;
	int holder[2];
	int index = 0;
	int lineCounter = 0;
	int combined = 0;
	int oneCounter = 0;
	int zeroCounter = 0;
	int total = 0;
	if(fp == NULL){}
	else
	{
		while((ch = fgetc(fp)) != EOF)
		{
			if((index % 2) == 0)
			{
				index = 0;
				lineCounter++;
				if(lineCounter >= 2)
				{
					combined = CombineArray(holder);
					printf("%d\t", combined);
					PrintArray(data->dataNodes[combined]->values,arrayLength);
					total += PrintArrayDifference(data->dataNodes[combined]->values,&zeroCounter,&oneCounter, arrayLength);
					//UpdateStatistics(stat, data->dataNodes[combined]->values, arrayLength);
					UpdateStatistics2(stat, data->dataNodes[combined]->values, arrayLength);
				}	
			}
			//printf("%d\n", ch);
			holder[index] = ch;
			index++;
		}
		//Print last one
		//PrintArray(holder, 2);
	}
	fclose(fp);
	printf("B%dB", total);
}

void OpenFile2(int *one, int *two, Data data)
{
	FILE *fp1 = fopen("lena.png", "rb");
	FILE *fp2 = fopen("sample.png","rb");
	int arrayIndex = 0;
	int c = 0;
	int c1 = 0;
	int count = 0;
	int holder1[2];
	int holder2[2];
	int combined1 = 0;
	int combined2 = 0;
	int index = 0;
	int lineCounter = 0;
	if(fp1 == NULL || fp2 == NULL)
	{
		printf("Error");
	}
	else
	{	
		while((c = fgetc(fp1)) != EOF)
		{
			c1 = fgetc(fp2);
			if(index % 2 == 0)
			{
				index = 0;
				lineCounter++;
				if(lineCounter > 1)
				{
					combined1 = CombineArray(holder1);
					combined2 = CombineArray(holder2);
					int result1 = PrintArray2(data->dataNodes[combined1]->values,7);
					int result2 = PrintArray2(data->dataNodes[combined2]->values,7);
					one[arrayIndex] = result1;
					two[arrayIndex] = result2;
					arrayIndex++;
					printf("%d %d\n", result1, result2);
					//putchar('\n');
				}
			}
			holder1[index] = c;
			holder2[index] = c1;
			index++;
			count++;
			if(count == 400)
			{
				return;
			}
		}
	}
}

void OpenFile3(float *counter1, float *counter2, Data data)
{
	FILE *fp1 = fopen("lena.png", "rb");
	FILE *fp2 = fopen("sample.png","rb");
	int arrayIndex = 0;
	int c = 0;
	int c1 = 0;
	int count = 0;
	int holder1[2];
	int holder2[2];
	int combined1 = 0;
	int combined2 = 0;
	int index = 0;
	int lineCounter = 0;
	if(fp1 == NULL || fp2 == NULL)
	{
		printf("Error");
	}
	else
	{	
		while((c = fgetc(fp1)) != EOF)
		{
			c1 = fgetc(fp2);
			if(index % 2 == 0)
			{
				index = 0;
				lineCounter++;
				if(lineCounter > 1)
				{
					combined1 = CombineArray(holder1);
					combined2 = CombineArray(holder2);
					int result1 = PrintArray2(data->dataNodes[combined1]->values,7);
					int result2 = PrintArray2(data->dataNodes[combined2]->values,7);
					counter1[result1] += 1;
					counter2[result2] += 1;
					//printf("%d %d\n", result1, result2);
					//putchar('\n');
				}
			}
			holder1[index] = c;
			holder2[index] = c1;
			index++;
			count++;
			if(count == 200000)
			{
				return;
			}
		}
	}
}

void Sum(float *array, int arrayLength)
{
	int value = 0;
	for(int i = 0; i < arrayLength; i++)
	{
		value+=array[i];	
	}
	for(int i = 0; i < arrayLength; i++)
	{
		array[i] /= value;	
	}
	for(int i = 0; i < arrayLength; i++)
	{
		printf("%.3f ", array[i]);	
	}
}
	
int main()
{
	Data data;
	int maxValue = 15;
	int arrayLength = 7;
	data = CreateData(arrayLength,maxValue);
	Statistic stat = CreateStats(maxValue, 10);
	GenerateNumbers(data, arrayLength, maxValue);
	float counter1[15] = {0};
	float counter2[15] = {0};
	OpenFile3(counter1, counter2,data);
	Sum(counter2, 15);
	
	//OpenFile(data, stat, arrayLength);
	//PrintStatistics(stat);
	//putchar('\n');
	//SumAndDivide(stat);
	//putchar('\n');
	//PrintStatistics(stat);
	//putchar('\n');
	/*
	int depth = 8;
	Tree tree = CreateTree(depth,231504640, 303980608, 89197312, 117121856);
	FillTree(tree);
	printf("\t%d Fractions\n", tree->numberOfNodes);
	PrintTreeLinear(tree);
	FillRanges(stat, depth);
	//ShowRange(14, tree, stat);
	//ShowRange(10, tree, stat);
	//ShowRange(5, tree, stat);
	ShowRange(5, tree, stat);
	//ShowRange(0, tree, stat);
	//11000
	*/
	/*
	int one[200] = {0};
	int two[200] = {0};
	OpenFile2(one, two, data);
	Finder finder = CreateFinder(200, 200);
	LargestSub(finder, one, two, 200, 200);
	printf("%d", finder->matrix[199][199]->value);
	//PrintFinder(finder);
	*/
	DestroyStats(stat);
	DataDestroy(data);
	return 0;
}
//gcc Holder.c subsequence.c brocot.c encoder.c fileio.c -o fileio.o && ./fileio.o



