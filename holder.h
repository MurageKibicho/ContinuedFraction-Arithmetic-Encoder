#include <stdio.h>

typedef struct dataHolder *Data;
typedef struct dataNode *DataNode;

struct dataNode
{
	int currentNumber;
	int *values;
};

struct dataHolder
{
	long maxValue;
	int startingValue;
	int base;
	DataNode *dataNodes;
};

typedef struct noder *Noder;
typedef struct find *Finder;

struct noder
{
	int value;
	int i; 
	int j;
};

struct find
{
	int arrayLength1;
	int arrayLength2;
	Noder **matrix;
};

Data CreateData(int startingValue, int base);

void GenerateNumbers(Data data, int arrayLength, int startingValue);

void PrintArray(int array[], int length);
int PrintArray2(int array[], int length);
int PrintArrayDifference(int array[],int *zeroCounter, int *oneCounter, int length);

void DataDestroy(Data data);





//////////////////////////////////////
Finder CreateFinder(int arrayLength1,int arrayLength2);
void PrintFinder(Finder finder);
int LargestSub(Finder finde, int *array1, int *array2, int arrayLength1, int arrayLength2);









