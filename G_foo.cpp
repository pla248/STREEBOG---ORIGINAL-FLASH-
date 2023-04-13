#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#define block_len  64
#include"all_the_func(no G_foo).h"

int G(uint8_t* result, uint8_t* N, uint8_t* h, uint8_t* m) {

	uint8_t* K = (uint8_t*)malloc(64 * sizeof(uint8_t));
	if (!K)
	{
		printf("Memory allocation error!");
		free(K);
		exit(-1);
	}
	memset(K, 0x00, 64 * sizeof(uint8_t));

	
	

	
	X(K,h,N);
	S(block_len, K);
	P(block_len, K);
	L(block_len, K);
	E( K, m);

	X(result, K, h);
	X(result, result, m);
	



	free(K);

	return 0;

}