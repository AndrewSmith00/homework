#include <iostream>
#include <stdio.h>
using namespace std;

float** CreateMatrix(int n, int m);
float** FillMatrix(int n, int m);
void PrintMatrix(float** arr, int n, int m);
float** MultOfMatrix(float** matr1, float** matr2, int row1, int col1, int row2, int col2);
float GetMatrixTrace(float** matr, int row, int col);
float* GetVector(float** matr, int row, int col, int m);

int main()
{
	for (int x = 1; x <= 50; x++)
		for (int y = 0; y < 50; y++)
			printf("%d %d | %d\n", x, y, sumOfSquares(x, y));
	
}



float** CreateMatrix(int n, int m)
{
	float** arr = new float* [n];

	for (int i = 0; i < n; i++)
	{
		arr[i] = new float[m];
	}

	return arr;
}

float** FillMatrix(int n, int m)
{
	float** arr = CreateMatrix(n, m);

	printf("Enter elements of matrix\n");
	for (int i = 0; i < n; i++)
	{
		printf("%d string:\n", i + 1);
		for (int j = 0; j < m; j++)
			scanf_s("%f", &arr[i][j]);
	}
	return arr;
	printf("\n\n");
}

void PrintMatrix(float** arr, int n, int m)
{
	printf("Matrix is:\n");
	for (int i = 0; i < n; i++)
	{
		printf("\n");
		for (int j = 0; j < m; j++)
			printf("%.1f\t", arr[i][j]);
		printf("\n");
	}
	printf("\n\n");
}

float** MultOfMatrix(float** matr1, float** matr2, int row1, int col1, int row2, int col2)
{
	if (col1 != row2)
	{
		printf("Multiplication is impossible");
		return 0;
	}

	float** product = new float* [row1];

	for (int i = 0; i < row1; i++)
	{
		product[i] = new float[col2];
		for (int j = 0; j < col2; j++)
		{
			product[i][j] = 0;
			for (int k = 0; k < col1; k++)
				product[i][j] += matr1[i][k] * matr2[k][j];
		}
	}

	return product;
}

float GetMatrixTrace(float** matr, int row, int col)
{
	if (col != row)
	{
		printf("Trace can not be found");
		return 0;
	}
	else
	{
		float trace = 0;

		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				if (i == j)
					trace = trace + matr[i][j];

		return trace;
	}
}

float* GetVector(float** matr, int row, int col, int m)
{
	if (col != row)
	{
		printf("Trace can not be found");
		return 0;
	}
	else
	{
		float* b = new float[m];

		float** tempMatr = matr;

		for (int i = 0; i < m; i++)
		{
			PrintMatrix(tempMatr, row, col);

			b[i] = GetMatrixTrace(tempMatr, col, row);


			tempMatr = MultOfMatrix(tempMatr, matr, row, col, row, col);
		}

		return b;
	}
}