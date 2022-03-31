#include <stdio.h>
#include <iostream>
#include "stringLib.cpp"

using namespace std;

char* getWord(char* str);
void getNewString(char* str);
int findPos(char* str, char* source);
//char* getNewString(char* str);

int main()
{
	char str[999] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Cras tincidunt sagittis lorem. Duis nec dolor luctus, fringilla turpis in, dapibus leo.";
 	getNewString(str);
	char str1[99] = "strstr";
	//printf("%d", sizeof(str1));
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
	char* word = new char[98];
	char* temp = str;
	int len = 0;
	while(*temp != '\0') {
		while (*temp == ' ')
			temp++;

		word = getWord(temp);
		int len = my_strlen(word);
		if (len % 2 != 0) {
			my_strrevInPlace(word);
			while (*word != '\0')
			{
				*temp = *word;
				temp++; word++;
			}
		}
		else {
			char* wordPos = my_strstr(str, word);
			int pos = (wordPos - str);
			my_strdelInPlace(str, pos, pos + len - 1);
			//if (*temp == '\0') break;
		}
	}
}

/*
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
*/
