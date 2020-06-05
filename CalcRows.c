#include <stdio.h>
#include <stdlib.h>

int CalcRows(unsigned long position)
{
    unsigned long row = 1 + (position - 1) / (100 - 2);
    return (int)row;
};