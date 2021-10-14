#include <stdio.h>
#include <stdlib.h>
#include "holder.h"



Finder CreateFinder(int arrayLength1,int arrayLength2)
{
	Finder finder;
	finder = malloc(sizeof(*finder));
	finder->arrayLength1 = arrayLength1;
	finder->arrayLength2 = arrayLength2;
	finder->matrix = malloc(sizeof(Noder*) * arrayLength1);
	
	Noder blankNode;
	for(int i = 0; i < arrayLength1; i++)
	{
		finder->matrix[i] = malloc(sizeof(Noder) * arrayLength2);
		for(int j = 0; j < arrayLength2; j++)
		{
			blankNode = malloc(sizeof(*blankNode));
			blankNode->value = 0;
			blankNode->i = 0;
			blankNode->j = 0;
			finder->matrix[i][j] = blankNode;
		}
	}
	return finder;
}

void PrintFinder(Finder finder)
{
	for(int i = 0; i < finder->arrayLength1; i++)
	{
		for(int j = 0; j < finder->arrayLength2; j++)
		{
			printf("%d(%d) ", finder->matrix[i][j]->value, finder->matrix[i][j]->i);
		}
		putchar('\n');
	}
	putchar('\n');
}


int Max(int a, int b)
{
	if(a >= b)
	{
		return 1;
	}
	else
	{
		return 2;
	}
}

int LargestSub(Finder finde, int *array1, int *array2, int arrayLength1, int arrayLength2)
{
	int indexi = 0;
	int indexj = 0;
	int direction = 0;
	
	for(int i = 1 ; i < arrayLength1; i++)
	{
		for(int j = 1; j < arrayLength2; j++)
		{ 
			if(array1[indexi] == array2[indexj])
			{
				finde->matrix[i][j]->value = (finde->matrix[i - 1][j - 1]->value) + 1;
				finde->matrix[i][j]->i = 0;
			}
			else
			{
				direction = Max(finde->matrix[i][j - 1]->value, finde->matrix[i - 1][j]->value);
				finde->matrix[i][j]->i = direction;
				if(direction == 1)
				{	//Came from left
					finde->matrix[i][j]->value = finde->matrix[i][j - 1]->value;
				}	
				else
				{	//Came from above
					finde->matrix[i][j]->value = finde->matrix[i - 1][j]->value;
				}			
			}
			indexj++;
		}
		indexj = 0;
		indexi++;	
	}
	//return finde->matrix[arrayLength1][arrayLength2]->value;
}

void FindString(Finder finder, int *two)
{
	int i = finder->arrayLength1 - 1;
	int j = finder->arrayLength2 - 1;
	int index = j;
	//Two is width
	while(index > -1)
	{
		if(finder->matrix[i][j]->i == 0)
		{
			printf("(%d %d, %d)",i,j, index);
			index--; 
			i--;
			j--;
		}
		else if(finder->matrix[i][j]->i == 1)
		{
			printf("(%d %d, %d)",i,j, index);
			j--;
			index--;
		}
		else
		{
			printf("(%d %d, %d)",i,j, index);
			i--;
		}
		
	}
}
/*
int main()
{
	int one[] = {'a','t','x','r','e','r','l'};
	int two[] = {'g','x','t','x','a','y'};
	int arrayLength1 = (sizeof(one) / sizeof(int)) + 1;
	int arrayLength2 = (sizeof(two) / sizeof(int)) + 1;
	
	Finder finder = CreateFinder(arrayLength1, arrayLength2);
	LargestSub(finder, one, two, arrayLength1, arrayLength2);
	PrintFinder(finder);
	FindString(finder, two);
	return 0;
}*/
