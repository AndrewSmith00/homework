#include <iostream>
#include <stdio.h>
#pragma warning(disable : 4996) 

using namespace std;

struct iniqueWords
{
	char word[30];
	int frequency = 1;
};

void createFile(FILE* filePtr, const char* fileName);
void fillFile(FILE* filePtr, const char* context, const char* fileName);
void printFile(char* buffer, int size, FILE* filePtr, const char* fileName);
void setFile(FILE* filePtr, const char* fileName, const char* context, char* buffer, int size);

char* getWord(char* str);
void result(char* buffer, int size, FILE* filePtr, const char* fileName, FILE* secndfilePtr, const char* secndfileName);
char** getArrayOfUniqueWords(char* str, int& count);
void writeAmountOfWords(char* amountOfWords, char* bufferClone, char** arrOfWords, int count);

int main()
{
	//---------------------------------Creating, filling and reading from file---------------------------------
	FILE* origFile = NULL;
	const char origFileName[15] = "text.txt";
	const char context[999] = "Lorem  ipsum\ndolor  sit  amet,  elit.\nEtiam tortor.\nCras  venenatis  lorem.\nProin  pulvinar,\nvehicula    velit.\nSed  eget   massa  ut,\nefficitur  sem.\nInteger  aliquam  diam.\nPellentesque  id  venenatis  augue.\nNunc   molestie.";
	char buffer[999];

	setFile(origFile, origFileName, context, buffer, 999);

	//---------------------------------Amount of words in every string-----------------------------------------

	FILE* resultFile = NULL;
	const char resultFileName[15] = "result.txt";

	createFile(resultFile, resultFileName);

	result(buffer, 999, origFile, origFileName, resultFile, resultFileName);
}

void createFile(FILE* filePtr, const char* fileName) {

	filePtr = fopen(fileName, "w");

	if (filePtr == NULL)
	{
		printf("%s has not been created.\n", fileName);
	}
	else
	{
		printf("%s has been created\n", fileName);
	}

	fclose(filePtr);
}

void fillFile(FILE* filePtr, const char* context, const char* fileName) {
	filePtr = fopen(fileName, "w+");

	int len = strlen(context);

	for (int i = 0; i < len; i++) {
		fputc(context[i], filePtr);
	}
	fputc('\0', filePtr);

	fclose(filePtr);
}

void printFile(char* buffer, int size, FILE* filePtr, const char* fileName) {

	filePtr = fopen(fileName, "r");

	while (fgets(buffer, size, filePtr) != NULL) {
		printf("%s", buffer);
	}
	printf("\n");

	fclose(filePtr);
}

void setFile(FILE* filePtr, const char* fileName, const char* context, char* buffer, int size)
{
	createFile(filePtr, fileName);
	fillFile(filePtr, context, fileName);
	printFile(buffer, size, filePtr, fileName);
}

char* getWord(char* str) {
	char* word = new char[198];
	char* wordStart = word;

	//while (*str == ' ')
		//str++;

	for (; *str != '\n'; str++) {
		for (; *str != ' '; str++, word++) {
			if (*str == '\n') {
				break;
			}
			*word = *str;
		}
		*word = '\0';
		return wordStart;
	}
}

