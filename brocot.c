#include <stdio.h>
#include <stdlib.h>
#include "encoder.h"
#include "brocot.h"



long Powerof(int number, int power)
{	
	long value = 1;
	for(long i = 0; i < power; i++)
	{
		value *= number;
	}
	return value;
}

void coefficient(int numerator, int denominator, int i)
{
	if(denominator == 0)
	{
		return;
	}
	else
	{
		int quotient = numerator / denominator;
		int remainder = numerator % denominator;
	
		if(i == 0)
		{
			i++;
			printf("%d; ", quotient);
			coefficient(denominator, remainder, i);
		}
		else
		{
			i++;
			printf("%d, ", quotient);
			coefficient(denominator, remainder, i);
		}
	}
}

Tree CreateTree(int depth,int num1, int den1, int num2, int den2)
{
	Tree tree;
	tree = malloc(sizeof(*tree));
	int numberOfNodes = Powerof(2, depth) + 1;
	tree->depth = depth;
	tree->startNumerator = num1;
	tree->startDenominator = den1;
	tree->endNumerator = num2;
	tree->endDenominator = den2;
	
	tree->numberOfNodes = numberOfNodes;
	tree->treeNodes = malloc(sizeof(Node*) * numberOfNodes);
	Node blankNode;
	for(int i = 0; i < numberOfNodes; i++)
	{
		tree->treeNodes[i] = malloc(sizeof(*blankNode));
		if(i == 0)
		{
			tree->treeNodes[i]->numerator = num1;
			tree->treeNodes[i]->denominator = den1;
		}
		else if(i == numberOfNodes -1)
		{
			tree->treeNodes[i]->numerator = num2;
			tree->treeNodes[i]->denominator = den2;
		}
		else
		{
			tree->treeNodes[i]->numerator = 0;
			tree->treeNodes[i]->denominator = 0;
		}
		tree->treeNodes[i]->leftChild = 0;
		tree->treeNodes[i]->rightChild = 0;
	}
	return tree;
}

void FillTreeHelper(Tree tree, int num1,int den1,int num2,int den2, int depth, int start, int stop)
{
	if(depth == 0)
	{
		return;
	}
	int numerator = num1 + num2;
	int denominator = den1 + den2;
	depth--;
	int newPosition = (start+stop) / 2;
	tree->treeNodes[newPosition]->numerator = numerator;
	tree->treeNodes[newPosition]->denominator = denominator;
	//printf("(%d %d , %d)\n", numerator, denominator, newPosition);
	FillTreeHelper(tree, num1, den1, numerator, denominator, depth, start, newPosition);	
	FillTreeHelper(tree, numerator, denominator,num2, den2, depth, newPosition, stop);
}

void FillTree(Tree tree)
{
	int start = 0;
	int stop = (tree->numberOfNodes) - 1;
	tree->treeNodes[0]->numerator = tree->startNumerator;
	tree->treeNodes[0]->denominator = tree->startDenominator;
	FillTreeHelper(tree, tree->startNumerator,tree->startDenominator,tree->endNumerator,tree->endDenominator,tree->depth, start, stop);
	tree->treeNodes[stop]->numerator = tree->endNumerator;
	tree->treeNodes[stop]->denominator = tree->endDenominator;
}

void PrintTreeLinear(Tree tree)
{
	int count[200] = {0};
	int end = tree->numberOfNodes;
	for(int i = 0; i < end; i++)
	{
		printf("%d: ([%d,%d] [%.10f] ", i+1, tree->treeNodes[i]->numerator, tree->treeNodes[i]->denominator,(double)(tree->treeNodes[i]->numerator) / (double)(tree->treeNodes[i]->denominator));
		//printf("%d: ([%d,%d] ", i, tree->treeNodes[i]->numerator, tree->treeNodes[i]->denominator);
		coefficient(tree->treeNodes[i]->numerator,tree->treeNodes[i]->denominator,0);
		printf(")\n");
	}
	
	putchar('\n');
	/*for(int i = 0; i < end; i++)
	{
		if(tree->treeNodes[i]->denominator == 74)
		{
			printf("B%dB\n", i);
		}
		count[tree->treeNodes[i]->denominator] = count[tree->treeNodes[i]->denominator] + 1;
		//printf(" %2d ", tree->treeNodes[i]->denominator);
	}*/
	/*for(int i = 0; i < 200; i++)
	{
		printf("%d, %d\n", i, count[i]);
	}*/
}

void PrintTreeHelper(Tree tree, int depth, int start, int stop, int count)
{
	if(depth == 0)
	{
		return;
	}
	depth--;
	int newPosition = (start+stop) / 2;
	printf("(%d/%d) %d", tree->treeNodes[newPosition]->numerator, tree->treeNodes[newPosition]->denominator, count);
	
	PrintTreeHelper(tree, depth, start, newPosition, count++);
	PrintTreeHelper(tree, depth, newPosition, stop, count++);

	
}
void PrintTree(Tree tree)
{
	int count = 0;
	PrintTreeHelper(tree, tree->depth, 0, (tree->numberOfNodes) - 1, count);
}

void FindDeterminant(int a, int b, int c, int d)
{
	printf("%d\n", a * d - b * c);
}

void ShowRange(int value, Tree tree, Statistic stat)
{
	int previous = 0;
	int treeStart = 0;
	if(value != 0)
	{
		previous = value - 1;
		treeStart = (stat->ranges[previous]);
	}
	int treeEnd = (stat->ranges[value]);
	printf("Range (%d - %d) : (%d, %d) - (%d, %d)\n",treeStart, treeEnd, tree->treeNodes[treeStart]->numerator, tree->treeNodes[treeStart]->denominator,tree->treeNodes[treeEnd]->numerator, tree->treeNodes[treeEnd]->denominator);
	coefficient(tree->treeNodes[treeStart]->numerator,tree->treeNodes[treeStart]->denominator,0);
	putchar('\n');
	coefficient(tree->treeNodes[treeEnd]->numerator,tree->treeNodes[treeEnd]->denominator,0);
	putchar('\n');
	//printf("(%d - %d)\n", treeStart, treeEnd);
}
//141252
//211158

//14 10 5 5 5 0    4 5 0 0 5 
//13 7 6 5 1 1     6 1 1 4 0 
//13 11 6 6 3 2    2 5 0 3 1
//14 13 12 7 4 4   1 1 5 3 3
int main()
{
	Tree tree = CreateTree(5,5,9,2,3);
	FillTree(tree);
	printf("\t%d Fractions\n", tree->numberOfNodes);
	PrintTreeLinear(tree);
	return 0;
}
