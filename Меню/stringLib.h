#pragma once


int my_strlen(char* str1);
bool my_strcat(char* str1, char* str2);
bool my_strcpy(char* str1, char* str2);
int my_strcmp(char* str1, char* str2);
char* my_strchr(char* str1, char smb);
char* my_strstr(char* str1, char* str2);
char* my_strdel(char* str1, int start, int end);
bool my_strdelInPlace(char* str, int k, int m);
char* my_strrev(char* str1);
void my_strrevInPlace(char* str);
