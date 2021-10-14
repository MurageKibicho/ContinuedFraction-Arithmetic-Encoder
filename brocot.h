#include <stdio.h>
#include <stdlib.h>

typedef struct brocotNode *Node;
typedef struct brocotTreeArray *Tree;


struct brocotNode
{
	int numerator;
	int denominator;
	int leftChild;
	int rightChild;
};

struct brocotTreeArray
{
	int depth;
	int numberOfNodes;
	int startNumerator;
	int startDenominator;
	int endNumerator;
	int endDenominator;
	Node *treeNodes;
};

Tree CreateTree(int depth,int num1, int den1, int num2, int den2);
void FillTree(Tree tree);
void PrintTreeLinear(Tree tree);
long Powerof(int number, int power);
void ShowRange(int value, Tree tree, Statistic stat);

