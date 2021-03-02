#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#define n 3
#pragma warning(disable : 4996)
double max(double t[n], double b[n])
//函数返回t向量减去b向量后所得到的向量中的一个最大数值，即向量t与b的最大误差 
{
	double max = t[0] - b[0];
	for (int i = 1; i < n; i++)
		if ((t[i] - b[i]) > max) max = t[i] - b[i];
	return max;
}

double* multi_matrix(int a[n][n], double x[n])
//返回矩阵相乘后得到的新矩阵 
{
	double t[n] = { 0 };
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			t[i] += a[i][j] * x[j];
	return t;
}

double W_option(int a[n][n], double b[n], double x[n], double eps)
{
	int i, j, k = 0;
	int min = 100000;   //min为最少迭代次数 
	double m, l;
	double w;
	for (w = 1; w < 2; w = w + 0.05)
	{
		while (max(multi_matrix(a, x), b) > eps)  //计算出A*x所得向量t，再用max函数与向量b相减进行比较 
		{
			for (i = 0; i < n; i++)
			{
				m = 0; l = 0;
				for (j = 0; j < i; j++)
					m += a[i][j] * x[j];
				for (j = i + 1; j < n; j++)
					l += a[i][j] * x[j];
				x[i] = (b[i] - m - l) / a[i][i] * w + x[i] * (1 - w);
			}
			printf("\n");
			k++;
		}
		printf("迭代次数为：%d\n", k);
		if (k < min) min = k;
		else return w;
	}
}

void SOR(int a[n][n], double b[n], double x[n], double eps, double w)
{
	int i, j, k = 0;
	double m, l;
	double t[n] = { 0 };
	while (max(multi_matrix(a, x), b) > eps)  //计算出A*x所得向量t，再用max函数与向量b相减进行比较 
	{
		for (i = 0; i < n; i++)
		{
			m = 0; l = 0;
			for (j = 0; j < i; j++)
				m += a[i][j] * x[j];
			for (j = i + 1; j < n; j++)
				l += a[i][j] * x[j];
			x[i] = (b[i] - m - l) / a[i][i] * w + x[i] * (1 - w);
			printf("%.7lf\t", x[i]);
		}
		printf("\n");
		k++;
	}

	for (i = 0; i < n; i++)
		printf("x%d=%.7lf\n", i + 1, x[i]);

}
/*void main()
{
	int i, j, k;
	double eps = pow(10, -5), w; //w为松弛因子 
	double x[n];
	int a[n][n];
	double b[n];
	printf("输入系数矩阵：\n");
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			scanf("%d", &a[i][j]);
	printf("输入向量b：\n");
	for (i = 0; i < n; i++)
		scanf("%lf", &b[i]);
	for (i = 0; i < n; i++)
		x[i] = 1;
	w = W_option(a, b, x, eps);
	SOR(a, b, x, eps, w);
	system("pause");
}*/
