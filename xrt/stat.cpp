#include "stat.h"

bool computeReturnCorrelation(double* inputA,double* inputB,long inputLength,double* output)
{
	// Running totals
	int sum1=0;
	double sumA=0;
	double sumB=0;
	double sumAA=0;
	double sumBB=0;
	double sumAB=0;
	
	// Current values
	double prevValueA = inputA[0];
	double prevValueB=inputB[0];
	double curValueA;
	double curValueB;
	double returnA;
	double returnB;
	
	for (int index=1;index < inputLength;index++)
	{
		curValueA=inputA[index];
		curValueB=inputB[index];
		
		// Securities with null price (and infinite returns) are ruled out
		if(curValueA==0||curValueB==0)
		{
			cout << "Value at zero for index "<<index<<"\n";
			continue;
		}
		
		returnA = curValueA/prevValueA-1;
		returnB = curValueB/prevValueB-1;
		
		sum1+=1;
		sumA+=returnA;
		sumB+=returnB;
		sumAA+=returnA*returnA;
		sumBB+=returnB*returnB;
		sumAB+=returnA*returnB;
		
		prevValueA=curValueA;
		prevValueB=curValueB;
	}
	
	// Statistics
	double avgA = sumA/sum1;
	double avgB = sumB/sum1;
	double varA = sumAA/sum1-avgA*avgA;
	double varB = sumBB/sum1-avgB*avgB;
	double covarAB = sumAB/sum1-avgA*avgB;
	
	// Consistency check
	if (varA<=0 || varB<=0) return false;
	
	// Output value
	*output = covarAB/(sqrt(varA*varB));
	
	return true;
}