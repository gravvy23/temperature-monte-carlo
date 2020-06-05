#include <OB/CORBA.h>
#include <OB/CosNaming.h>
#include <iostream>
#include <iomanip>
#include <math.h>
#include "TemperatureDataInterface.h"
#include "helpers.h"

using namespace std;

int main(int argc, char *argv[])
{
    /************************** calc variables ******************************/
    float SIDE_TEMPERATURES[4] = {60.f, 10.f, 60.f, 10.f}; // north, east, south, west
    const float INIT_TEMP = 0.f;                           // initial temp in nodes, should be always 0
    float MESH[NODES][NODES];
    char *pName;
    float average, tmp_avg, err;

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
    tmp_avg = calcAvg(MESH);

    /****************** check args validity *********************************/
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

        /*********************** main calculations *************************************/
        do
        {
            average = tmp_avg;
            /*********************** iteration *************************************/
            for (int i = 1; i < NODES - 1; ++i)
            {
                for (int j = 1; j < NODES - 1; ++j)
                {
                    // cout << "Before calculations " << MESH[i][j] << "\n";
                    // Execute remote object method call
                    server->randomWalk(MESH, i, j);
                    // cout << "After calculations " << MESH[i][j] << "\n";
                }
            }
            tmp_avg = calcAvg(MESH);
            err = fabs(average - tmp_avg);
            cout << "ERROR: " << err << "\n";
        } while (err > ERROR);
    }

    catch (CORBA::SystemException &e)
    {
        cout << "Exception: " << e.reason() << "\n";
        return 1;
    }

    return 0;
}
