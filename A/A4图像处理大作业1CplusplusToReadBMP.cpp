#include <stdio.h>    
#include "CplusplusToReadBMP.h"    
#include "stdlib.h"    
#include <iostream>    
using namespace std;

//变量定义    
BITMAPFILEHEADER strHead;
RGBQUAD strPla[256];//256色调色板    
BITMAPINFOHEADER strInfo;
IMAGEDATA imagedata[256][256];//存储像素信息    

//显示位图文件头信息    
void showBmpHead(BITMAPFILEHEADER pBmpHead) {
	cout << "位图文件头:" << endl;
	//cout<<"bfType value is "<<hex<<pBmpHead.bfType<<endl;    
	cout << "文件大小:" << pBmpHead.bfSize << endl;
	//printf("文件大小:%d\n",pBmpHead.bfSize);    
	cout << "保留字_1:" << pBmpHead.bfReserved1 << endl;
	cout << "保留字_2:" << pBmpHead.bfReserved2 << endl;
	cout << "实际位图数据的偏移字节数:" << pBmpHead.bfOffBits << endl << endl;
}

void showBmpInforHead(tagBITMAPINFOHEADER pBmpInforHead) {
	cout << "位图信息头:" << endl;
	cout << "结构体的长度:" << pBmpInforHead.biSize << endl;
	cout << "位图宽:" << pBmpInforHead.biWidth << endl;
	cout << "位图高:" << pBmpInforHead.biHeight << endl;
	cout << "biPlanes平面数:" << pBmpInforHead.biPlanes << endl;
	cout << "biBitCount采用颜色位数:" << pBmpInforHead.biBitCount << endl;
	cout << "压缩方式:" << pBmpInforHead.biCompression << endl;
	cout << "biSizeImage实际位图数据占用的字节数:" << pBmpInforHead.biSizeImage << endl;
	cout << "X方向分辨率:" << pBmpInforHead.biXPelsPerMeter << endl;
	cout << "Y方向分辨率:" << pBmpInforHead.biYPelsPerMeter << endl;
	cout << "使用的颜色数:" << pBmpInforHead.biClrUsed << endl;
	cout << "重要颜色数:" << pBmpInforHead.biClrImportant << endl;
}

tagRGBQUAD* ReadFile(char *strFile) {
	FILE *fpi, *fpw;
	fpi = fopen(strFile, "rb");
	if (fpi != NULL) {
		//先读取文件类型    
		WORD bfType;
		fread(&bfType, 1, sizeof(WORD), fpi);
		if (0x4d42 != bfType) {
			cout << "the file is not a bmp file!" << endl;
			return NULL;
		}
		//读取bmp文件的文件头和信息头    
		fread(&strHead, 1, sizeof(tagBITMAPFILEHEADER), fpi);
		showBmpHead(strHead);//显示文件头    
		fread(&strInfo, 1, sizeof(tagBITMAPINFOHEADER), fpi);
		showBmpInforHead(strInfo);//显示文件信息头    


		//读取调色板    
		for (int nCounti = 0; nCounti < strInfo.biClrUsed; nCounti++) {
			//存储的时候，一般去掉保留字rgbReserved    
			fread((char *)&strPla[nCounti].rgbBlue, 1, sizeof(BYTE), fpi);
			fread((char *)&strPla[nCounti].rgbGreen, 1, sizeof(BYTE), fpi);
			fread((char *)&strPla[nCounti].rgbRed, 1, sizeof(BYTE), fpi);
			cout << "strPla[nCounti].rgbBlue" << strPla[nCounti].rgbBlue << endl;
			cout << "strPla[nCounti].rgbGreen" << strPla[nCounti].rgbGreen << endl;
			cout << "strPla[nCounti].rgbRed" << strPla[nCounti].rgbRed << endl;
		}

		//读出图片的像素数据    
		memset(imagedata, 0, sizeof(IMAGEDATA) * 256 * 256);
		//fseek(fpi,54,SEEK_SET);    
		fread(imagedata, sizeof(struct tagIMAGEDATA) * strInfo.biWidth, strInfo.biHeight, fpi);
		//for(int i = 0;i < strInfo.biWidth;++i)    
		for (int i = 0; i < 1; ++i)//只输出第一行数据    
		{
			for (int j = 0; j < strInfo.biHeight; ++j) {
				printf("%d  ", imagedata[i][j].green);
				// cout<<imagedata[0][j].green+ " ";    
				if ((i * strInfo.biHeight + j + 1) % 5 == 0)
					cout << endl;
			}
		}

		fclose(fpi);
	}
	else {
		cout << "file open error!" << endl;
		return NULL;
	}

	//保存bmp图片    
	if ((fpw = fopen("b.bmp", "wb")) == NULL) {
		cout << "create the bmp file error!" << endl;
		return NULL;
	}
	WORD bfType = 0x4d42;
	fwrite(&bfType, 1, sizeof(WORD), fpw);
	//fpw +=2;    
	fwrite(&strHead, 1, sizeof(tagBITMAPFILEHEADER), fpw);
	fwrite(&strInfo, 1, sizeof(tagBITMAPINFOHEADER), fpw);
	//保存调色板数据    
	for (int nCounti = 0; nCounti < strInfo.biClrUsed; nCounti++) {
		fwrite(&strPla[nCounti].rgbBlue, 1, sizeof(BYTE), fpw);
		fwrite(&strPla[nCounti].rgbGreen, 1, sizeof(BYTE), fpw);
		fwrite(&strPla[nCounti].rgbRed, 1, sizeof(BYTE), fpw);
	}
	//保存像素数据    
	for (int i = 0; i < strInfo.biWidth; ++i) {
		for (int j = 0; j < strInfo.biHeight; ++j) {
			fwrite(&imagedata[i][j].blue, 1, sizeof(BYTE), fpw);
			fwrite(&imagedata[i][j].green, 1, sizeof(BYTE), fpw);
			fwrite(&imagedata[i][j].red, 1, sizeof(BYTE), fpw);
		}
	}

	fclose(fpw);
}
