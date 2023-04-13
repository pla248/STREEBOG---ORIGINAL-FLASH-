#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include "L_foo.h"

int L(int block_len, uint8_t* vector) {
	size_t* vector_long = NULL;
	uint8_t* vector_res = NULL;
	size_t X = 1;

	

	vector_long = (size_t*)malloc(8 * sizeof(size_t));
	if (!vector_long) goto exit;
	memset(vector_long, 0x00, 8*sizeof(size_t));


	vector_res = (uint8_t*)malloc(64 * sizeof(uint8_t));
	if (!vector_res) goto exit;
	memset(vector_res, 0x00, 64*sizeof(uint8_t));

	/*printf("Initialization block:        ");*/
	
	for (uint8_t i = 0; i < 8; i++)
	{
		vector_long[i] =    (((size_t)vector[8 * i] << 56) & 0xff00000000000000) ^
						(((size_t)vector[8 * i + 1] << 48) & 0x00ff000000000000) ^
						(((size_t)vector[8 * i + 2] << 40) & 0x0000ff0000000000) ^
						(((size_t)vector[8 * i + 3] << 32) & 0x000000ff00000000) ^
						(((size_t)vector[8 * i + 4] << 24) & 0x00000000ff000000) ^
						(((size_t)vector[8 * i + 5] << 16) & 0x0000000000ff0000) ^
						(((size_t)vector[8 * i + 6] << 8) & 0x000000000000ff00) ^
						 ((size_t)vector[8 * i + 7] & 0x00000000000000ff);
	
			/*printf("%zX", vector_long[i]);*/

	}
	/*printf("\n");
	printf("After linear transformation: ");*/
	for (uint8_t i = 0; i < 8; i++) // 8 vectors
	{
		for (uint8_t k = 0; k < 64; k++) //down
		{
			if (vector_long[i] & (X << (63 - k)))
			{
				for (uint8_t j = 0; j < 8; j++) // ---->
				{
					vector_res[i * 8 + j] ^= A[k * 8 + j];
				}
			}
		}
	}

	/*for (uint8_t i = 0; i <64; i++)
	{
		printf("%X",vector_res[i]);
	}*/
	memcpy(vector, vector_res, 64 * sizeof(uint8_t));
	//printf("\n");
	/*for (uint8_t i = 0; i < 64; i++)
	{
		printf("%X", vector[i]);
	}*/

	free(vector_long);
	free(vector_res);
	return (0);
	
exit:
	free(vector_long);
	free(vector_res);
	return -1;
}