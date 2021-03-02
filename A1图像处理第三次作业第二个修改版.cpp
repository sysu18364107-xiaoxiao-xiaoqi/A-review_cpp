#include<iomanip>
#include <iostream>
#include <cstring>
#include <string>
#include <cstringt.h>
#include<vector>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
using namespace std;
#define MAX 100
/*
实现思路：
1:首先输入预想要进行求逆的矩阵
2:求行列式，判断矩阵能否求逆
3:判断是否需要进一步求余子式
4:求出矩阵的余子式，对余子式进行转置，并且除以行列式得到
*/

//----------------------------------------------------------solved
//read matrix : cin>> in c++ , scanf() in c
int scanf(float a[MAX][MAX]) {
	int i, j, n;
	cout << "\n Enter Length Of Matrix N*N : ";
	cin >> n;
	cout << "\n--------------------------\n";
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++) {
			cout <<setw(8) << " Matrix[" << i + 1 << "][" << j + 1 << "] : ";
			cin >> a[i][j];
		}
	cout << "\n----------------------------------------------------\n";
	return n;
}

//-----------------------------------------------------solved
// show matrix : cout<< in c++ , printf() in c
void printf(float a[MAX][MAX], int n, int show) {
	int i, j;
	if (show == 1)
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++)
				cout << " " << setw(8) << a[i][j] << " \t";
			cout << "\n";
		}
	else if (show == 2) {
		cout << "\n\n The Inverse Of Matrix Is : \n\n";
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++)
				cout << " " << setw(8) << a[i][j] << " \t";
			cout << "\n";
		}
	}
}

//---------------------------------------------------solved
//	calculate minor of matrix OR build new matrix : k-had = minor//计算矩阵的余子式或建立新矩阵:k-had =余子式
void minor(float b[MAX][MAX], float a[MAX][MAX], int i, int n) {//0<=i<n
	int j, l, h = 0, k = 0;
	for (l = 1; l < n; l++)
		for (j = 0; j < n; j++) {//此处不用考虑会不会取到第i行，因为l=i+1，自然地避开了取第i行的风险
			if (j == i)//假设进行到第i列
				continue;//不加入余子式中
			b[h][k] = a[l][j];//如果不是第i列，余子式先从第一行开始填满
			k++;			  //如在求a[0][0]的余子式，则不考虑第0列的
			if (k == (n - 1)) {//当第一列填满时，h++，进行下一行的填充
				h++;
				k = 0;//k回到第一列，准备继续向后填充
			}
		}
}// end function

//---------------------------------------------------solved
//	calculate determinte of matrix//先计算行列式，判断矩阵能否求逆矩阵
float det(float a[MAX][MAX], int n) {
	int i;
	float b[MAX][MAX], sum = 0;
	if (n == 1)//如果行列式为一阶行列式
		return a[0][0];
	else if (n == 2)//如果为二阶行列式
		return (a[0][0] * a[1][1] - a[0][1] * a[1][0]);
	else
		for (i = 0; i < n; i++) {
			minor(b, a, i, n);	// read function//这样可以求得行列式的余子式
			sum = (float)(sum + a[0][i] * pow(-1, i)*det(b, (n - 1)));	// read function	// sum = determinte matrix
			//在后面出现递归，依次降维矩阵的维数，让矩阵满足n==2的条件即可计算出矩阵的行列式
		}
	return sum;
}// end function

//---------------------------------------------------
//	calculate transpose of matrix//计算矩阵的转置
void transpose(float c[MAX][MAX], float d[MAX][MAX], int n, float det) {
	//通过对余子式求转置除行列式得到矩阵的逆
	//task4:求出矩阵的余子式，对余子式进行转置，并且除以行列式得到
	int i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			d[i][j] = c[j][i] / det;//先将刚刚求得的余子式进行转置,因为这里对每一行都求了余子式
									// array d[][] = inverse matrix
}// end function

//---------------------------------------------------
//	calculate cofactor of matrix//计算矩阵的余子式
void cofactor(float a[MAX][MAX], float d[MAX][MAX], int n, float determinte) {
	float b[MAX][MAX], c[MAX][MAX];
	int l, h, m, k, i, j;
	for (h = 0; h < n; h++)
		for (l = 0; l < n; l++) {
			m = 0;
			k = 0;
			for (i = 0; i < n; i++)
				for (j = 0; j < n; j++)
					if (i != h && j != l) {//求余子式的时候跳过本行
						b[m][k] = a[i][j];//b是建立的余子式
						if (k < (n - 2))//基本实现思路和求行列式的思路是差不多的
							k++;
						else {
							k = 0;
							m++;
						}
					}
			c[h][l] = (float)pow(-1, (h + l))*det(b, (n - 1));	// c = cofactor Matrix
		}
	transpose(c, d, n, determinte);	// read function
}// end function

//---------------------------------------------------solved
//	calculate inverse of matrix//计算矩阵的逆
void inverse(float a[MAX][MAX], float d[MAX][MAX], int n, float det) {
	if (det == 0)
		cout << "\nInverse of Entered Matrix is not possible\n";
	else if (n == 1)
		d[0][0] = 1;
	else
		cofactor(a, d, n, det);	// 计算矩阵的余子式
}// end function

//---------------------------------------------------
//main fuction exe
int main(void) {
	int n;
	float a[MAX][MAX], d[MAX][MAX], deter;
	cout << "\n C++ Program To Find Inverse Of Matrix\n\n";
	n = scanf(a);	//task1:首先输入预想要进行求逆的矩阵
	int print_matrix = 1;
	printf(a, n, print_matrix);	//将输入的代码打印出来
	deter = (float)det(a, n);	//task2:求行列式，判断矩阵能否求逆
	cout << "----------------------------------------------------\n";
	cout << "\n\n Determinant of the Matrix : " << deter;//打印行列式的值
	cout << "\n\n-----------------------\n";
	inverse(a, d, n, deter);	//task3:判断是否需要进一步求余子式
	int print_inverse = 2;
	printf(d, n, print_inverse);	// 展示逆矩阵
	cout << "\n\n==============================* THE END *==============================\n";
	cout << "\n		**** Thanks For Using The Program!!! ****\n";
	_getch();
	return 0;
}// end main
