#include "stringLib.h"
#include <iostream>

using namespace std;

int my_strlen(char* str1)
{
	int len = 0;
	int len = 0;
	while (str1++) len++;
	return len;
}

char* my_strcat(char* str1, char* str2)
{
	int len1 = my_strlen(str1);

	char* start = str1;
	str1 += len1;
	while (*str2 != '\0')
	{
		*str1 = *str2;
		str1++; str2++;
	}
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
	int diff = 0;
	while (*str1 !='\0' || *str2 != '\0')
	{
		if (*str1 != *str2)
			diff += *str1 - *str2;
		if (*str2 == '\0')
			diff += *str1;
		if (*str1 == '\0')
			diff -= *str2;
	}
	return diff;
}

char* my_strchr(char* str1, char smb)
{
	while(*str1 != '0') 
	{
		if (*str1 == smb)
			return str1;
		str1++;
	}
	return NULL;
}

char* my_strstr(char* str1, char* str2)
{
	char* start = NULL;

	while (*str1 != '0')
	{
		if (*str1 == *str2)
		{
			start = str1;
			while (*str2 != '0')
			{
				if (*str1 != *str2)
				{
					start = NULL;
					break;
				}
				str1++; str2++;
			}
		}
		str1++;
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
	int len = strlen(str1);
	for (; *str1 != '\0'; str1++) {}
	str1--;
	for (int i = 0; i < len; i++)
	{
		*str2 = *str1;
		str1--;
		str2++;
	}
	*str2 = '\0';
	return start;
}
