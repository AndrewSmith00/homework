#include <iostream>
#include <stdio.h>
#pragma warning(disable : 4996) 

using namespace std;

void createFile(char* fileName);
char* getWord(char* str);
void result(char* sourceName, char* resultName);
char** getArrayOfUniqueWords(char* str, int& count);
void writeAmountOfWords(char* amountOfWords, char* str);

int main()
{
	setlocale(LC_ALL, "Rus");

	//---------------------------------Creating, filling and reading from file---------------------------------
	char fileName[15];

	printf("Введите название файла:\n");
	scanf_s("%s", fileName, sizeof(fileName));

	createFile(fileName);

	//---------------------------------Amount of words in every string-----------------------------------------

	char resultName[15] = "result.txt";

	printf("Введите название файла для хранения результата:\n");
	scanf_s("%s", resultName, sizeof(resultName));

	result(fileName, resultName);
}

void createFile(char* fileName)
{
	//--------------------------------Открытие файла---------------------------------
	FILE* fPtr;
	char buffer[499];

	fPtr = fopen(fileName, "w");

	//--------------------------------Ввод содержимого-------------------------------

	if (fPtr == NULL) 
	{
		printf("Файл <<%s>> не был создан\n\n", fileName);
	}
	else
	{
		printf("Вводите содержимое файла. Для завершения введите exit\n");

		while (true) {
			gets_s(buffer);

			if (strcmp(buffer, "exit") == 0) {
				fputs("\0", fPtr);
				break;
			}

			//buffer[strlen(buffer) + 1] = '\n';
			fputs(buffer, fPtr);
			fputs("\n", fPtr);

			buffer[0] = '\0';
		}

		fputs("\0", fPtr);

		fclose(fPtr);

		//-------------------------------Вывод на консоль---------------------------

		fPtr = fopen(fileName, "r");

		system("cls");
		printf("Содержимое файла:\n");

		while (fgets(buffer, 99, fPtr) != NULL) {
			printf("%s", buffer);
		}
		printf("\n");

		fclose(fPtr);
	}
}

char* getWord(char* str) {
	char* word = new char[198];
	char* wordStart = word;

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

void result(char* sourceName, char* resultName)
{
	FILE* source = fopen(sourceName, "r");
	FILE* result = fopen(resultName, "w");
	char buffer[99];
	char* amountOfWords = new char[999]{ "" };
	int count;

	while (fgets(buffer, 99, source) != NULL) {

	writeAmountOfWords(amountOfWords, buffer);

	fputs(amountOfWords, result);
	amountOfWords[0] = '\0';
	}
	printf("\n");

	fclose(source);
	fclose(result);
}

char** getArrayOfUniqueWords(char* str, int& count) {
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
		if (*str == '\n' || *str == '\0')
			break;

		word = getWord(str);
		flag = true;
		for (int j = 0; j < i; j++)
			if (strcmp(arrOfUniqueWords[j], word) == 0)
			{
				flag = false;
				str = str + len;
				break;
			}

		if (flag)
		{
			arrOfUniqueWords[count] = word;
			len = strlen(word);
			str = str + len;
			count++;
		}
	}
	return arrOfUniqueWords;
}

void writeAmountOfWords(char* amountOfWords, char* str) {
	int repeate, count;
	char** arrOfWords;
	char* word = new char[99];
	char* rep = new char[5];
	char* strStart = str;

	arrOfWords = getArrayOfUniqueWords(str, count);

	for (int j = 0; j < count; j++)
	{
		repeate = 0;
		while (*str != '\n')
		{
			while (*str == ' ') str++;
			if (*str == '\n' || *str == '\0')
				break;

			word = getWord(str);
			str += strlen(word);

			if (strcmp(word, arrOfWords[j]) == 0)
				repeate++;
		}

		sprintf(rep, "%d", repeate);
		strcat(amountOfWords, arrOfWords[j]);
		strcat(amountOfWords, "-");
		strcat(amountOfWords, rep);
		strcat(amountOfWords, " ");

		str = strStart;
	}
	strcat(amountOfWords, "\n");
}
