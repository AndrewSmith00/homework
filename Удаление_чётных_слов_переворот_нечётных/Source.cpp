#include <stdio.h>
#include <iostream>
#include "stringLib.cpp"

using namespace std;

char* getWord(char* str);
char* getNewString(char* str);

int main()
{
	char str[999] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras elit ex, posuere et diam id, imperdiet dictum nulla. Donec enim libero, ullamcorper sed justo ut, lacinia pharetra purus. Aliquam et massa commodo, mollis urna vitae, varius quam. Vivamus vel lobortis ex, id pharetra est.";
	char* word = getWord(str);
	char* newString = getNewString(str);

	printf("%s", newString);
}

char* getWord(char* str) {
	char *word = new char[98];
	char* wordStart = word;
	for (; *str != '\0'; str++) {
			for (; *str != ' '; str++, word++) {
				if (*str == '\0') {
					break;
				}
				*word = *str;
			}
			*word = '\0';
			return wordStart;
	}
}


char* getNewString(char* str) {
	char* newString = new char[98];
	char* newStringStart = newString;
	char* word = new char[98];
	char* newWord = new char[97];
	char* newWordStart = newWord;
	int len = 0;
	for (; *str != '\0'; str++) {
		if (*str == ' ') {
			*newString = *str;
			newString++;
			str++;
		}

		word = getWord(str);
		int len = my_strlen(word);
		if (len % 2 != 0) {
			newWord = my_strrev(word);
			for (; *newWord != '\0'; newWord++, newString++)
				*newString = *newWord;
		}
		str += len - 1;
	}
	*newString = '\0';
	return newStringStart;
}

