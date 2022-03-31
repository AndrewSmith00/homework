#include <stdio.h>
#include <iostream>

using namespace std;

struct Student {
	char name[60];
	char surname[30];
	int age;
	char faculty[15];
	int marks[4];
	bool isGrant = true;
};

Student* setStudentInfo(int num);
void printStudentInfo(Student* studentList, int num);
void getStudentsWithGrants(Student* studentList, int num);
void printStudentsWithGrants(Student* studentList, int num);

int main()
{
	setlocale(LC_ALL, "Rus");

	int numberOfStudent = 2;
	Student* studentList = new Student[numberOfStudent];

	//studentList = setStudentInfo(numberOfStudent);

	studentList[0] = { "Ann", 22, "pmk", {3, 4, 5, 3} };
	studentList[1] = { "John", 22, "pmk", {4, 4, 5, 3} };

	printStudentInfo(studentList, numberOfStudent);
	getStudentsWithGrants(studentList, numberOfStudent);

	printStudentsWithGrants(studentList, numberOfStudent);
}

Student* setStudentInfo(int num) {
	Student* studentList = new Student[num];

	for (int i = 0; i < num; i++)
	{
		printf("%d.\nName: ", i+1);
		scanf_s("%s", studentList[i].name, 30);
		printf("\n");
		
		printf("%d.\nSurname: ", i+1);
		scanf_s("%s", studentList[i].surname, 30);
		printf("\n");

		printf("Age: ");
		scanf_s("%d", &studentList[i].age);
		printf("\n");

		printf("Faculty: ");
		scanf_s("%s", studentList[i].faculty, 15);
		printf("\n");

		printf("Marks: ");
		printf("\n");
		for (int j = 0; j < 4; j++)
		{
			printf("\t%d): ", j+1);
			scanf_s("%d", &studentList[i].marks[j]);
			printf("\n");
		}
	}
	return studentList;
}

void printStudentInfo(Student* studentList, int num) {

	for (int i = 0; i < num; i++)
	{
		printf("%d.\nName: %s\n", i + 1, strcat(studentList[i].name, studentList[i].surname)); 

		printf("Age: %d\n", studentList[i].age);

		printf("Faculty: %s\n", studentList[i].faculty);

		printf("Marks: \n");
		for (int j = 0; j < 4; j++)
			printf("\t%d): %d\n", j + 1, studentList[i].marks[j]);
	}
	printf("\n");
}

void getStudentsWithGrants(Student* studentList, int num) {
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < 4; j++)
			if (studentList[i].marks[j] < 4) {
				studentList[i].isGrant = false;
				break;
			}
	}
}

void printStudentsWithGrants(Student* studentList, int num) {
	int count = 0;
	
	for (int i = 0; i < num; i++)
		if (studentList[i].isGrant)
		{
			printf("%s %d %s\n", strcat(studentList[i].name, studentList[i].surname), studentList[i].age, studentList[i].faculty);
			count++;
		}

	if (count == 0)
		printf("No students with grants");
}
