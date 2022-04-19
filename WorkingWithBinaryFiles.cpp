#include <iostream>
#include <stdio.h>
#include <windows.h>
#pragma warning(disable : 4996) 

using namespace std;

struct Student
{
    char name[30];
    char surname[30];
    char secondname[30];
    char adressStreet[30];
    int adress, groupNumber, booksNumber, booksValue;
};

struct Group
{
    int groupNumber, booksNumber, booksValue;
};


int setStudentInfo(char* fileName);
int getArrayFromFile(char* fileName);
void sortUprise(Student* arrOfStruct, int n);
void getGroupsInfo(Student* student, Group* groupInfo, int n);

int main()
{
    SetConsoleCP(1251); 
    SetConsoleOutputCP(1251);

    char fileName[30];

    printf("Введите название файла для хранения данных\n");
    gets_s(fileName);

    setStudentInfo(fileName);
    getArrayFromFile(fileName);
}

int setStudentInfo(char* fileName)
{
    FILE* fPtr = fopen(fileName, "wb");
    struct Student student;
    int count;
    
    if (fPtr == NULL) {
        printf("Ошибка при создании файла");
        return -1;
    }
    else {
        printf("Введите количество студентов:\n");
        scanf("%d", &count);

        printf("Вводите данные о студентах:\n");

        for (int i = 0; i < count; i++)
        {
            scanf("%s%s%s%s%d%d%d%d", student.surname, student.name, student.secondname, student.adressStreet, &student.adress, &student.groupNumber, &student.booksNumber, &student.booksValue);
            fwrite(&student, sizeof(struct Student), 1, fPtr);
        }
        fclose(fPtr);
        return 0;
    }
}

int getArrayFromFile(char* fileName)
{
    Student* arrOfStudents = new Student[999];
    Group* groupsInfo = new Group[10];
    long count = 0;

    FILE* fPtr = fopen(fileName, "rb");

    if (fPtr == NULL) {
        printf("Ошибка при открытии файла");
        return -1;
    }
    else {
        while ( fread(&arrOfStudents[count], sizeof(struct Student), 1, fPtr) != NULL )
        {
            count++;
            fseek(fPtr, count * sizeof(struct Student), 0);
        }

        getGroupsInfo(arrOfStudents, groupsInfo, count);

        printf("\nГруппы:\n");
        for (int i = 0; i < 11; i++)
        {
            if(groupsInfo[i].groupNumber > 0)
                printf("%d %d %d\n", groupsInfo[i].groupNumber, groupsInfo[i].booksNumber, groupsInfo[i].booksValue);
        }
        return 0;
    }
}

void sortUprise(Student* arrOfStruct, int n) 
{
    Student temp;

    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arrOfStruct[j].groupNumber > arrOfStruct[j + 1].groupNumber)
            {
                temp = arrOfStruct[j];
                arrOfStruct[j] = arrOfStruct[j + 1];
                arrOfStruct[j + 1] = temp;
            }
}

void getGroupsInfo(Student* student, Group* groupInfo, int n)
{
    int num;

    for (int i = 0; i < 10; i++)
    {
        groupInfo[i].groupNumber = 0;
        groupInfo[i].booksNumber = 0;
        groupInfo[i].booksValue = 0;
    }

    for (int i = 0; i < n; i++)
    {
        num = student[i].groupNumber;
        groupInfo[num].groupNumber = num;
        groupInfo[num].booksNumber += student[i].booksNumber;
        groupInfo[num].booksValue += student[i].booksValue;
    }

}
