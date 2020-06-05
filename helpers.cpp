#include <iostream>
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