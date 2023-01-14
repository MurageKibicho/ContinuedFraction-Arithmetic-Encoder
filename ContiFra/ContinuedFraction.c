#include "ContinuedFraction.h"


ContinuedFractionModel CreateNewModel()
{
	ContinuedFractionModel newModel = malloc(sizeof(*newModel));
	newModel->oneCount   = 1;
	newModel->totalCount = 2;
	
	newModel->minimumNumerator   = 0;
	newModel->minimumDenominator = 1;
	newModel->maximumNumerator   = 1;
	newModel->maximumDenominator = 1;
	
	newModel->splitNumerator   = 1;
	newModel->splitDenominator = 2;
	

	return newModel;
}

void ResetModel(ContinuedFractionModel model)
{
	model->oneCount   = 1;
	model->totalCount = 2;
}

void DestroyModel(ContinuedFractionModel model)
{
	free(model);
}

void PrintContinuedFraction(unsigned long numerator, unsigned long denominator)
{
	if(denominator == 0)
	{
		printf("\n");
		return;
	}
	else
	{
		unsigned long quotient = numerator / denominator;
		unsigned long remainder = numerator % denominator;
		printf("%lu,",quotient);
		PrintContinuedFraction(denominator, remainder);
	}
}

void PrintModel(ContinuedFractionModel model)
{
	//printf("(%2lu,%2lu,%2lu)\t",model->totalCount - model->oneCount,model->oneCount, model->totalCount);
	printf("(%8lu,%8lu)\t", model->minimumNumerator, model->minimumDenominator);
	PrintContinuedFraction(model->minimumNumerator, model->minimumDenominator);
	
	printf("(%8lu,%8lu)\t", model->splitNumerator , model->splitDenominator);
	PrintContinuedFraction(model->splitNumerator, model->splitDenominator);
	
	printf("(%8lu,%8lu)\t", model->maximumNumerator, model->maximumDenominator);
	PrintContinuedFraction(model->maximumNumerator, model->maximumDenominator);

	/*printf("(%.12f)\t", (double)model->minimumNumerator/(double) model->minimumDenominator);
	PrintContinuedFraction(model->minimumNumerator, model->minimumDenominator);
	
	printf("(%.12f)\t", (double) model->splitNumerator/(double) model->splitDenominator);
	PrintContinuedFraction(model->splitNumerator, model->splitDenominator);
	
	printf("(%.12f)\t", (double)model->maximumNumerator/(double) model->maximumDenominator);
	PrintContinuedFraction(model->maximumNumerator, model->maximumDenominator);*/
}

unsigned long GCD(unsigned long num, unsigned long den)
{
	if(num == den){return den;}if(num == 0){return den;}if(den == 0){return num;}if(num > den){return GCD(num-den,den);}
	return GCD(num,den-num);
}



void AddFractions(unsigned long a, unsigned long b, unsigned long c, unsigned long d, unsigned long *numeratorResult, long *denominatorResult)
{
	*numeratorResult   = (a * d) + (b * c);
	*denominatorResult = b * d;
	//printf("Z%lu %lu %lu %luZ\n", a,b,c,d);
}

void SubtractFractions(unsigned long a, unsigned long b, unsigned long c, unsigned long d, unsigned long *numeratorResult, unsigned long *denominatorResult)
{
	*numeratorResult   = (a * d) - (b * c);
	*denominatorResult = b * d;
}

void ReducedCFToFraction(unsigned long numerator, unsigned long denominator, unsigned long *numeratorResult, unsigned long *denominatorResult)
{
	unsigned long quotient,remainder;
	quotient = remainder = 0;
	unsigned long num0 = 0; unsigned long num1 = 1;
	unsigned long den0 = 1; unsigned long den1 = 0;
	unsigned long currentNumerator = 0; unsigned long currentDenominator = 0; 
	unsigned long currentTitle = 0;
	while(1)
	{
		quotient = numerator / denominator;
		remainder = numerator % denominator;
		currentTitle = quotient;
		numerator = denominator;
		denominator = remainder;
		//printf("%lu ",currentTitle);
		currentNumerator   = (num1 * currentTitle) + num0;
		currentDenominator = (den1 * currentTitle) + den0;
		
		
		
		num0 = num1; num1 = currentNumerator;
		den0 = den1; den1 = currentDenominator;
		if(denominator == 0){break;}
	}
	//printf("\n");
	//Last coefficient
	num1 = (num1 * currentTitle) + num0;
	den1 = (den1 * currentTitle) + den0;
	//printf("(%lu,%lu)", num1, den1);
	if(num1 > den1)
	{
		*numeratorResult = den1;
		*denominatorResult = num1;
	}
	else
	{
		*numeratorResult = num1;
		*denominatorResult = den1;
	}
}


