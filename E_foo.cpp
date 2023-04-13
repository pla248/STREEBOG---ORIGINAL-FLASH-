#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#define block_len  64
#include"all_the_func(no E_foo).h"
#include "const(C[i]).h"

int E(uint8_t* K, uint8_t* m) {

	uint8_t* state = (uint8_t*)malloc(64 * sizeof(uint8_t));
	if (!state)
	{
		printf("Memory allocation error!");
		free(state);
		exit(-1);
	}
	memset(state, 0x00, 64 * sizeof(uint8_t));
	if (K == NULL or m == NULL)
	{
		goto exit;
	}

	X(state, m, K);
	
	for (uint8_t i = 0; i <=11; i++)
	{
		
		S(block_len, state);	
		P(block_len, state);
		L(block_len, state);

		X(K, K, C[i]);
		S(block_len, K);
		P(block_len, K);
		L(block_len, K);

		X(state, state, K);


	}


	memcpy(K, state, 64 * sizeof(uint8_t));
	free(state);

	return 0;
exit:
	free(m);
	free(K);

	return -1;
}