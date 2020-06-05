#include "TestInterface_skel.h"

// Prototype of C++ class implementing remotely available methods
// based on the header file generated by IDL-to-C++ interface translation
// Server skeleton generated by inheritance - standalone TCP servant
class TestImplementation:
				public POA_TestInterface,
				public PortableServer::RefCountServantBase
                                                                        
{
    public: virtual CORBA::Long PowerVecWrapper( xVector&     vector,
        					 CORBA::Float  Power,
					         CORBA::Float& Sum 
					       )
					       throw(CORBA::SystemException);
};

