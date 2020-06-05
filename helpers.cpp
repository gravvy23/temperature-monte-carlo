#include <iostream>
#include <stdlib.h>
#include "helpers.h"

float calcAvg(float mesh[][NODES])
{
    float sum = 0.0f;
    for (int i = 0; i < NODES; ++i)
    {
        for (int j = 0; j < NODES; ++j)
        {
            sum += mesh[i][j];
        }
    }
    return sum / (NODES * NODES);
}

void saveToFile(float mesh[][NODES])
{
    FILE *fptr;
    fptr = fopen("dane.txt", "w");
    if (fptr != NULL)
    {
        for (int i = 0; i < NODES; ++i)
        {
            for (int j = 0; j < NODES; ++j)
            {
                fprintf(fptr, "%lf ", mesh[i][j]);
            }
            fprintf(fptr, "\n");
        }
        fclose(fptr);
    }
}

void copyMesh(float mesh[][NODES], float meshToCopy[][NODES])
{
    for (int i = 1; i < NODES - 1; ++i)
    {
        for (int j = 1; j < NODES - 1; ++j)
        {

            mesh[i][j] = meshToCopy[i][j];
        }
    }
}