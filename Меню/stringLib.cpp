#include "stringLib.h"
#include <iostream>

using namespace std;

int const strSize = 99;

int my_strlen(char* str)
{
	int len = 0;
	while (*str++) {
		len++;
	}
	return len;
}

bool my_strcat(char* str1, char* str2)
{
	if (my_strlen(str1) + my_strlen(str2) > strSize) {
		printf("Error: string lengths exceed the allowed value");
		return false;
	}

	str1 += my_strlen(str1);
	while (*str2++)
	{
		*str1 = *str2;
		str2++;
	}
	return true;
}

bool my_strcpy(char* str1, char* str2)
{
	if (my_strlen(str2) > strSize)
	{
		printf("Error: string length exceed the allowed value");
		return false;
	}

	while (*str1++) {
		*str2 = *str1;
		str2++;
	}
	*str2 = '\0';
	return true;
}

int my_strcmp(char* str1, char* str2)
{
	int diff = 0;
	while (*str1 || *str2)
	{
		if (*str1 != *str2)
			diff += *str1 - *str2;
		if (*str2 == '\0')
			diff += *str1;
		if (*str1 == '\0')
			diff -= *str2;
		str1++; str2++;
	}
	return diff;
}

char* my_strchr(char* str1, char smb)
{
	while (*str1++)
	{
		if (*str1 == smb)
			return str1;
	}
	return NULL;
}

char* my_strstr(char* str1, char* str2)
{
	char* start = NULL;

	while (*str1++)
	{
		if (*str1 == *str2)
		{
			start = str1;
			while (*str2++)
			{
				if (*str1 != *str2)
				{
					start = NULL;
					break;
				}
				str1++;
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
	while (len > 0)
	{
		str2[n] = str1[len - 1];
		len--; n++;
	}
	str2[n] = '\0';
	return start;
}

bool my_strdelInPlace(char* str, int k, int m) {
	
	if ((k + m) > my_strlen(str))
	{
		printf("Error: deletion could not complete successfully");
		return false;
	}

	while (str[k + m - 1] != '\0')
	{
		str[k] = str[k + m];
		k++;
	}
	str[k] = '\0';
	return true;
}

void my_strrevInPlace(char* str) {
	int n = 0;
	int len = strlen(str);
	int i = 0;
	while (i < len / 2)
	{
		char temp = str[len - 1];
		str[len - 1] = str[n];
		str[n] = temp;
		len--; n++; i++;
	}
}
