#pragma once
#include <pshpack2.h>  
#include "stdio.h"  
#include "stdlib.h"  
#include "string.h"  
#include <fstream>
#include <iostream>
using namespace std;
//typedef long BOOL;
typedef long LONG;
typedef unsigned char BYTE;
typedef unsigned long DWORD;
typedef unsigned short WORD;

//λͼ�ļ�ͷ�ļ�����  
//���в������ļ�������Ϣ�����ڽṹ����ڴ�ṹ������Ҫ�Ǽ��˵Ļ���������ȷ�Ķ�ȡ�ļ���Ϣ��  
typedef struct {
	WORD    bfType;//�ļ����ͣ�������0x424D,���ַ���BM��  
	DWORD   bfSize;//�ļ���С  
	WORD    bfReserved1;//������  
	WORD    bfReserved2;//������  
	DWORD   bfOffBits;//���ļ�ͷ��ʵ��λͼ���ݵ�ƫ���ֽ���  
} BMPFILEHEADER_T;

struct BMPFILEHEADER_S {
	WORD    bfType;
	DWORD   bfSize;
	WORD    bfReserved1;
	WORD    bfReserved2;
	DWORD   bfOffBits;
};
typedef struct {
	DWORD      biSize;//��Ϣͷ��С  
	LONG       biWidth;//ͼ����  
	LONG       biHeight;//ͼ��߶�  
	WORD       biPlanes;//λƽ����������Ϊ1  
	WORD       biBitCount;//ÿ����λ��  
	DWORD      biCompression;//ѹ������  
	DWORD      biSizeImage;//ѹ��ͼ���С�ֽ���  
	LONG       biXPelsPerMeter;//ˮƽ�ֱ���  
	LONG       biYPelsPerMeter;//��ֱ�ֱ���  
	DWORD      biClrUsed;//λͼʵ���õ���ɫ����  
	DWORD      biClrImportant;//��λͼ����Ҫ��ɫ����  
} BMPINFOHEADER_T;//λͼ��Ϣͷ����  
void generateBmp(BYTE * pData, int width, int height, char * filename);
int writebmp(int height, int width);