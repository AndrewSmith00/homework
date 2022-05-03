#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable : 4996)

int strLength(const char* str)
{
    int len = 0;
    for (int i = 0; str[i] != '\0'; i++) len++;
    return len;
}

void strCopy(char* str1, char* str2)
{
    int i, len;

    len = strLength(str2);
    for (i = 0; i < len; i++)
    {
        str1[i] = str2[i];
    }
    str1[i] = '\0';
}

int strcompare(const char* str1, const char* str2)
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

char* findSubstr(char* str, const char* substr)
{
    int n, m, j;
    n = strLength(str);
    m = strLength(substr);

    for (int i = 0; i < n; i++)
    {
        j = 0;
        for (; j < m; j++)
        {
            if (str[i] != substr[j]) break;
            i++;
        }
        if (j == m)
            return (str + i - j);
    }
    return NULL;
}

void mergeINIfiles(const char* firstFileName, const char* scndFileName)
{
    FILE* fPointer1 = NULL;
    FILE* fPointer2 = NULL;
    char* str; //* sectionName;
    char** checkedSectionNames;
    int k, sectionEnd, isChecked;

    fPointer1 = fopen(firstFileName, "r");
    //fPointer2 = fopen(scndFileName, "r");
    str = (char*)malloc(99 * sizeof(char));
    checkedSectionNames = (char**)malloc(99 * sizeof(char*));
    k = 0;


    for (int i = 0; i < 99; i++)
        checkedSectionNames[i] = (char*)malloc(99 * sizeof(char));

    while (fgets(str, 99, fPointer1) != NULL)
    {
        printf("%s", str);
        if (findSubstr(str, "[") != NULL && findSubstr(str, "]") != NULL)
        {
            sectionEnd = 0;

            strCopy(checkedSectionNames[k], str);

            fPointer2 = fopen(scndFileName, "r");

            while (fgets(str, 99, fPointer2) != NULL && sectionEnd == 0)
            {
                if (findSubstr(str, checkedSectionNames[k]) == NULL)
                {
                    continue;
                }
                else
                {
                    while (fgets(str, 99, fPointer2) != NULL)
                    {
                        if (findSubstr(str, "[") != NULL && findSubstr(str, "]") != NULL)
                        {
                            sectionEnd = 1;
                            break;
                        }
                        printf("%s", str);
                    }
                }
            }

            k++;

            fclose(fPointer2);
        }
    }

    fPointer2 = fopen(scndFileName, "r");
    fgets(str, 99, fPointer2);

    while (!feof(fPointer2))
    {
        sectionEnd = 0;
        if (findSubstr(str, "[") != NULL && findSubstr(str, "]") != NULL)
        {
            
            isChecked = 0;
            for (int i = 0; i < k; i++)
                if (strcompare(str, checkedSectionNames[i]) == 0)
                {
                    isChecked = 1;
                    break;
                }

            if (isChecked == 0)
            {
                printf("%s", str);
                while (fgets(str, 99, fPointer2) != NULL)
                {
                    if (findSubstr(str, "[") != NULL && findSubstr(str, "]") != NULL)
                    {
                        sectionEnd = 1;
                        break;
                    }
                    printf("%s", str);
                }
            }
        }
        if (sectionEnd == 0)
            fgets(str, 99, fPointer2);
    }

    fclose(fPointer2);

    for (int i = 0; i < 99; i++)
    {
        free(checkedSectionNames[i]);
    }

    free(checkedSectionNames);
    free(str);

    fclose(fPointer1);
}

int main()
{
    char firstFileName[90] = "test_first.ini";
    char scndFileName[90] = "test_second.ini";

    mergeINIfiles(firstFileName, scndFileName);

    return 0;
}