/*
char** countWordsInStr(char* str, int &countUnique) {
	int amountOfWords = 0, len, repeate;
	char* word = new char[198];
	char* startStr = str;
	bool flag;
	char rep[10];

	countUnique = 1;

	for (; *str != '\n'; )
	{
		if (*str == ' ')
			str++;
		else {
			word = getWord(str);
			len = strlen(word);
			amountOfWords++;
			str += len + 1;
		}

	}

	char** arrayOfWords = new char* [amountOfWords];
	str = startStr;

	for (int i = 0; i < amountOfWords; i++)
	{
		arrayOfWords[i] = new char[99];
	}

	for (int i = 0; *str != '\n'; )
	{
		if (*str == ' ')
			str++;
		else
		{
			word = getWord(str);
			len = strlen(word);
			arrayOfWords[i] = word;
			i++;
			str += len + 1;
		}

	}

	for (int i = 0; i < amountOfWords - 1; i++)
	{
		flag = true;
		for (int j = i + 1; j < amountOfWords; j++)
			if (strcmp(arrayOfWords[i], arrayOfWords[j]) == 0)
				flag = false;
		if (flag)
			countUnique++;
	}

	char** uniqueWords = new char* [countUnique];

	for (int i = 0; i < amountOfWords; i++)
	{
		uniqueWords[i] = new char[99];
	}

	for (int i = 0, k = 0; i < amountOfWords; i++)
	{
		flag = true;
		for (int j = 0; j < i; j++)
			if (strcmp(arrayOfWords[i], uniqueWords[j]) == 0)
				flag = false;

		if (flag)
		{
			uniqueWords[k] = arrayOfWords[i];
			k++;
		}
	}

	for (int i = 0; i < countUnique; i++)
	{
		repeate = 0;
		for (int j = 0; j < amountOfWords; j++)
		{
			if (strcmp(uniqueWords[i], arrayOfWords[j]) == 0)
				repeate++;
		}

		sprintf(rep, "%d", repeate);
		strcat(uniqueWords[i], " ");
		strcat(uniqueWords[i], rep);
		strcat(uniqueWords[i], " ");
		//printf("%s\n", uniqueWords[i]);
	}

	str = startStr;

	return uniqueWords;
}
*/


void result(char* buffer, int size, FILE* filePtr, const char* fileName, FILE* secndfilePtr, const char* secndfileName) {
	filePtr = fopen(fileName, "r");
	secndfilePtr = fopen(secndfileName, "w+");
	int countUnique = 0, bufferLen, repeate = 0, count;
	char* bufferStart;
	char** arrOfUniqueWords;
	char* bufferClone = new char[999];
	char* amountOfWords = new char[999]{ "" };


	while (fgets(buffer, size, filePtr) != NULL) {
		bufferStart = buffer;
		strcpy(bufferClone, buffer);

		arrOfUniqueWords = getArrayOfUniqueWords(bufferClone, count);

		writeAmountOfWords(amountOfWords, bufferClone, arrOfUniqueWords, count);

		fputs(amountOfWords, secndfilePtr);
		amountOfWords[0] = '\0';

		/*
		for (int i = 0; i < count; i++)
		{
			arrOfUniqueWords[i][0] = ' ';
		}
		*/
	}
	printf("\n");

	fclose(filePtr);
	fclose(secndfilePtr);
}

char** getArrayOfUniqueWords(char* str, int &count) {
	char** arrOfUniqueWords = new char* [30];
	char* word = new char[99];
	bool flag;
	int len;

	count = 0;

	for (int i = 0; i < 10; i++)
	{
		arrOfUniqueWords[i] = new char[50]{ " " };
	}

	for (int i = 0; ; i++)
	{
		while (*str == ' ') str++;
		if (*str == '\n' || *str =='\0')
			break;

		word = getWord(str);
		flag = true;
		for (int j = 0; j < i; j++)
			if (strcmp(arrOfUniqueWords[j], word) == 0)
			{
				flag = false;
				break;
			}

		if (flag)
		{
			arrOfUniqueWords[i] = word;
			len = strlen(word);
			str = str + len;
			count++;
		}
	}
	return arrOfUniqueWords;
}

void writeAmountOfWords(char* amountOfWords, char* bufferClone, char** arrOfWords, int count) {
	int repeate;
	char* word = new char[99];
	char* rep = new char[5];
	
	for (int i = 0; i < count; i++)
	{
		repeate = 0;

		while (*bufferClone == ' ') bufferClone++;
		if (*bufferClone == '\n' || *bufferClone == '\0')
			break;

		word = getWord(bufferClone);

		for (int j = 0; j < count; j++)
		{
			if (strcmp(word, arrOfWords[j]) == 0)
				repeate++;
		}

		sprintf(rep, "%d", repeate);
		strcat(amountOfWords, arrOfWords[i]);
		strcat(amountOfWords, "-");
		strcat(amountOfWords, rep);
		strcat(amountOfWords, " ");
	}
	strcat(amountOfWords, "\n");
}