#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

char* getWord(char* str);
int strLen(const char* str);
int compareStrings(const char* str1, const char* str2);
void uniqueWords(const char* fName1, const char* fName2);
int uniqueWordsInFile(char** arr, const char* filename, int &size);

int main()
{
	char filename1[99] = "tellmewhy1.txt";
	char filename2[99] = "running.txt";
	//int count;

	//char** arr = new char* [9999];
	//uniqueWordsInFile(arr, filename2, count);
	uniqueWords(filename1, filename2);
}

char* getWord(char* str) 
{
	char* word = new char[9999];
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

int strLen(const char* str)
{
	int length = 0;
	for (int i = 0; str[i] != '\0'; i++)
	{
		length++;
	}

	return length;
}

int compareStrings(const char* str1, const char* str2)
{
	int i = 0;
	while (str1[i] != '\0' || str2[i] != '\0')
	{
		if (str1[i] != str2[i])
			return 1;
		if (str1[i] == '\0' && str2[i] != '\0')
			return 1;
		if (str1[i] != '\0' && str2[i] == '\0')
			return 1;
		i++;
	}

	return 0;
}

void uniqueWords(const char* filename1, const char* filename2)
{
	char** firstFileUniqueWords = new char* [999];
	char** secondFileUniqueWords = new char* [999];
	char** temp = new char* [999];
	char** result = new char* [999];
	int size1, size2, tempSize, resultSize, flag;

	uniqueWordsInFile(firstFileUniqueWords, filename1, size1);
	uniqueWordsInFile(secondFileUniqueWords, filename2, size2);

	tempSize = 0;
	resultSize = 0;

	for (int i = 0; i < size1; i++)
	{
		flag = 1;
		for (int j = 0; j < size2; j++)
		{
			if (compareStrings(firstFileUniqueWords[i], secondFileUniqueWords[j]) == 0)
			{
				flag = 0;
				break;
			}
		}
		if (flag)
		{
			result[resultSize] = firstFileUniqueWords[i];
			resultSize++;
		}
	}

	for (int i = 0; i < size2; i++)
	{
		flag = 1;
		for (int j = 0; j < size1; j++)
		{
			if (compareStrings(secondFileUniqueWords[i], firstFileUniqueWords[j]) == 0)
			{
				flag = 0;
				break;
			}
		}
		if (flag)
		{
			result[resultSize] = secondFileUniqueWords[i];
			resultSize++;
		}
	}

	for (int i = 0; i < resultSize; i++)
	{
		printf("%s ", result[i]);
	}
}

int uniqueWordsInFile(char** arr, const char* filename, int &size)
{
	FILE* file;
	char* word;
	char* str = new char[9999];
	int length, i, flag;

	file = fopen(filename, "r");
	if (!file)
	{
		printf("File not open!\n");
		return -1;
	}

	size = 0;

	for (int i = 0; i < 999; i++)
	{
		arr[i] = new char[99]{ " " };
	}

	while (fgets(str, 9999, file) != NULL)
	{
		for (int i = 0; ; i++)
		{
			while (*str == ' ') str++;
			if (*str == '\n' || *str == '\0')
				break;

			word = getWord(str);
			length = strLen(word);
			flag = 1;

			for (int j = 0; j < size; j++)
				if (compareStrings(arr[j], word) == 0)
				{
					flag = 0;
					str = str + length;
					break;
				}

			if (flag)
			{
				arr[size] = word;
				str = str + length;
				size++;
			}
		}
	}

	//for (int j = 0; j < size; j++)
	//{
	//	printf("%s ", arr[j]);
	//}
	fclose(file);

	return 0;
}