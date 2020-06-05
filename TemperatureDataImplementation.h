#include "TemperatureDataInterface_skel.h"

// Prototype of C++ class implementing remotely available methods
// based on the header file generated by IDL-to-C++ interface translation
// Server skeleton generated by inheritance - standalone TCP servant
class TemperatureDataImplementation : public POA_TemperatureDataInterface,
                                      public PortableServer::RefCountServantBase
{
public:
    virtual CORBA::Long randomWalk(TemperatureMesh& mesh, ::CORBA::ULong position) throw(CORBA::SystemException);
};