void FindContinuedFractions(unsigned long *a, unsigned long *b, unsigned long *c, unsigned long *d, unsigned long *e, unsigned long *f)
{
	int matching = 0;
	unsigned long quotientAB,remainderAB,quotientCD,remainderCD,quotientEF,remainderEF;
	quotientAB=remainderAB=quotientCD=remainderCD=quotientEF=remainderEF = 0;
	
	unsigned long a1 = *a; unsigned long b1 = *b; unsigned long c1 = *c; unsigned long d1 = *d; unsigned long e1 = *e; unsigned long f1 = *f;
	
	unsigned long g,h,i,j;
	g=h=i=j=0;
	while(matching < 3)
	{	
		quotientAB = a1 / b1; quotientCD = c1 / d1; quotientEF = e1 / f1; 
		if(quotientAB != quotientCD || quotientCD != quotientEF){break;}
		remainderAB = a1 % b1; remainderCD = c1 % d1; remainderEF = e1 % f1; 
		a1 = b1; b1 = remainderAB; c1 = d1; d1 = remainderCD; e1 = f1; f1 = remainderEF;
		if(b1 == 0){break;}if(d1 == 0){break;}if(f1 == 0){break;}
		if(matching > 0)
		{
			ReducedCFToFraction(a1,b1,&g,&h);
			ReducedCFToFraction(e1,f1,&i,&j);
			double test0 = (double) g / (double) h;
			double test1 = (double) i / (double) j;
			if(test1 > test0 )
			{
				*a = g; *b = h;
				*e = i; *f = j;
				//printf("\n %.12f \n %.12f \n Good\n",test0,test1);
				break;
			}
			
		}
		matching++;
	}
	//printf("(%lu: %lu %lu %lu )", quotientAB,a1,b1, a1/b1);
	//printf("(%lu: %lu %lu %lu)",previousMatch, quotientAB,quotientCD,quotientEF);
	
}
void SimplifyFraction(unsigned long *a, unsigned long *b)
{
	unsigned long gcdAB = 0;
	gcdAB = GCD(*a, *b); 
	*a /= gcdAB; *b /= gcdAB;
} 

void SimplifyFractions(unsigned long *a, unsigned long *b, unsigned long *c, unsigned long *d, unsigned long *e, unsigned long *f)
{
	unsigned long gcdAB,gcdCD,gcdEF;
	gcdAB=gcdCD=gcdEF=0;
	gcdAB = GCD(*a, *b); gcdCD = GCD(*c, *d); gcdEF = GCD(*e, *f);
	*a /= gcdAB; *b /= gcdAB;
	*c /= gcdCD; *d /= gcdCD;
	*e /= gcdEF; *f /= gcdEF;
}

void FindNewSplit(ContinuedFractionModel model)
{
	//Find the size of our range
	unsigned long rangeNumerator   = 0;
	unsigned long rangeDenominator = 0;
	SubtractFractions(model->maximumNumerator, model->maximumDenominator, model->minimumNumerator, model->minimumDenominator, &rangeNumerator, &rangeDenominator);
	SimplifyFractions(&model->minimumNumerator,&model->minimumDenominator,&rangeNumerator, &rangeDenominator,&model->maximumNumerator,&model->maximumDenominator);
	unsigned long zeroCount    = model->totalCount - model->oneCount;
	rangeNumerator   = rangeNumerator    * zeroCount;
	rangeDenominator = rangeDenominator  * model->totalCount;
	SimplifyFraction(&rangeNumerator, &rangeDenominator);
	unsigned long newSplitNumerator   = 0;
	unsigned long newSplitDenominator = 0;
	AddFractions(model->minimumNumerator,model->minimumDenominator,rangeNumerator,rangeDenominator,&newSplitNumerator,&newSplitDenominator);	
	SimplifyFraction(&newSplitNumerator, &newSplitDenominator);
	model->splitNumerator   = newSplitNumerator;
	model->splitDenominator = newSplitDenominator;
}

void FindNewBounds(ContinuedFractionModel model,int binaryValue)
{
	model->totalCount += 1;
	if(binaryValue == 1)
	{
		model->oneCount += 1;
		model->minimumNumerator   = model->splitNumerator;
		model->minimumDenominator = model->splitDenominator;
	}
	else
	{
		model->maximumNumerator   = model->splitNumerator;
		model->maximumDenominator = model->splitDenominator;
	}
}


void UpdateModel(ContinuedFractionModel model, int binaryValue)
{
	//printf("\n%d\n",binaryValue);
	FindNewBounds(model, binaryValue);
	FindNewSplit(model);
	
	int limit = 20;
	if(log2(model->splitDenominator) > limit)
	{
		SimplifyFractions(&model->minimumNumerator,&model->minimumDenominator,&model->splitNumerator,&model->splitDenominator,&model->maximumNumerator,&model->maximumDenominator);
	}
	if(log2(model->splitDenominator) > limit)
	{
		printf("\n");
		//PrintModel(model);
		FindContinuedFractions(&model->minimumNumerator,&model->minimumDenominator,&model->splitNumerator,&model->splitDenominator,&model->maximumNumerator,&model->maximumDenominator);
		//ResetModel(model);
		FindNewSplit(model);
		printf("\n");
		
	}
	if(model->splitNumerator > model->splitDenominator)
	{
		printf("Bug!");
	}
	// weird bug
	//printf("%.0f %.0f %.0f\n",log2(model->minimumDenominator),log2(model->splitDenominator), log2(model->maximumDenominator));
}

int main()
{
	ContinuedFractionModel model = CreateNewModel();
	UpdateModel(model, 1);
	UpdateModel(model, 0);
	UpdateModel(model, 1);
	UpdateModel(model, 0);
	UpdateModel(model, 1);
	UpdateModel(model, 0);
	UpdateModel(model, 0);
	UpdateModel(model, 0);
	UpdateModel(model, 1);
	UpdateModel(model, 1);
	UpdateModel(model, 1);
	UpdateModel(model, 1);
	UpdateModel(model, 1);
	UpdateModel(model, 0);
	PrintModel(model);
	DestroyModel(model);
	//PrintModel(model);
	return 0;
}
