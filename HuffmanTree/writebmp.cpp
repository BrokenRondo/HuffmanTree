#include "writebmp.h"

void generateBmp(BYTE * pData, int width, int height, char * filename)//生成Bmp图片，传递RGB值，传递图片像素大小，传递图片存储路径  
{
	int size = width * height * 3; // 每个像素点3个字节  
								   // 位图第一部分，文件信息  
	BMPFILEHEADER_T bfh;
	bfh.bfType = 0X4d42;  //bm  
	bfh.bfSize = size  // data size  
		+ sizeof(BMPFILEHEADER_T) // first section size  
		+ sizeof(BMPINFOHEADER_T) // second section size  
		;
	bfh.bfReserved1 = 0; // reserved  
	bfh.bfReserved2 = 0; // reserved  
	bfh.bfOffBits = bfh.bfSize - size;

	// 位图第二部分，数据信息  
	BMPINFOHEADER_T bih;
	bih.biSize = sizeof(BMPINFOHEADER_T);
	bih.biWidth = width;
	bih.biHeight = height;
	bih.biPlanes = 1;
	bih.biBitCount = 24;
	bih.biCompression = 0;
	bih.biSizeImage = size;
	bih.biXPelsPerMeter = 0;
	bih.biYPelsPerMeter = 0;
	bih.biClrUsed = 0;
	bih.biClrImportant = 0;
	FILE * fp = fopen(filename, "wb");
	if (!fp) return;
	fwrite(&bfh, 1, sizeof(BMPFILEHEADER_T), fp);
	fwrite(&bih, 1, sizeof(BMPINFOHEADER_T), fp);
	fwrite(pData, 1, size, fp);
	fclose(fp);
}
int writebmp(int height, int width)
{
	std::cout << "正在写入图片......";
	int i = 0, j = 0;
	struct pRGB {
		BYTE b;
		BYTE g;
		BYTE r;
	};  // 定义位图数据  
	pRGB *p = new pRGB[height*width];
	ifstream fin("e:/xxl/decode.txt");
	const char* decodebmp = "e:/xxl/write.bmp";
	memset(p, 0, height*width); // 设置背景为黑色  
								// 在中间画一个100*100的矩形  
	for (i = height - 1; i >= 0; i--) {
		for (j = width-1; j >= 0; j--) {
			//  pRGB[i][j].r = 0xff;  
			int t; fin >> t;
			p[i*width + j].r = t;
			p[i*width + j].g = t;
			p[i*width + j].b = t;
		}
	}
	// 生成BMP图片  
	generateBmp((BYTE*)p, width, height, (char*)decodebmp);
	cout << "写入图片完成！";
	return 0;
}