#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include <process.h>
#include <iostream>
#include "BMP.h"
#pragma warning (disable:4996)
BITMAPFILEHEADER bmfh;
BITMAPINFOHEADER bmih;
BYTE *imgData;//定义一个字节型的指针变量
bool bReadBMFH = false;
bool bReadBMIH = false;
bool bReadPixel = false;
//检查路径是否合法：文件能打开；以bmp为后缀名
int CheckFilePath(char *filepath);
//读入位图的文件头
int ReadFileHeader(char *filepath, BITMAPFILEHEADER *bmfh);
//打印位图的文件头
void PrintFileHeader(BITMAPFILEHEADER *bmfh);
//读入位图的信息头
int ReadInfoHeader(char *filepath, BITMAPINFOHEADER *bmih);
//打印位图的信息头
void PrintInfoHeader(BITMAPINFOHEADER *bmih);
//创建8位位图的调色板
int CreatePalette(RGBQUAD pal[]);
//读入位图的像素数据
int ReadPixelData(char *filepath, BYTE *imgData);
//计算每行像素所占的字节数
LONG GetLineBytes(int imgWidth, int bitCount);
//打印位图的像素数据
void PrintPixelData(BYTE *imgData, int width, int height, int bitCount);
//打印菜单选项
void PrintMenu();
//另存为位图
int SaveAsImage(char *filepath);
//显示位图
void ShowImage(char * filepath);
int main()
{
	char filepath[256];//开辟了一个256大小的字符型一维数组
	char saveasfilepath[256];
	int i;
	int width;
	int height;
	int bitCount;
	DWORD dwLineBytes;
	int select;
	int q = 0;

	system("echo off");
	system("color 2");

	printf("-----------TIMimage-----------\n");
	printf("Input the path of the BMP file:\n");
	//gets(filepath);//从键盘输入的字符放在filepath数组中
	fgets(filepath, 250, stdin);
	i = CheckFilePath(filepath);//调用函数
	if (i == -1)
	{
		return -1;
	}

	do
	{
		PrintMenu();
		scanf("%u", &select);
		switch (select)
		{
		case 0:
		{
			printf("Input the path of the BMP file:\n");
			scanf("%s", filepath);
			CheckFilePath(filepath);
			break;
		}
		case 1:
		{
			i = ReadFileHeader(filepath, &bmfh);
			if (i != -1)
			{
				printf("Read the file header successfully.\n");
				bReadBMFH = true;
				break;
			}
			else
			{
				printf("Read the file header failed.\n");
				bReadBMFH = false;
				q = 1;
				break;
			}
		}
		case 2:
		{
			i = ReadInfoHeader(filepath, &bmih);
			if (i != -1)
			{
				printf("Read the info header successfully.\n");
				bReadBMIH = true;
				break;
			}
			else
			{
				printf("Read the info header failed.\n");
				bReadBMIH = false;
				q = 1;
				break;
			}
		}
		case 3:
		{
			if (!bReadBMIH)
			{
				printf("Please read the info header at first.\n");
				break;
			}
			height = bmih.biHeight;
			width = bmih.biWidth;
			bitCount = bmih.biBitCount;
			dwLineBytes = GetLineBytes(width, bitCount);
			imgData = (BYTE*)malloc(dwLineBytes*height * sizeof(BYTE));
			if (!imgData)
			{
				printf("Can not allocate memory for the image.\n");
				q = 1;
				break;
			}
			i = ReadPixelData(filepath, imgData);
			if (i == -1)
			{
				printf("Read the pixel data failed.\n");
				bReadPixel = false;
				q = 1;
				break;
			}
			else
			{
				printf("Read the pixel data successfully.\n");
				bReadPixel = true;
				break;
			}
		}
		case 4:
		{
			if (bReadBMFH)
			{
				PrintFileHeader(&bmfh);
				break;
			}
			else
			{
				printf("Please read the file header at first.\n");
				break;
			}
		}
		case 5:
		{
			if (bReadBMIH)
			{
				PrintInfoHeader(&bmih);
				break;
			}
			else
			{
				printf("Please read the info header at first.\n");
				break;
			}
		}
		case 6:
		{
			if (bReadPixel)
			{
				PrintPixelData(imgData, width, height, bitCount);
				break;
			}
			else
			{
				printf("Please read the pixel data at first.\n");
				break;
			}
		}
		case 7:
		{
			ShowImage(filepath);
			break;
		}
		case 8:
		{
			printf("Input the path(ex. d://poon.bmp) you want to save:\n");
			scanf("%s", saveasfilepath);
			i = SaveAsImage(saveasfilepath);
			if (i == -1)
			{
				printf("Error: failed to save the image.\n");
				break;
			}
			break;
		}
		default:
			q = 1;
			break;
		}
		select = 9527;
	} while (q == 0);
	system("pause");
	return 0;
}
int ReadFileHeader(char *filepath, BITMAPFILEHEADER *bmfh)
{
	FILE *fp;
	fp = fopen(filepath, "rb");
	if (!fp)
	{
		printf("Can not open the file:%s\n", filepath);
		return -1;
	}
	if (fread(&bmfh->bfType, sizeof(WORD), 1, fp) != 1)
	{
		printf("Can not read bfType in the file header.\n");
		fclose(fp);
		return -1;
	}
	if (fread(&bmfh->bfSize, sizeof(DWORD), 1, fp) != 1)
	{
		printf("Can not read bfSize in the file header.\n");
		fclose(fp);
		return -1;
	}
	if (fread(&bmfh->bfReserved1, sizeof(WORD), 1, fp) != 1)
	{
		printf("Can not read bfReserved1 in the file header.\n");
		fclose(fp);
		return -1;
	}
	if (fread(&bmfh->bfReserved2, sizeof(WORD), 1, fp) != 1)
	{
		printf("Can not read bfReserved2 in the file header.\n");
		fclose(fp);
		return -1;
	}
	if (fread(&bmfh->bfOffBits, sizeof(DWORD), 1, fp) != 1)
	{
		printf("Can not read bfOffBits in the file header.\n");
		fclose(fp);
		return -1;
	}
	fclose(fp);
	return 0;
}
int ReadInfoHeader(char *filepath, BITMAPINFOHEADER *bmih)
{
	FILE *fp;
	fp = fopen(filepath, "rb");
	if (!fp)
	{
		printf("Can not open the file:%s\n", filepath);
		return -1;
	}
	fseek(fp, 14, SEEK_SET);
	if (fread(&bmih->biSize, sizeof(DWORD), 1, fp) != 1)
	{
		printf("Can not read biSize in the info header.\n");
		fclose(fp);
		return -1;
	}
	if (fread(&bmih->biWidth, sizeof(LONG), 1, fp) != 1)
	{
		printf("Can not read biWidth in the info header.\n");
		fclose(fp);
		return -1;
	}
	if (fread(&bmih->biHeight, sizeof(LONG), 1, fp) != 1)
	{
		printf("Can not read biHeight in the info header.\n");
		fclose(fp);
		return -1;
	}
	if (fread(&bmih->biPlanes, sizeof(WORD), 1, fp) != 1)
	{
		printf("Can not read biPlanes in the info header.\n");
		fclose(fp);
		return -1;
	}
	if (fread(&bmih->biBitCount, sizeof(WORD), 1, fp) != 1)
	{
		printf("Can not read biBitCount in the info header.\n");
		fclose(fp);
		return -1;
	}
	if (fread(&bmih->biCompression, sizeof(DWORD), 1, fp) != 1)
	{
		printf("Can not read biCompression in the info header.\n");
		fclose(fp);
		return -1;
	}
	if (fread(&bmih->biSizeImage, sizeof(DWORD), 1, fp) != 1)
	{
		printf("Can not read biSizeImage in the info header.\n");
		fclose(fp);
		return -1;
	}
	if (fread(&bmih->biXPelsPerMeter, sizeof(LONG), 1, fp) != 1)
	{
		printf("Can not read biXPelsPerMeter in the info header.\n");
		fclose(fp);
		return -1;
	}
	if (fread(&bmih->biYPelsPerMeter, sizeof(LONG), 1, fp) != 1)
	{
		printf("Can not read biYPelsPerMeter in the info header.\n");
		fclose(fp);
		return -1;
	}
	if (fread(&bmih->biClrUsed, sizeof(DWORD), 1, fp) != 1)
	{
		printf("Can not read biClrUsed in the info header.\n");
		fclose(fp);
		return -1;
	}
	if (fread(&bmih->biClrImportant, sizeof(DWORD), 1, fp) != 1)
	{
		printf("Can not read biClrImportant in the info header.\n");
		fclose(fp);
		return -1;
	}
	fclose(fp);
	return 0;
}
int CreatePalette(RGBQUAD pal[])
{
	int i;
	if (sizeof(pal) / sizeof(RGBQUAD) != 256)
	{
		printf("The size of the palette must be 256.\n");
		return -1;
	}
	for (i = 0; i < 256; i++)
	{
		pal[i].rgbBlue = i;
		pal[i].rgbGreen = i;
		pal[i].rgbRed = i;
		pal[i].rgbReserved = 0;
	}
	return 0;
}
int ReadPixelData(char *filepath, BYTE *imgData)
{
	BITMAPINFOHEADER bmih;
	BITMAPFILEHEADER bmfh;
	BYTE *data;
	FILE *fp;
	int n;
	int width;
	int height;
	int bitCount;
	DWORD dwLineBytes;
	n = ReadFileHeader(filepath, &bmfh);
	if (n == -1)
	{
		printf("Can not read the file header of the BMP file.\n");
		return -1;
	}
	n = ReadInfoHeader(filepath, &bmih);
	if (n == -1)
	{
		printf("Can not read the info header of the BMP file.\n");
		return -1;
	}
	width = bmih.biWidth;
	height = bmih.biHeight;
	bitCount = bmih.biBitCount;
	dwLineBytes = GetLineBytes(width, bitCount);
	if (_msize(imgData) != (dwLineBytes*height))
	{
		printf("The size you allocate for the pixel data is not right.\n");
		printf("Fittable size: %ld bytes.\n", (dwLineBytes*height));
		printf("Your size: %ld bytes.\n", sizeof(imgData));
		return -1;
	}
	data = (BYTE*)malloc(dwLineBytes*height * sizeof(BYTE));
	if (!data)
	{
		printf("Can not allocate memory for the pixel data.\n");
		return -1;
	}
	fp = fopen(filepath, "rb");
	if (!fp)
	{
		printf("Can not open the file: %s\n", filepath);
		free(data);
		return -1;
	}
	if (bitCount == 8)
	{
		fseek(fp, bmfh.bfOffBits, SEEK_SET);
	}
	else if (bitCount == 24)
	{
		fseek(fp, bmfh.bfOffBits, SEEK_SET);
	}
	else
	{
		printf("Only Support: 8 or 24 bits.\n");
		free(data);
		fclose(fp);
		return -1;
	}
	if (fread(data, dwLineBytes*height * sizeof(BYTE), 1, fp) != 1)
	{
		printf("Can not read the pixel data.\n");
		free(data);
		fclose(fp);
		return -1;
	}
	memcpy(imgData, data, dwLineBytes*height * sizeof(BYTE));
	free(data);
	fclose(fp);
	return 0;
}
void PrintFileHeader(BITMAPFILEHEADER *bmfh)
{
	printf("The contents in the file header of the BMP file:\n");
	printf("bfOffBits: %ld\n", bmfh->bfOffBits);
	printf("bfReserved1: %ld\n", bmfh->bfReserved1);
	printf("bfReserved2: %ld\n", bmfh->bfReserved2);
	printf("bfSize: %ld\n", bmfh->bfSize);
	printf("bfType: %ld\n", bmfh->bfType);
}
void PrintInfoHeader(BITMAPINFOHEADER *bmih)
{
	printf("The content in the info header of the BMP file:\n");
	printf("biBitCount: %ld\n", bmih->biBitCount);
	printf("biClrImportant: %ld\n", bmih->biClrImportant);
	printf("biClrUsed: %ld\n", bmih->biClrUsed);
	printf("biCompression: %ld\n", bmih->biCompression);
	printf("biHeight: %ld\n", bmih->biHeight);
	printf("biPlanes: %ld\n", bmih->biPlanes);
	printf("biSize: %ld\n", bmih->biSize);
	printf("biSizeImage: %ld\n", bmih->biSizeImage);
	printf("biWidth: %ld\n", bmih->biWidth);
	printf("biXPelsPerMeter: %ld\n", bmih->biXPelsPerMeter);
	printf("biYPelsPerMeter: %ld\n", bmih->biYPelsPerMeter);
}
LONG GetLineBytes(int imgWidth, int bitCount)
{
	return (imgWidth*bitCount + 31) / 32 * 4;
}
void PrintPixelData(BYTE *imgData, int width, int height, int bitCount)
{
	int i;
	int j;
	int p;
	DWORD dwLineBytes = GetLineBytes(width, bitCount);
	if (bitCount == 8)
	{
		for (i = 0; i < height; i++)
		{
			for (j = 0; j < width; j++)
			{
				p = *(imgData + dwLineBytes * (height - 1 - i) + j);
				printf("%d,", p);
			}
			printf("\n");
		}
	}
	else if (bitCount == 24)
	{
		for (i = 0; i < height; i++)
		{
			for (j = 0; j < width * 3; j++)
			{
				printf("(");
				p = *(imgData + dwLineBytes * (height - 1 - i) + j);
				printf("%d,", p);
				j++;
				p = *(imgData + dwLineBytes * (height - 1 - i) + j);
				printf("%d,", p);
				j++;
				p = *(imgData + dwLineBytes * (height - 1 - i) + j);
				printf("%d) ", p);
			}
			printf("\n");
		}
	}
	else
	{
		printf("Only supported: 8 or 24 bits.\n");
	}
}
int CheckFilePath(char *filepath)
{
	FILE *fp;
	int len = strlen(filepath) / sizeof(char);
	char ext[3];
	if (filepath[0] != int('\"'))
	{
		strncpy(ext, &filepath[len - 3], 3);
		if (!(ext[0] == 'b' && ext[1] == 'm' && ext[2] == 'p'))
		{
			printf("Error: The file is not a BMP file.\n");
			printf("Error: The extention of the filename must be 'bmp',not 'BMP'\n");
			return -1;
		}
		fp = fopen(filepath, "r");
		if (!fp)
		{
			printf("Error: The path is not correct.\n");
			return -1;
		}
		fclose(fp);
	}
	else
	{
		printf("Error: The path must not include blank space.\n");
		return -1;
	}
	return 0;
}
void PrintMenu()
{
	printf(" -----Choose Your Operation-----\n");
	printf("| 0-----Input the image path    |\n");
	printf("| 1-----Read the file header    |\n");
	printf("| 2-----Read the info header    |\n");
	printf("| 3-----Read the pixel data     |\n");
	printf("| 4-----Print the file header   |\n");
	printf("| 5-----Print the info header   |\n");
	printf("| 6-----Print the pixel data    |\n");
	printf("| 7-----View the original image |\n");
	printf("| 8-----Save as the image       |\n");
	printf("| other-----Exit the program    |\n");
	printf(" -------------------------------\n");
}
int SaveAsImage(char *filepath)
{
	FILE *fp;
	RGBQUAD pal[256];
	int i;
	int height;
	DWORD dwLineBytes;
	if (!bReadBMFH)
	{
		printf("Error: read the file header at first.\n");
		return -1;
	}
	if (!bReadBMIH)
	{
		printf("Error: read the info header at first.\n");
		return -1;
	}
	if (bmih.biBitCount != 8 && bmih.biBitCount != 24)
	{
		printf("Error: only supported 8 or 24 bits.\n");
		return -1;
	}
	height = bmih.biHeight;
	dwLineBytes = GetLineBytes(bmih.biWidth, bmih.biBitCount);
	if (!bReadPixel)
	{
		printf("Error: read the pixel data at first.\n");
		return -1;
	}
	fp = fopen(filepath, "wb");
	if (!fp)
	{
		printf("Error: Can not open the file:%s\n", filepath);
		return -1;
	}

	for (i = 0; i < 256; i++)
	{
		pal[i].rgbReserved = 0;
		pal[i].rgbBlue = i;
		pal[i].rgbGreen = i;
		pal[i].rgbRed = i;
	}

	if (fwrite(&bmfh.bfType, sizeof(WORD), 1, fp) != 1)
	{
		printf("Can not write bfType in the file header.\n");
		fclose(fp);
		return -1;
	}

	if (fwrite(&bmfh.bfSize, sizeof(DWORD), 1, fp) != 1)
	{
		printf("Can not write bfSize in the file header.\n");
		fclose(fp);
		return -1;
	}

	if (fwrite(&bmfh.bfReserved1, sizeof(WORD), 1, fp) != 1)
	{
		printf("Can not write bfReserved1 in the file header.\n");
		fclose(fp);
		return -1;
	}

	if (fwrite(&bmfh.bfReserved2, sizeof(WORD), 1, fp) != 1)
	{
		printf("Can not write bfReserved2 in the file header.\n");
		fclose(fp);
		return -1;
	}

	if (fwrite(&bmfh.bfOffBits, sizeof(DWORD), 1, fp) != 1)
	{
		printf("Can not write bfOffBits in the file header.\n");
		fclose(fp);
		return -1;
	}
	if (fwrite(&bmih.biSize, sizeof(DWORD), 1, fp) != 1)
	{
		printf("Can not write biSize in the info header.\n");
		fclose(fp);
		return -1;
	}

	if (fwrite(&bmih.biWidth, sizeof(LONG), 1, fp) != 1)
	{
		printf("Can not write biWidth in the info header.\n");
		fclose(fp);
		return -1;
	}

	if (fwrite(&bmih.biHeight, sizeof(LONG), 1, fp) != 1)
	{
		printf("Can not write biHeight in the info header.\n");
		fclose(fp);
		return -1;
	}

	if (fwrite(&bmih.biPlanes, sizeof(WORD), 1, fp) != 1)
	{
		printf("Can not write biPlanes in the info header.\n");
		fclose(fp);
		return -1;
	}

	if (fwrite(&bmih.biBitCount, sizeof(WORD), 1, fp) != 1)
	{
		printf("Can not write biBitCount in the info header.\n");
		fclose(fp);
		return -1;
	}

	if (fwrite(&bmih.biCompression, sizeof(DWORD), 1, fp) != 1)
	{
		printf("Can not write biCompression in the info header.\n");
		fclose(fp);
		return -1;
	}

	if (fwrite(&bmih.biSizeImage, sizeof(DWORD), 1, fp) != 1)
	{
		printf("Can not write biSizeImage in the info header.\n");
		fclose(fp);
		return -1;
	}

	if (fwrite(&bmih.biXPelsPerMeter, sizeof(LONG), 1, fp) != 1)
	{
		printf("Can not write biXPelsPerMeter in the info header.\n");
		fclose(fp);
		return -1;
	}

	if (fwrite(&bmih.biYPelsPerMeter, sizeof(LONG), 1, fp) != 1)
	{
		printf("Can not write biYPelsPerMeter in the info header.\n");
		fclose(fp);
		return -1;
	}

	if (fwrite(&bmih.biClrUsed, sizeof(DWORD), 1, fp) != 1)
	{
		printf("Can not write biClrUsed in the info header.\n");
		fclose(fp);
		return -1;
	}

	if (fwrite(&bmih.biClrImportant, sizeof(DWORD), 1, fp) != 1)
	{
		printf("Can not write biClrImportant in the info header.\n");
		fclose(fp);
		return -1;
	}

	if (bmih.biBitCount == 8)
	{
		if (fwrite(pal, sizeof(RGBQUAD), 256, fp) != 256)
		{
			printf("Error: can not write the color palette.\n");
			fclose(fp);
			return -1;
		}
	}

	if (fwrite(imgData, height*dwLineBytes, 1, fp) != 1)
	{
		printf("Error: can not write the pixel data.\n");
		fclose(fp);
		return -1;
	}

	fclose(fp);
	printf("Save As the image successfully.\n");
	return 0;
}
void ShowImage(char * filepath)
{
	char cmd[266];
	strcpy(cmd, "start ");
	strcat(cmd, filepath);
	printf("%s\n", cmd);
	system(cmd);
}
