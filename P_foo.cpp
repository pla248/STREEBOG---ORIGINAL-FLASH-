#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

int P(int block_len, uint8_t* vector) {
	
	if (vector == NULL)
		{
			goto exit;
		}

	for (char i = 0; i < block_len; i++)
	{

		
		if (i >= (i >> 3) + (i % 8) * 8)
			continue;
		else 
		{
			vector[(i >> 3) + (i % 8) * 8] ^= vector[i];
			vector[i] ^= vector[(i >> 3) + (i % 8) * 8];
			vector[(i >> 3) + (i % 8) * 8] ^= vector[i];
		}
	}
	return 0;
exit:
	free(vector);
	return -1;

}