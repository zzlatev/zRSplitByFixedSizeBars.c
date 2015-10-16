// zRSplitByFixedSizeBars
// By Zlatomir Zlatev
// Source: https://github.com/zzlatev/zRSplitByFixedSizeBars.c
#include <R.h>
#include <Rdefines.h>

SEXP zSplitByFixedSizeBars(SEXP xIntVect, SEXP nBy, SEXP nCount)
{
	int i, j, N, NBy, intSplitTo, intSplitTo2, startI;
	long long int sum=0;
	int *pNUM, *pResult;
	SEXP result;
	PROTECT(xIntVect = AS_INTEGER(xIntVect));
	NBy = INTEGER_VALUE(nBy);
	N = INTEGER_VALUE(nCount);
	pNUM = INTEGER(xIntVect);

	//get sum
	for(i=0; i<N; i++)
	{
		sum += pNUM[i];
	}
	//how many rows we'll need to split the volume bars to
	intSplitTo = sum/NBy;
	if(sum % NBy > 0)
		intSplitTo += 1;
	
	//reserve space for the results
	PROTECT(result = allocMatrix(INTSXP, intSplitTo, 3));
	pResult = INTEGER(result);
	intSplitTo2 = intSplitTo * 2;

	//split
	j=0; //j is the index for the split matrix
	i=0; // i is the index of the original vector
	sum = 0;
	startI = 1;
	while(1)
	{
		if(sum >= NBy) //split
		{
			pResult[j] = startI;
			pResult[j+intSplitTo] = i;
			pResult[j+intSplitTo2] = NBy;
			sum -= NBy;
			if(sum == 0)
				startI = i+1;
			else
				startI = i;
			j++;
			continue;
		}
		if(i==N && sum <= NBy) {
			if(sum != 0) { // final split
				pResult[intSplitTo-1] = startI;
				pResult[intSplitTo2-1] = i;
				pResult[intSplitTo*3-1] = sum;
			}
			break;
		}
		if(i<N) {
			sum += pNUM[i];
			i++;
		}
	}
	UNPROTECT(2);
	return result;
}
