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


	char* start = str1;
	for (; *str1 != '\0'; str1++) {};
	for (; *str2 != '\0'; str1++, str2++)
		*str1 = *str2;
	*str1 = '\0';
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
	for (; *str1 != '\0'; str1++, str2++)
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