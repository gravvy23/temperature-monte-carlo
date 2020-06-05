#include <OB/CORBA.h>
#include <stdio.h>
#include "TemperatureDataImplementation.h"
#include "helpers.h"

//Function calculating temerature in provided position in separate source file
extern float RandomWalk(int row, int col, float** mesh, float sum, int count);

// Implementation of C++ class method (based on prototype from the header file)
// mesh is being transferred by reference (changes returned)
CORBA::Long TemperatureDataImplementation::randomWalk(TemperatureMesh mesh,
                                                      CORBA::ULong row, CORBA::ULong column) throw(CORBA::SystemException)
{
    // static float** pmesh = NULL;

    // // Mesh length may not change after 1st call (static pointer)
    // if(!pmesh) 
    // {
    //     pmesh = new float*[NODES];
    //     for (int i = 0; i < NODES; ++i)
    //     {
    //         pmesh[i] = new float[NODES];
    //     }
    // }
    // for (int i = 0; i < NODES; ++i)
    // {
    //     for (int j = 0; j < NODES; ++j)
    //     {
    //         // Copy CORBA object fields into generic matrix
    //         pmesh[i][j] = mesh[i][j];
    //     }
    // }

    //Execute some calculations
    float newTemperature = RandomWalk((int)row, (int)column, mesh, 0.0f, 0);
    //save new temperature in original mesh
    mesh[row][column] = newTemperature;

    // Dummy data returned
    return 0;
}