#pragma once

#include <iostream>


int S(int block_len, uint8_t *vector);
int P(int block_len, uint8_t* vector);
int L(int block_len, uint8_t* vector);
int X(uint8_t* result, uint8_t* vector2,uint8_t* vector);
int G(uint8_t* result, uint8_t* N, uint8_t* m, uint8_t* h);
int E(uint8_t* K, uint8_t* m);
void AddModulo512(uint8_t* a, uint8_t* b, uint8_t* c);
