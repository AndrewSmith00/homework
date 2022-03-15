#include <iostream>
#include <stdio.h>


using namespace std;

int* getDigits(char* str);
void createNumber(char* str);

int main()
{
    char str[999] = "zzzzzzaa...";

	createNumber(str);
}

int* getDigits(char* str) {
    int* digits = new int[59];
	int digitNumber = 0;

	for (int i = 48; i < 58; i++)
		digits[i] = 0;

	for (; *str != '\0'; str++)
	{
		digitNumber = *str;

		if (*str > 47 && *str < 58)
			digits[digitNumber]++;
	}

	return digits;
}

void createNumber(char* str) {

	int* digits = getDigits(str);
	int maxNumber = 0;
	int digit = 0;
	bool isEmpty = true;

	for (int i = 57; i >= 48; i--)
	{
		digit = i - 48;
		if (digits[i] != 0)
		{
			isEmpty = false;

			for (int j = 0; j < digits[i]; j++)
			{
				maxNumber = maxNumber * 10 + digit;
			}
		}
	}
		
	if (!isEmpty)
		printf("Yes: %d", maxNumber);
	else
	{
		printf("No");
	}
}