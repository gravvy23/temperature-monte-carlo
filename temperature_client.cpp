#include <OB/CORBA.h>
#include <OB/CosNaming.h>
#include <iostream>
#include <iomanip>
#include "TemperatureDataInterface.h"
#define NODES 100

using namespace std;

int main(int argc, char *argv[])
{
    /************************** calc variables ******************************/
    float SIDE_TEMPERATURES[4] = {60.f, 10.f, 60.f, 10.f}; // north, east, south, west
    const float INIT_TEMP = 0.f;                         // initial temp in nodes, should be always 0
    float MESH[NODES][NODES];
    char *pName;

    /****************** Initializing values *********************************/
    for (int i = 0; i < NODES; i++)
    {
        for (int j = 0; j < NODES; j++)
        {
            if (i == 0) // south
            {
                MESH[i][j] = SIDE_TEMPERATURES[2];
            }
            else if (j == 0) //west
            {
                MESH[i][j] = SIDE_TEMPERATURES[3];
            }
            else if (i == NODES - 1) // east
            {
                MESH[i][j] = SIDE_TEMPERATURES[1];
            }
            else if (j == NODES - 1) // north
            {
                MESH[i][j] = SIDE_TEMPERATURES[0];
            }
            else //interior
            {
                MESH[i][j] = INIT_TEMP;
            }
        }
    }

    if (argc < 2)
    {
        cout << "Usage: " << argv[0]
             << " <server_name> -ORBnaming <IOR> "
             << "\n";
        return 1;
    }

    try
    {
        // Initialize client ORB
        CORBA::ORB_var vOrb = CORBA::ORB_init(argc, argv);
        // Locate Name Service
        CORBA::Object_var vObject =
            vOrb->resolve_initial_references("NameService");
        CosNaming::NamingContext_var vNamingContext =
            CosNaming::NamingContext::_narrow(vObject);
        // Prepare object with "server name" query
        CosNaming::Name implName;
        implName.length(1);
        pName = argv[1];
        implName[0].id = CORBA::string_dup(pName);
        implName[0].kind = CORBA::string_dup("");
        // Get remote object reference from Name Service
        CORBA::Object_var vCorbaObj =
            vNamingContext->resolve(implName);
        TemperatureDataInterface_var server =
            TemperatureDataInterface::_narrow(vCorbaObj);


        cout << "Before calculations " << MESH[10][10] << "\n";
        // Execute remote object method call
        server->randomWalk(MESH,10,10);
        // Print results received from remote object
        cout << "After calculations " <<  MESH[10][10] << "\n";
    }
    catch (CORBA::SystemException &e)
    {
        cout << "Exception: " << e.reason() << "\n";
        return 1;
    }

    return 0;
}
