#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int PowerVec( float *pVector, int length, float *Sum, float Power )
{
	int i, errorCode;
	
	/* calculate power sum */
	*Sum = 0.0;

	printf(" start *** sum= %f power= %f\n", *Sum,  Power );

        for ( i = 0 ; i < length ; i++ ) 
        {
        	*Sum += pow( *(pVector+i), Power );
	// printf(" i= %d val=%f \n", i, pow( *(px+i), Power ) );
	}
        
	printf(" PowerVec *** sum = %f \n", *Sum );
	errorCode = 0 ;

	return( errorCode );
}
