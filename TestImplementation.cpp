
#include <OB/CORBA.h>
#include <stdio.h>
#include "TestImplementation.h"

// Computational function in separate source file
extern int PowerVec( float *pVector, int length, float *Sum, float Power );


// Implementation of C++ class method (based on prototype from the header file)
// Some arguments are being transferred by reference (changes returned)
CORBA::Long TestImplementation::PowerVecWrapper( xVector&     vector, 
					    	 CORBA::Float  Power,
					   	 CORBA::Float& Sum )
					   	throw(CORBA::SystemException)
{
	static float *pVector = NULL;
	float pSum;

	// Vector length may not change after 1st call (static pointer) !!!
	if( !pVector )
		pVector = new float[ vector.length() ];

	// Copy CORBA object sequence fields into generic vector
	for( int i = 0; i < vector.length(); i++ )
		pVector[ i ] = vector[ i ];
	// Copy CORBA object value into generic scalar
	pSum = Sum;
	
	// Execute some calculations (args send by reference)
	int errorCode = PowerVec( pVector,
                                 vector.length(), &pSum, Power );

	// Copy modified local vector back into CORBA object sequence fields
	for( int i = 0; i < vector.length(); i++ )
		vector[ i ] = pVector[ i ];
	// Copy modified local scalar back into CORBA object value
	Sum = pSum;
	
	// Dummy data returned in this example
	return errorCode;
}
