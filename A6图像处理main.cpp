#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include <process.h>
#include <iostream>
#include <TCHAR.h>
using namespace std;
#pragma warning (disable:4996)
/*BMP位图数据是4字节对齐*/
#define WIDTHBYTES(bits) ((DWORD)(((bits)+31) & (~31)) / 8)
#define WIDTHBYTES(bits) ((DWORD)((((bits)+31) / 32) * 4)

unsigned char *gPBmpBuf;     //指向图像数据的指针
int            gBmpWidth;    //图像的宽  
int            gBmpHeight;     //图像的高
RGBQUAD       *gPColorTable; //颜色表指针
int            gBiBitCount;   //图像类型，每个像素的位数
char           bmp[100] = "E:/test_pic.bmp";
char           saveBmp[100] = "E:/save_pic.bmp";

bool loadBmp(char *bmpName)
{
	/*以二进制方式打开bmp文件*/
	FILE *fp = fopen(bmpName, "rb");
	if (NULL == fp)
	{
		printf("open file \"%s\" failed \n", bmpName);
		return false;
	}

	/*跳过bmp文件结构体*/
	fseek(fp, sizeof(BITMAPFILEHEADER), 0);

	/*读取bmp文件信息头*/
	BITMAPINFOHEADER infoHead;
	fread(&infoHead, sizeof(BITMAPINFOHEADER), 1, fp);

	/*获取图像宽，高，像素位数*/
	gBmpWidth = infoHead.biWidth;
	gBmpHeight = infoHead.biHeight;
	gBiBitCount = infoHead.biBitCount;

	/*获取每行像素所占内存大小(必须为4的倍数)*/
	int lineByte = (gBmpWidth*gBiBitCount / 8 + 3) / 4 * 4;

	/*灰度图像有颜色表，且颜色表表项为256,24-位真彩色图像就不使用彩色板*/
	if (8 == gBiBitCount)
	{
		gPColorTable = (RGBQUAD *)malloc(sizeof(RGBQUAD) * 256);
		fread(gPColorTable, sizeof(RGBQUAD), 1, fp);
	}

	/*申请位图数据空间，并将位图数据存放到内存*/
	gPBmpBuf = (unsigned char *)malloc(sizeof(unsigned char)*gBmpHeight*lineByte);
	fread(gPBmpBuf, 1, gBmpHeight*lineByte, fp);

	fclose(fp);

	return true;
}

bool storeBmp(char *bmpName, unsigned char *imgBuf, int width, int height,
	int gBiBitCount, RGBQUAD *gPColorTable)
{
	/*对位图数据进行判空操作*/
	if (NULL == imgBuf)
	{
		return false;
	}

	/*根据像素位数，判断当前颜色表大小*/
	int colorTableSize = 0;
	if (gBiBitCount == 8)
	{
		/*
		   1字节用于蓝色分量
		   1字节用于绿色分量
		   1字节用于红色分量
		   1字节用于填充符(设置为0)
		 */
		colorTableSize = 1024; /*4*256*/
	}

	/*待存储图像数据每行像素的大小(4的倍数)*/
	int lineByte = (gBmpWidth*gBiBitCount / 8 + 3) / 4 * 4;

	FILE *fp = fopen(bmpName, "wb");
	if (NULL == fp)
	{
		printf("creat file failed !\n");
		return false;
	}

	/*填写位图文件头结构体*/
	BITMAPFILEHEADER fileHead;
	fileHead.bfType = 0x4D42; //bmp类型
	fileHead.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) +
		colorTableSize + lineByte * height;
	fileHead.bfReserved1 = 0;
	fileHead.bfReserved2 = 0;
	fileHead.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) +
		colorTableSize;
	fwrite(&fileHead, sizeof(BITMAPFILEHEADER), 1, fp);

	/*填写位图信息结构体*/
	BITMAPINFOHEADER infoHead;
	infoHead.biBitCount = gBiBitCount;
	infoHead.biClrImportant = 0;
	infoHead.biClrUsed = 0;
	infoHead.biCompression = 0;
	infoHead.biHeight = height;
	infoHead.biPlanes = 1;
	infoHead.biSize = 40;
	infoHead.biSizeImage = lineByte * height;
	infoHead.biWidth = width;
	infoHead.biXPelsPerMeter = 0;
	infoHead.biYPelsPerMeter = 0;
	fwrite(&infoHead, sizeof(BITMAPINFOHEADER), 1, fp);

	/*填写颜色表*/
	if (gBiBitCount == 8)
	{
		fwrite(&gPColorTable, sizeof(RGBQUAD), 256, fp);
	}

	/*写位图数据进文件*/
	fwrite(imgBuf, height * lineByte, 1, fp);

	fclose(fp);

	return true;
}

int _tmain(int argc, _TCHAR* argv[])
{

	bool ret = false;

	ret |= loadBmp(bmp);
	ret |= storeBmp(saveBmp, gPBmpBuf, gBmpWidth, gBmpHeight, gBiBitCount, gPColorTable);

	if (false == ret)
	{
		printf("excut fail! \n");
	}
	else if (true == ret)
	{
		printf("excut success!\n");
	}

	if (gBiBitCount == 8)
	{
		free(gPColorTable);
	}

	free(gPBmpBuf);

	return 0;
}
