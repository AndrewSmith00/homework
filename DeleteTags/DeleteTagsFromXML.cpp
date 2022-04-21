#include <stdio.h>
#pragma warning(disable : 4996) 

void DeleteTags(char* fileName, char* tag);
int len(char* str);
void my_strcat(char* str1, const char* str2);
char* substr(char* str1, char* str2);
char* delSubstr(char* str1, int start, int end);

int main()
{
    char fileName[99];
    char tag[99];

    scanf("%s", fileName);
    scanf("%s", tag);


    DeleteTags(fileName, tag);
}

void DeleteTags(char* fileName, char* tag)
{
    FILE* fPtr;
    char* buffer = new char[999];
    char fullTag[99] = "<";
    char closedTag[99] = "</";
    char* tagPos;
    char* closedTagPos;
    int pos1, pos2;

    fPtr = fopen(fileName, "r");

    if (!fPtr) 
    {
        printf("File can not be opened");
    }
    else
    {
        my_strcat(fullTag, tag);
        my_strcat(fullTag, ">\0");
        printf("%s\n", fullTag);

        my_strcat(closedTag, tag);
        my_strcat(closedTag, ">\0");
        printf("%s\n", closedTag);

        while (fgets(buffer, 99, fPtr) != NULL) {
            tagPos = substr(buffer, fullTag);
            while (tagPos != NULL)
            {
                pos1 = tagPos - buffer;

                closedTagPos = substr(buffer, closedTag);
                if (closedTagPos == NULL)
                {
                    while (fgets(buffer, 99, fPtr) != NULL)
                    {
                        closedTagPos = substr(buffer, closedTag);
                        if(closedTagPos == NULL)
                            continue;
                        else
                        {
                            pos1 = 0;
                            pos2 = closedTagPos - buffer + len(closedTag);
                            buffer = delSubstr(buffer, pos1, pos2);
                            break;
                        }
                    }
                }
                else
                {
                    pos2 = closedTagPos - buffer + len(closedTag);
                    buffer = delSubstr(buffer, pos1, pos2);
                }
                tagPos = substr(buffer, fullTag);
            }

            printf("%s", buffer);
        }
        printf("\n");

        fclose(fPtr);
    }
}

int len(char* str)
{
    int len = 0;
    while (*str != '\0') {
        len++;
        str++;
    }
    return len;
}

void my_strcat(char* str1, const char* str2)
{
    int i = len(str1);
    int j = 0;
    while (str2[j] !='\0')
    {
        str1[i] = str2[j];
        i++; j++;
    }
    str1[i + 1] = '\0';
}

char* substr(char* str1, char* str2)
{
	int n = len(str1), m = len(str2);
	for (int i = 0; i < n - m; i++)
	{
        int j = 0;
        for (; j < m; j++)
            if (str1[i + j] != str2[j]) break;
        if (j == m) return str1 + i;
	}
    return NULL;
}

char* delSubstr(char* str1, int start, int end)
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