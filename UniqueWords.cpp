#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

void uniqueWordsInFile(char* filename);
char* getWord(char* str);
int strLen(const char* str);
int compareStrings(const char* str1, const char* str2);

int main()
{
    char filename[99] = "tellmewhy1.txt";
    uniqueWordsInFile(filename);
    return 0;
}

/*
char* getWord(char* str)
{
    char* word = (char*) malloc (99 * sizeof(char));
    int i;
    i = 0;
    while(str[i] != ' ' || str[i] != '\n')
    {
        word[i] = str[i];
        i++;
    }
    word[i] = '\0';
    return word;
}
*/

char* getWord(char* str)
{
    char* word = (char*) malloc(99 * sizeof(char));
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

void uniqueWordsInFile(char* filename)
{
    char** arr;
    FILE* file;
    char* word;
    char* str;
    int len, flag, size;

    file = fopen(filename, "r");

    if (!file)
    {
        printf("File not opened!\n");
    }
    else
    {
        arr = (char**)malloc(99 * sizeof(char*));
        for (int i = 0; i < 99; i++)
        {
            arr[i] = (char*)malloc(99 * sizeof(char));
            
        }

        word = (char*)malloc(99 * sizeof(char));

        str = (char*)malloc(999 * sizeof(char));
        size = 0;
        /*
        while(fgets(str, 999, file) != NULL)
        {
            for(int i = 0; str[i] != '\n'; i++)
            {
                while (str[i] == ' ') i++;
                if (str[i] == '\n') break;
                word = getWord(str);
                len = strLen(word);
                flag = 1;
                for(int j = 0; j < size; j++)
                    if (compareStrings(arr[j], word) == 0)
                    {
                        flag =  0;
                        i = i + len;
                        break;
                    }

                if (flag)
                {
                    arr[size] = word;
                    i = i + len;
                    size++;
                }
            }
        }
        */
        while (fgets(str, 999, file) != NULL)
        {
            for (int i = 0; str[i] != '\0'; i++)
            {
                while (*str == ' ') str++;
                if (*str == '\n' || *str == '\0')
                    break;

                word = getWord(str);
                len = strLen(word);
                flag = 1;

                for (int j = 0; j < size; j++)
                    if (compareStrings(arr[j], word) == 0)
                    {
                        flag = 0;
                        str = str + len;
                        break;
                    }

                if (flag)
                {
                    arr[size] = word;
                    str = str + len;
                    size++;
                }
            }
        }
        for (int i = 0; i < size; i++)
            printf("%s ", arr[i]);

        for (int i = 0; i < 99; i++)
            free(arr[i]);
        free(arr);
        //free(word);
        //free(str);
        fclose(file);
    }
}
