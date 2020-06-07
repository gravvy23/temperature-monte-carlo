#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"

int isBoundary(int i, int j)
{
    return i == 0 || j == 0 || i == NODES - 1 || j == NODES - 1;
}


float RandomWalk(int i, int j, float** mesh, float sum, int count, long counter)
{
    srand((count+1)*(counter+1));
    sum += mesh[i][j];
    count++;
    if (isBoundary(i, j))
    {
        return sum / count;
    }
    int direction = rand() % 4;
    if (direction == 0) //north
    {
        return RandomWalk(j + 1, i, mesh, sum, count, counter);
    }
    if (direction == 1) //east
    {
        return RandomWalk(j, i + 1, mesh, sum, count, counter);
    }
    if (direction == 2) //south
    {
        return RandomWalk(j - 1, i, mesh, sum, count, counter);
    }
    return RandomWalk(j, i - 1, mesh, sum, count, counter);
};