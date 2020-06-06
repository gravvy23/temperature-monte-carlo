#include <OB/CORBA.h>
#include <OB/CosNaming.h>
#include <iostream>
#include <iomanip>
#include <math.h>
#include "TemperatureDataInterface.h"
#include "helpers.h"

using namespace std;

float MESH[NODES][NODES];
float TEMP_MESH[NODES][NODES];
JTCMutex MeshMutex;
JTCMonitor MeshMonitor;

TemperatureDataInterface_var openServer(char *pName, CORBA::ORB_var vOrb)
{
    // Locate Name Service
    CORBA::Object_var vObject =
        vOrb->resolve_initial_references("NameService");
    CosNaming::NamingContext_var vNamingContext =
        CosNaming::NamingContext::_narrow(vObject);
    // Prepare object with "server name" query
    CosNaming::Name implName;
    implName.length(1);
    implName[0].id = CORBA::string_dup(pName);
    implName[0].kind = CORBA::string_dup("");
    // Get remote object reference from Name Service
    CORBA::Object_var vCorbaObj =
        vNamingContext->resolve(implName);
    return TemperatureDataInterface::_narrow(vCorbaObj);
}

class SideThread : public JTCThread
{
    static int stoppedCount;
    char *pName;
    int startRow;
    int endRow;
    TemperatureDataInterface_var server;

    void waitForOthers()
    {
        JTCSynchronized sync(MeshMonitor);
        stoppedCount++;
        if (stoppedCount == 2)
        {
            stoppedCount = 0;
            MeshMonitor.notify();
        }
        else
        {
            MeshMonitor.wait();
        }
    }

public:
    SideThread(int startRow, int endRow, TemperatureDataInterface_var server) : startRow(startRow), endRow(endRow), server(server)
    {
    }

    virtual void run()
    {
        /*********************** iteration *************************************/
        for (int i = startRow; i <= endRow; ++i)
        {
            for (int j = 1; j < NODES - 1; ++j)
            {
                MeshMutex.lock();
                TEMP_MESH[i][j] = server->randomWalk(MESH, i, j);
                MeshMutex.unlock();
            }
        }
        waitForOthers();
    }
};
int SideThread::stoppedCount = 0;
int main(int argc, char *argv[])
{
    /************************** calc variables ******************************/
    float SIDE_TEMPERATURES[4] = {60.f, 60.f, 10.f, 10.f}; // north, east, south, west
    float average, tmp_avg, err;
    JTCThread *pThread1, *pThread2;
    TemperatureDataInterface_var server1, server2;

    /****************** Initializing values *********************************/
    JTCInitialize initialize;
    initMesh(MESH, SIDE_TEMPERATURES);
    tmp_avg = calcAvg(MESH);
    copyMesh(TEMP_MESH, MESH);
    /****************** check args validity *********************************/
    if (argc < 3)
    {
        cout << "Usage: " << argv[0]
             << " <server_name1> <server_name2>"
             << "\n";
        return 1;
    }
    CORBA::ORB_var vOrb;
    try
    {
        vOrb = CORBA::ORB_init(argc, argv);
        server1 = openServer(argv[1], vOrb);
        server2 = openServer(argv[2], vOrb);
    }
    catch (CORBA::SystemException &e)
    {
        return 1;
    }

    do
    {
        average = tmp_avg;

        pThread1 = new SideThread(1, NODES / 2, server1);
        pThread2 = new SideThread(NODES / 2 + 1, NODES - 1, server2);
        pThread2->start();
        pThread1->start();
        try
        {
            pThread1->join();
            pThread2->join();
        }
        catch (...)
        {
        }

        copyMesh(MESH, TEMP_MESH);
        tmp_avg = calcAvg(MESH);
        err = fabs(average - tmp_avg);
        cout << "ERROR: " << err << "\n";
    } while (err > ERROR);

    //save data to output file
    cout << "HERE";
    saveToFile(MESH);
    return 0;
}
