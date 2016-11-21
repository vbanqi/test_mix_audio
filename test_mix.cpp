// test_mix.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define BLOCK_BUF 256
/************************************************************************/
/* 混音算法，平均值算法
/************************************************************************/
int _tmain(int argc, _TCHAR* argv[])
{
	FILE* fp1, *fp2, *fp3;
	int erro = fopen_s(&fp1, "D:\\speaker.pcm", "rb");
	if (erro)
	{
		return 1;
	}
	erro = fopen_s(&fp2, "D:\\mic.pcm", "rb");
	if (erro)
	{
		return 1;
	}

	erro = fopen_s(&fp3, "D:\\test_mix_audio.pcm", "ab+");
	if (erro)
	{
		return 1;
	}
	float buf1[BLOCK_BUF];
	float buf2[BLOCK_BUF];

	size_t size;
	size_t index1=0;
	size_t index2=0;
	while (true)
	{
		size = fread(buf1, 4, BLOCK_BUF, fp1);
		if (size < BLOCK_BUF)
		{
			break;
		}
		size = fread(buf2, 4, BLOCK_BUF, fp2);

		if (size < BLOCK_BUF)
		{
			break;
		}
		for (int i = 0; i < BLOCK_BUF ; i++)
		{
			buf1[i] = buf1[i] / 2.f + buf2[i] / 2.f;
		}

		fwrite(buf1, 4, BLOCK_BUF, fp3);
	}
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	return 0;
}

