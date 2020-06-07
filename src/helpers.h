#ifndef HELPERS_H
#define HELPERS_H

#define NODES 50
// #define ERROR 0.00001
#define ERROR 0.01

float calcAvg(float mesh[][NODES]);

void saveToFile(float mesh[][NODES]);

void copyMesh(float mesh[][NODES], float meshToCopy[][NODES]);

void initMesh(float mesh[][NODES], float SIDE_TEMPERATURES[]);

#endif