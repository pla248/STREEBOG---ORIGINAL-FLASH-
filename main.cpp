#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <iostream>
#include "all_the_func.h"
#define block_len  64

int main(int argc, const char* argv[]) {
	
	uint8_t message_str[] = { 0xfb,0xe2,0xe5,0xf0,0xee,0xe3,0xc8,0x20,0xfb,0xea,0xfa,0xeb,0xef,0x20,0xff,0xfb,0xf0,0xe1,
		0xe0,0xf0,0xf5,0x20,0xe0,0xed,0x20,0xe8,0xec,0xe0,0xeb,0xe5,0xf0,0xf2,0xf1,0x20,
		0xff,0xf0,0xee,0xec,0x20,0xf1,0x20,0xfa,0xf2,0xfe,0xe5,0xe2,0x20,0x2c,0xe8,0xf6,
		0xf3,0xed,0xe2,0x20,0xe8,0xe6,0xee,0xe1,0xe8,0xf0,0xf2,0xd1,0x20,0x2c,0xe8,0xf0,0xf2,0xe5,0xe2,0x20,0xe5,0xd1 };

	uint8_t number[] = { 0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00,0x00 ,0x00 ,0x00 ,0x00 ,
		0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,
		0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x0 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,
		0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 ,0x00 };

	


	uint8_t* block;
	block = message_str;
	int output_length = 512;
	uint8_t N[block_len] = { 0 };
	uint8_t iv[block_len] = { 0 };
	uint8_t sigma[block_len] = { 0 };


	
	
	if (output_length != 256 and output_length != 512)
	{
		printf("Initialization vector don`t exist!\n");
		 exit(0);

	}

	if (output_length == 512)
	{
		for (uint8_t i = 0; i < block_len; i++)
		{
			N[i] = 0x00;
			sigma[i] = 0x00;
			iv[i] = 0x00;

		}
		

	}

	if (output_length == 256)
	{
		for (uint8_t i = 0; i < block_len; i++)
		{
			N[i] = 0x00;
			sigma[i] = 0x00;
			iv[i] = 0x01;

		}

	}


	int message_len = sizeof(message_str);
	int message_lenBITS = sizeof(message_str)*8;

	//STEP 2//
	if (message_len>64)
	{
		uint8_t* last64bytes = (uint8_t*)malloc(64 * sizeof(uint8_t));
		if (!last64bytes)
		{
			printf("Memory allocation error!");
			free(last64bytes);
			exit(-1);
		}

		int y = 1;


		while (message_len > 64)
		{

			memcpy(last64bytes, block + message_len - (64 * y), 64 * sizeof(uint8_t));
			G(iv, N, iv, last64bytes );
			number[63] = 512 % 256;
			number[62] = 512 / 256;
			AddModulo512(N, number, N);
			number[63] = 0x00;
			number[62] = 0x00;
			AddModulo512(sigma, last64bytes, sigma);
			message_len -= 64;
			message_lenBITS -= 512;
			y++;
		}
		free(last64bytes);
	}


		//STEP 3//

	uint8_t* M = (uint8_t*)malloc(64 * sizeof(uint8_t));
	if (!M)
	{
		printf("Memory allocation error!");
		free(M);
		exit(-1);
	}
	if (message_len != 64)
	{
		memcpy(M + (64 - message_len), block, message_len * sizeof(uint8_t));

		if (message_len != 63)
		{
			memset(M, 0x00, (63 - message_len) * sizeof(uint8_t));
		}
		
		memset(M + (63 - message_len), 0x01, sizeof(uint8_t));
	}
	else
	{
		memcpy(M, block, block_len * sizeof(uint8_t));
	}




	uint8_t* hash = (uint8_t*)malloc(64 * sizeof(uint8_t));
	if (!hash)
	{
		printf("Memory allocation error!");
		free(hash);
		exit(-1);
	}
	memset(hash, 0x00, 64 * sizeof(uint8_t));

	G(hash, N, iv, M);
	number[63] = message_lenBITS % 256;
	number[62] = message_lenBITS / 256;
	AddModulo512(N, number, N);
	number[63] = 0x00;
	number[62] = 0x00;
	AddModulo512(sigma, M, sigma);
	G(hash, number, hash, N);
	G(hash, number, hash, sigma);


	if (output_length == 512)
	{
		uint8_t hash_final[512] = { 0 };
		uint8_t* hh = hash_final;
		memcpy(hh, hash, 64);
		free(hash);

		printf("\n HASH = ");

		for (uint8_t i = 0; i < 64; i++)
		{
			printf("%X", hash_final[i]);
		}
	}

	else
	{
		uint8_t hash_final[256] = { 0 };
		uint8_t* hh = hash_final;
		memcpy(hh, hash, 32);
		free(hash);
		printf("\nHASH = ");

		for (uint8_t i = 0; i < 32; i++)
		{
			printf("%X", hash_final[i]);
		}
	}


	
	
	free(M);

	return 0;





	
}




// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
