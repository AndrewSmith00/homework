#include <stdio.h>
#include <stdlib.h>

int len(const char *str)
{
    int i = 0;
    for(; str[i] != '\0'; i++) {}
    return i; 
}

char* getWord(char* str) {
	char* word = (char*) malloc(100 * sizeof(char));
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
    return wordStart;
}
/*
int isSameLen(char* str) 
{
    char* temp = (char*) malloc(100 * sizeof(char));
    int length;

    temp = getWord(str);
    length = len(temp);

    for (int i = 0; str[i] != '\0'; i++)
	{
		while (*str == ' ') str++;
		if (*str == '\n' || *str == '\0') break;

        temp = getWord(str);
        if (len(temp) != length) 
        {
            free(temp);
            return 0;
        }
    }
    
    free(temp);
    return 1;
}
*/
int stringsWithSameLenWords(const char *fName)
{
    FILE* fp = NULL;
    char* buff = (char*) malloc(2048 * sizeof(char));
    char* temp = (char*) malloc(100 * sizeof(char));
    int length, flag;

    fp = fopen(fName, "r");

    if (fp == NULL)
    {
        printf("File has not been opened");
        return 1;
    } 
    else
    {
        while(fgets(buff, 2048, fp) != NULL)
        {
            /*if(isSameLen(buff)) 
                printf("%s", buff);
            else
                continue;
            */

            temp = getWord(buff);
            length = len(temp);
            flag = 1;

            for (int i = 0; buff[i] != '\n'; i++)
            {
                while (*buff == ' ') buff++;
                if (*buff == '\n' || *buff == '\0') break;

                temp = getWord(buff);
                if (len(temp) != length) 
                {
                    flag = 0;
                    break;
                }
            }

            if (flag)
                printf("%s", buff);
        }

        free(buff);
        free(temp);
        return 0;
    }
}

int main()
{
    char fName[50] = "text.txt";

    stringsWithSameLenWords(fName);
}