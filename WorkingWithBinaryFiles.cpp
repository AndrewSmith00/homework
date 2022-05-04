#include <iostream>
#include <stdio.h>

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

int getArrayFromFile(char* fileName);
void sortUprise(Student* arrOfStruct, int n);
void getGroupsInfo(Student* student, Group* groupInfo, int n);
int printStudentInfo(char* fileName);
Student getMaxBooksNumber(Student* arrOfStudent, int n);
Student getMaxBooksValue(Student* arrOfStudent, int n);

int main()
{
	char fileName[30];

	printf("Введите название файла для хранения данных\n");
	scanf("%s", fileName);

	//printStudentInfo(fileName);
	//setStudentInfo(fileName);
	getArrayFromFile(fileName);
	
	return 0;
}

int getArrayFromFile(char* fileName)
{
	Student* arrOfStudents = new Student[999];
	Group* groupsInfo = new Group[10];
	long count = 0;
	Student maxBooksNumber, maxBooksValue;

	FILE* fPtr = fopen(fileName, "rb");

	if (fPtr == NULL) {
		printf("Ошибка при открытии файла");
		return -1;
	}
	else {
		while (fread(&arrOfStudents[count], sizeof(struct Student), 1, fPtr) != 0)
		{
			count++;
			fseek(fPtr, count * sizeof(struct Student), 0);
		}

		getGroupsInfo(arrOfStudents, groupsInfo, count);

		printf("\nГруппы:\n");
		for (int i = 0; i < 11; i++)
		{
			if (groupsInfo[i].groupNumber > 0)
				printf("%d %d %d\n", groupsInfo[i].groupNumber, groupsInfo[i].booksNumber, groupsInfo[i].booksValue);
		}

		maxBooksNumber = getMaxBooksNumber(arrOfStudents, count);
		maxBooksValue = getMaxBooksValue(arrOfStudents, count);

		printf("Студент с максимальным количество книг:\n");
		printf("%s %s %s %s %d %d %d %d\n", maxBooksNumber.surname, maxBooksNumber.name, maxBooksNumber.secondname, maxBooksNumber.adressStreet, maxBooksNumber.adress, maxBooksNumber.groupNumber, maxBooksNumber.booksNumber, maxBooksNumber.booksValue);
		printf("Студент с максимальной стоимостью книг:\n");
		printf("%s %s %s %s %d %d %d %d\n", maxBooksValue.surname, maxBooksValue.name, maxBooksValue.secondname, maxBooksValue.adressStreet, maxBooksValue.adress, maxBooksValue.groupNumber, maxBooksValue.booksNumber, maxBooksValue.booksValue);

		return 0;
	}
}

int printStudentInfo(char* fileName)
{
	FILE* fPtr = fopen(fileName, "rb");
	Student student;
	
	if(!fPtr)
	{
		printf("File has not been opened");
		return -1;
	}
	else
	{
		while (fread(&student, sizeof(struct Student), 1, fPtr) != 0)
			printf("%d %s %s %s %s %d %d %d\n", student.groupNumber, student.surname, student.name, student.secondname, student.adressStreet, student.adress, student.booksNumber, student.booksValue);
		
		fclose(fPtr);
		return 0;
	}
}

//void sortUprise(Student* arrOfStruct, int n)
//{
//	Student temp;
//
//	for (int i = 0; i < n - 1; i++)
//		for (int j = 0; j < n - i - 1; j++)
//			if (arrOfStruct[j].groupNumber > arrOfStruct[j + 1].groupNumber)
//			{
//				temp = arrOfStruct[j];
//				arrOfStruct[j] = arrOfStruct[j + 1];
//				arrOfStruct[j + 1] = temp;
//			}
//}

Student getMaxBooksNumber(Student* arrOfStudent, int n)
{
	Student max;
	max.booksNumber = 0;

	for (int i = 0; i < n; i++)
		if (arrOfStudent[i].booksNumber > max.booksNumber)
			max = arrOfStudent[i];

	return max;
}

Student getMaxBooksValue(Student* arrOfStudent, int n)
{
	Student max;
	max.booksValue = 0;

	for (int i = 0; i < n; i++)
		if (arrOfStudent[i].booksValue > max.booksValue)
			max = arrOfStudent[i];

	return max;
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
