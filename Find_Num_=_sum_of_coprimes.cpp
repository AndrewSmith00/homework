#include <iostream>
#include <stdio.h>

using namespace std;

int NOD(int x, int y);
void getArrOfCoprimes(int num, int** arrOfCoprimes, int& size);
int** createMatrix(int n, int m);
void printArrOfCoprimes(int num);
void deleteMatrix(int** matr, int n);

int main()
{
	printArrOfCoprimes(15);
}

int NOD(int x, int y) {
	while (x > 0 and y > 0)
		if (x > y)
			x %= y;
		else
			y %= x;
	return x + y;
}

void getArrOfCoprimes(int num, int** arrOfCoprimes, int &size) {

	for (int i = 0; i <= num / 2 ; i++)
		for (int j = 0; j < num; j++)
			if (i + j == num)
				if (NOD(i, j) == 1)
				{
					arrOfCoprimes[size][0] = i;
					arrOfCoprimes[size][1] = j;
					size++;
				}
}

int** createMatrix(int n, int m) {

	int** matr = new int* [n];

	for (int i = 0; i < n; i++)
		matr[i] = new int[m];

	return matr;
}

void printArrOfCoprimes(int num) {
	int size = 0;

	int** arrOfCoprimes = createMatrix(1000, 2);

	getArrOfCoprimes(num, arrOfCoprimes, size);

	for (int i = 0; i < size; i++)
		printf("%d %d\n", arrOfCoprimes[i][0], arrOfCoprimes[i][1]);

	deleteMatrix(arrOfCoprimes, num);
}

void deleteMatrix(int** matr, int n) {
	for (int i = 0; i < n; i++)
		delete[] matr[i];

	delete[] matr;
}