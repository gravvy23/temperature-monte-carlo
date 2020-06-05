#include <OB/CORBA.h>
#include <OB/CosNaming.h>
#include <iostream>
#include <iomanip>
#include "TestInterface.h"
#define DIM 5

using namespace std;

int main( int argc, char *argv[] )
{
	float	pVector[ DIM ];
	char	*pName;
	float	Power;
	float Sum;
	CORBA::Float& pSum(Sum);

	for( int i = 0; i < DIM; i++ )
				pVector[ i ] = i + 1;
	if( argc < 3 )
	{
		cout << "Usage: " << argv[ 0 ] 
		     << " <server_name> <power> -ORBnaming <IOR> " << "\n";
		return 1;
	}

	try 
	{
                // Initialize client ORB
		CORBA::ORB_var vOrb = CORBA::ORB_init( argc, argv );
		// Locate Name Service
		CORBA::Object_var vObject =
			vOrb->resolve_initial_references( "NameService" );
		CosNaming::NamingContext_var vNamingContext =
			CosNaming::NamingContext::_narrow( vObject );
                // Prepare object with "server name" query
		CosNaming::Name implName;
		implName.length( 1 );
		pName = argv [ 1 ];
		implName[ 0 ].id   = CORBA::string_dup( pName );
		implName[ 0 ].kind = CORBA::string_dup( "" );
		// Get remote object reference from Name Service
		CORBA::Object_var vCorbaObj =
                	vNamingContext->resolve( implName );
		TestInterface_var vPowerVec =
			TestInterface::_narrow( vCorbaObj );
                // Prepare remote call arguments
		float tmpVector[ DIM ];
		xVector vector( DIM, DIM, tmpVector );
		for( int i = 0; i < DIM; i++ )
				vector[ i ] = pVector[ i ];
		Power = (float)atoi( argv[ 2 ] );
		// Execute remote object method call
		vPowerVec->PowerVecWrapper( vector, Power, pSum );
		// Print results received from remote object 
		cout << fixed << setprecision(3)
		     << "Power " << Power << " sum of vector is: " 
		     << pSum << "\n";
	}
	catch( CORBA::SystemException& e ) {
		cout << "Exception: " << e.reason() << "\n";
		return 1;
	}

	return 0;
}	
