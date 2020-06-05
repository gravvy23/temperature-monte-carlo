#include <stdio.h>
#include <stdlib.h>

int CalcCols(unsigned long position)
{
    unsigned long rows = 1 + (position - 1) / (100 - 2);
    unsigned long col = position - (100 - 2) * (rows - 1);
    return (int)col;
}