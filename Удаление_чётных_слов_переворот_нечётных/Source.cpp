#include <stdio.h>
#include <iostream>
#include "stringLib.cpp"

using namespace std;

char* getWord(char* str);
void getNewString(char* str);

int main()
{
	char str[999] = "Lorem    ipsum dolor sit amet, consectetur adipiscing elit. Cras elit ex, posuere et diam id, imperdiet dictum nulla. Donec enim libero, ullamcorper sed justo ut, lacinia pharetra purus. Aliquam et massa commodo, mollis urna vitae, varius quam. Vivamus vel lobortis ex, id pharetra est.";
	getNewString(str);
	printf("%s", str);
}

char* getWord(char* str) {
	char* word = new char[98];
	char* wordStart = word;
	while (*str != ' ') {
		if (*str == '\0') {
			break;
		}
		*word = *str;
		str++; word++;
	}
	*word = '\0';
	return wordStart;
}


void getNewString(char* str) {
	char* newString = new char[98];
	char* newStringStart = newString;
	char* word = new char[98];
	char* newWord = new char[97];
	char* newWordStart = newWord;
	int len = 0;
	for (int i = 0; str[i]; i++) {
		if (str[i] == ' ')
			continue;

		word = getWord(str + i);
		int len = my_strlen(word);
		int n = 0;
		if (len % 2 != 0) {
			my_strrevInPlace(word);
			while (n < len)
			{
				str[i] = word[n];
				i++; n++;
			}
		}
		else {
			my_strdelInPlace(str, i, i + len - 1);
		}
	}
}
