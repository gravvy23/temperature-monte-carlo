#ifndef HELPERS_H
#define HELPERS_H

// #define NODES 100
#define NODES 20
#define ERROR 0.00001
// #define ERROR 0.01

float calcAvg(float mesh[][NODES]);

void saveToFile(float mesh[][NODES]);

#endif