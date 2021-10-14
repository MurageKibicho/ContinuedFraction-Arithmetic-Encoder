#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "holder.h"



long NchooseK(int n, int k)
{
	long numerator = 1;
	long denominator = 1;
	
	if(n == k)
	{
		return 1;
	}
	else if(n < k)
	{
		return 0;
	}
	else
	{
		int nMinusk = n - k;
		int denominator = 1;
		int index = 1;
		if(nMinusk >= k)
		{
			for(int i = nMinusk + 1; i <= n; i++)
			{
				numerator *= i;
				denominator *= index;
				index++;
			}
			return (numerator/ denominator);
		}
		else
		{
			for(int i = k + 1; i <= n; i++)
			{
				numerator *= i;
				denominator *= index;
				index++;
			}
			return (numerator/ denominator);
		}
	}
}

Data CreateData(int startingValue, int base)
{
	Data data;
	data = malloc(sizeof(*data));
	data->startingValue = startingValue;
	data->base = base;
	int n = startingValue + base;
	int k = 0;
	if(startingValue <= base)
	{
		k = startingValue;
	}
	else
	{
		k = base;
	}
	data->maxValue = NchooseK(n,k);
	DataNode blankNode;
	data->dataNodes = malloc(sizeof(DataNode*) * data->maxValue);
	for(int i = 0; i < data->maxValue; i++)
	{
		data->dataNodes[i] = malloc(sizeof(*blankNode));
		data->dataNodes[i]->currentNumber = i;
		data->dataNodes[i]->values = malloc(sizeof(int) * startingValue);	
	}
	return data;
	//GenerateNumbers(startingValue, base);
}

void FillData(Data data)
{
	
}



void ResetAfter(int array[],int valueToReset, int index, int length)
{
	for(int i = index; i < length; i++)
	{
		array[i] = valueToReset;
	}
}

int GetFirstZeroIndex(int array[], int length)
{
	int index = -1;
	for(int i = 0; i < length; i++)
	{
		if(array[i] == 0)
		{
			index = i;
			break;
		}
	}
	return index;
}

void PrintArray(int array[], int length)
{
	//avoid first,put in binary
	for(int i = 0 ; i < length; i++)
	{
		printf("%d ", array[i]);
	}
	printf("\t\t");
}

int PrintArray2(int array[], int length)
{
	//avoid first,put in binary
	/*for(int i = 1 ; i < length; i++)
	{
		printf("%d ", array[i]);
	}
	printf("\t\t");*/
	return array[0] - array[1];
}

void DigitToUnary(int digit, int zeroOrOne)
{
	digit += 1;
	for(int i = 0 ; i  < digit; i++)
	{
		if(zeroOrOne == 0)
		{
			putchar('0');
		}
		else
		{
			putchar('1');
		}
	}
}

int PrintArrayDifference(int array[],int *zeroCounter, int *oneCounter, int length)
{
	int difference = 0;
	int lengths = 0;
	for(int i = 0; i < length - 1; i++)
	{
		difference =  array[i] - array[i + 1];
		lengths += (difference);
		printf("%d ", difference);
		//putchar('(');
		if(i % 2 == 0)
		{
			//DigitToUnary(difference, 0);
			//*(zeroCounter) += difference;
		}
		else
		{
			//DigitToUnary(difference, 1);
			//*oneCounter += difference;
		}
		//putchar(')');
		
	}
	//printf(" %d",lengths);
	putchar('\n');
	return lengths;
}

void GenerateHelper(int array[], int length)
{
	int zeroPosition = GetFirstZeroIndex(array, length);	
	if(zeroPosition == -1)
	{
		array[length-1]--;
		//PrintArray(array, length);
	}
	else
	{
		array[zeroPosition-1]--;
		ResetAfter(array,array[zeroPosition-1],zeroPosition, length);
		//PrintArray(array, length);
	}

}

int *CreateArray(int value, int length)
{
	int *myArray = malloc(length * sizeof(int));
	for(int i = 0; i < length; i++)
	{
		myArray[i] = value;
	}
	return myArray;
}

void CopyArray(int arrayToFill[], int array[], int length)
{
	for(int i = 0 ; i < length; i++)
	{
		//printf("%d ", array[i]);
		arrayToFill[i] = array[i];
	}
	//putchar('\n');
}

void GenerateNumbers(Data data, int arrayLength, int startingValue)
{
	int length = arrayLength;
	int *array = CreateArray(startingValue, length);
	long count = 0;
	while(array[0] != 0)
	{
		CopyArray(data->dataNodes[count]->values, array, length);
		GenerateHelper(array, length);
		count++;
	}
	//Copy last one
	CopyArray(data->dataNodes[count]->values, array, length);
	//PrintArray(data->dataNodes[count]->values, length);
	free(array);	
}

void DataDestroy(Data data)
{
	for(int i = 0; i < data->maxValue; i++)
	{
		free(data->dataNodes[i]->values);
		free(data->dataNodes[i]);
	}
	free(data->dataNodes);
	free(data);
}
/*
int main()
{
	Data data;
	int maxValue = 15;
	int arrayLength = 7;
	data = CreateData(arrayLength,maxValue);
	GenerateNumbers(data, arrayLength, maxValue);
	printf("%ld\n", data->maxValue);
	for(int i = 0; i < 65536; i++)
	{
		printf("%d : ", i);
		PrintArray(data->dataNodes[i]->values, arrayLength);
		putchar('\n');
	}
	DataDestroy(data);
	
	
	return 0;
}*/


