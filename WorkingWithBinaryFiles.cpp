#include <iostream>
#include <stdio.h>
#pragma warning(disable : 4996) 

using namespace std;

int setStudentInfo(char* fileName);

struct StudentInfo
{
    char name[30]; 
    char adress[30];
    int groupNumber, booksNumber, booksValue;
};

int main()
{
    setlocale(LC_ALL, "Rus");

    char fileName[30];

    printf("Введите название файла для хранения данных\n");
    gets_s(fileName);

    setStudentInfo(fileName);
}

int setStudentInfo(char* fileName)
{
    FILE* fPtr = fopen(fileName, "wb");
    struct StudentInfo student;
    char buffer[200];
    int size;
    
    if (fPtr == NULL) {
        printf("Ошибка при создании файла");
        return -1;
    }
    else {
        //printf("Вводите данные о студентах. Для завершения введите exit\n");
        //scanf("%s%s%d%d%d", student.name, student.adress, &student.groupNumber, &student.booksNumber, &student.booksValue);

        student = { "ddd", "ddd", 15, 15, 15 };

        fwrite(&student, sizeof(struct StudentInfo), 1, fPtr);
        fclose(fPtr);
    }
}