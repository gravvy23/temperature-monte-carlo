#include <OB/CORBA.h>
#include <OB/CosNaming.h>
#include <OB/OBNaming.h>
#include <fstream>
#include <iostream>
#include "TemperatureDataImplementation.h"

using namespace std;

int main( int argc, char *argv[] )
{
	try 
	{
		// Initialize server ORB
		CORBA::ORB_var vOrb = CORBA::ORB_init( argc, argv );
		// Get Root POA reference from ORB
		//	(with object lifetime managed by CORBA)
                CORBA::Object_var vPoaObj =
		            vOrb -> resolve_initial_references( "RootPOA" );
		assert(!CORBA::is_nil(vPoaObj));
		// Narrow (cast) reference to expected object class type 
		PortableServer::POA_var vRootPoa =
		            PortableServer::POA::_narrow(vPoaObj);
		// Get Root POA Manager object reference
		PortableServer::POAManager_var vManager =
		            vRootPoa -> the_POAManager();
		// Create implementation class instance object 
		//    (available locally on server)
                TemperatureDataImplementation *pTemperatureImpl
                            = new TemperatureDataImplementation;
		// Implicitly activate local instance as "CORBA Object" ...
                PortableServer::ServantBase_var vServant = pTemperatureImpl;
		// ... and obtain its IOR reference (for remote use)
                TemperatureDataInterface_var vTemperatureImplObj = pTemperatureImpl -> _this();
                // Locate Name Service
		CORBA::Object_var vObject =
                	vOrb->resolve_initial_references( "NameService" );
		assert(!CORBA::is_nil(vObject));
		CosNaming::NamingContext_var vNamingContext =
				CosNaming::NamingContext::_narrow( vObject );
                // Prepare object with "server name" data key
		CosNaming::Name implName;
		implName.length( 1 );
		implName[ 0 ].id   = CORBA::string_dup( argv[ 1 ] );
		implName[ 0 ].kind = CORBA::string_dup( "" );
		// Register object IOR reference in Name Service
		vNamingContext->bind( implName, vTemperatureImplObj );
		// Activate Root POA Manager - start processing request queue
                vManager -> activate();
		// Start ORB event loop (indefinitely)
                vOrb -> run();
	}
	catch( CORBA::SystemException& e )
        {
		cout << "Problem: parameters 1,2,3 are " 
			<< argv[ 1 ] << " " << argv[ 2 ] << " "
			<< argv[ 3 ] << "\n";
		cout << "Exception: " << e.reason() << "\n";
		return 1;
	}
	return 0;
}
