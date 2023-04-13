#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#define block_len  64

int X(uint8_t* result, uint8_t* vector2, uint8_t* vector) {
	if (vector == NULL or vector2 == NULL)
	{
		goto exit;
	}
	for (uint8_t i = 0; i < block_len; i++)
	{
		result[i] = vector2[i] ^ vector[i];
	}
return 0;
exit:
free(vector);
free(vector2);
return -1;
}