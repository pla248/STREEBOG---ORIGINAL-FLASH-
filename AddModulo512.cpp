#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
void AddModulo512(uint8_t* a, uint8_t* b, uint8_t* c)
{
    int i = 0, t = 0;

    for (i = 63; i>=0; i--)
    {
        t = a[i] + b[i] + (t >> 8);
        c[i] = t & 0xFF;
    }
}