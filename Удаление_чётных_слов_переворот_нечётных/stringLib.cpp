#include "stringLib.h"
#include <iostream>

using namespace std;

int my_strlen(char* str1)
{
	int len = 0;
	for (; *str1 != '\0'; str1++)
		len++;
	return len;
}

char* my_strcat(char* str1, char* str2)
{
	if (98 < my_strlen(str1) + my_strlen(str2))
	{
		printf("error");
		return 0;
	}

	char* start = str1;
	for (; *str1 != '\0'; str1++) {};
	for (; *str2 != '\0'; str1++, str2++)
		*str1 = *str2;
	return start;
}

char* my_strcpy(char* str1, char* str2)
{
	char* start = str2;
	for (; *str1 != '\0'; str1++, str2++)
		*str2 = *str1;
	*str2 = '\0';
	return start;
}

int my_strcmp(char* str1, char* str2)
{
	for (; *str1 != '\0', *str2 != '\0'; str1++, str2++)
	{
		if (*str1 != *str2)
			return -1;
		if (*str2 == '\0')
			return 1;
	}
	if (*str2 != '\0')
		return -1;
	return 0;
}

char* my_strchr(char* str1, char smb)
{
	for (; *str1 != '0'; str1++)
	{
		if (*str1 == smb)
			return str1;
	}
	return NULL;
}

char* my_strstr(char* str1, char* str2)
{
	char* start = NULL;

	for (; *str1 != '\0'; str1++)
	{
		if (*str1 == *str2)
		{
			start = str1;
			for (; *str2 != '\0'; str1++, str2++)
			{
				if (*str1 != *str2)
				{
					start = NULL;
					break;
				}
			}
		}
	}

	return start;
}

char* my_strdel(char* str1, int start, int end)
{
	char* str2 = new char[98];
	char* res = str2;
	for (int i = 0; *str1 != '\0'; str1++, i++)
	{
		if (i >= start && i < end)
			continue;
		*str2 = *str1;
		str2++;
	}
	*str2 = '\0';
	return res;
}

char* my_strrev(char* str1)
{
	char* str2 = new char[98];
	char* start = str2;
	int n = 0;
	int len = strlen(str1);
	while(len > 0)
	{
		str2[n] = str1[len - 1];
		len--; n++;
	}
	str2[n] = '\0';
	return start;
}

void my_strdelInPlace(char* str, int k, int m) {
	while (str[k + m - 1] != '\0')
	{
		str[k] = str[k + m];
		k++;
	}
	str[k] = '\0';
}

void my_strrevInPlace(char* str) {
	int n = 0;
	int len = strlen(str);
	int i = 0;
	while (i < len/2 + 1)
	{
		char temp = str[len - 1];
		str[len - 1] = str[n];
		str[n] = temp;
		len--; n++; i++;
	}
}
