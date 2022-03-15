#include <iostream>
#include <stdio.h>
#include "stringLib.cpp"

using namespace std;

int* getFrequanceOfLetters(char* str);
int getMaxFrecuence(char* str);
char getMaxFrecuenteLetter(char* str);

int main()
{
	char str[999] = "zzzzzzaaaaabbbbbab...";
	
	int* letters = getFrequanceOfLetters(str);
	int maxFrequence = getMaxFrecuence(str);
	char maxFrequentLetter = getMaxFrecuenteLetter(str);

	printf("%c %d", maxFrequentLetter, maxFrequence);
}

int* getFrequanceOfLetters(char* str) {

	int* letters = new int[127];
	int letterNumber = 0;

	for (int i = 65; i < 127; i++)
		letters[i] = 0;
		

	for (; *str != '\0' ; str++)
	{
		letterNumber = *str;

		if ((*str > 64 && *str < 91) || (*str > 96 && *str < 123))
		{
			if (*str > 96)
				letterNumber -= 32;

			letters[letterNumber]++;
		}
	}

	return letters;
}

int getMaxFrecuence(char* str) {

	int* letters = getFrequanceOfLetters(str);

	int maxNumber = 0;

	for (int i = 65; i < 127; i++)
		if (letters[i] > maxNumber)
			maxNumber = letters[i];

	return maxNumber;
}

char getMaxFrecuenteLetter(char* str) {

	int* letters = getFrequanceOfLetters(str);
	int maxNumber = 0;
	char maxFrecuentLetter;

	for (int i = 65; i < 127; i++)
		if (letters[i] > maxNumber)
		{
			maxFrecuentLetter = i;
			maxNumber = letters[i];
		}

	return maxFrecuentLetter;
}