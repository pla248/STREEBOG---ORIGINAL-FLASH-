#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "const.h"

int S(int block_len, uint8_t* vector) {

	if (vector == NULL)
	{
		goto exit;
	}

	for (int i = 0; i < block_len; i++)
	{
		vector[i] = Pi[vector[i]];
	}
	return 0;
exit: 
	free(vector);
	return -1;

}
