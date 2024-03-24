### Задача 1 - 1 точка

Напишете програма, която записва и чете данни в текстов файл масиви от обекти на структура,
която съдържа следната информация за един студент:

- firstName (char array)
- lastName (string)
- facultyNumber(string)
- takenCourses(int)
- averageGrade(double)
- hasTakenAllCourses(bool)

<details><summary><b>Solution</b></summary> 
<p>

```cpp
#include <iostream>
#include <cstring>
#include <fstream>

struct Name 
{
	char* firstName;
	char* lastName;
};

struct Student
{
	Name name;
	char facultyNumber[11]; // Follows 1MI0700001 format
	unsigned takenCourses;
	double averageGrade;
	bool hasPassedAllCourses;
};

Name createName(const char* firstName, const char* lastName) 
{
	if (firstName == nullptr)
		return createName("", lastName);

	if (lastName == nullptr)
		return createName(firstName, "");

	Name newName;
	newName.firstName = strcpy(new char[strlen(firstName) + 1], firstName); // Cool shorthand for copying a string!!
	newName.lastName = strcpy(new char[strlen(lastName) + 1], lastName);

	return newName;
}

void deleteName(Name& name)
{
	if (name.firstName != nullptr)
		delete[] name.firstName;

	if (name.lastName != nullptr)
		delete[] name.lastName;
}

Student createStudent(const Name& name, const char* facultyNumber, 
					  unsigned takenCourses = 0, double averageGrade = 2.0, 
					  bool hasPassedAllCourses = false) 
{
	Student student;
	student.name = createName(name.firstName, name.lastName);

	if (facultyNumber == nullptr || strlen(facultyNumber) != 10)
		strcpy(student.facultyNumber, "0SU0000000"); // Some default faculty number
	else
		strcpy(student.facultyNumber, facultyNumber);

	student.takenCourses = takenCourses;
	student.averageGrade = averageGrade >= 2.0 && averageGrade <= 6 ? averageGrade : 2.0;
	student.hasPassedAllCourses = hasPassedAllCourses;

	return student;
}

void deleteStudent(Student& student)
{
	deleteName(student.name);
	student.facultyNumber[0] = '\0';
	student.averageGrade = 2.0;
	student.takenCourses = 0;
	student.hasPassedAllCourses = false;
}

char* readStringFromFile(std::ifstream& stream, char delimiter = '\n')
{
	if (!stream.is_open() || !stream.good())
		return nullptr;

	char* readString = strcpy(new char[1], "");
	char currentChar = stream.get();

	while (stream.good() && !stream.eof() && currentChar != delimiter)
	{
		char* oldString = readString;
		size_t oldStringLength = strlen(oldString);

		// oldStringLength + 2, because we want to add one more character;
		readString = strcpy(new char[oldStringLength + 2], oldString);
		readString[oldStringLength] = currentChar;
		readString[oldStringLength + 1] = '\0';
		delete[] oldString;

		currentChar = stream.get();
	}

	return readString;
}

void writeStudentToFile(const Student& student, std::ofstream& stream)
{
	if (!stream.is_open() || !stream.good())
		return;

	stream << student.name.firstName;
	stream << ",";
	stream << student.name.lastName;
	stream << ",";
	stream << student.facultyNumber;
	stream << ",";
	stream << student.takenCourses;
	stream << ",";
	stream << student.averageGrade;
	stream << ",";
	stream << student.hasPassedAllCourses;
	stream << "\n";
}

Student readStudentFromFile(std::ifstream& stream)
{
	if (!stream.is_open() || !stream.good())
	{
		Student student;
		student.name = Name{ nullptr, nullptr };
		student.averageGrade = 2.0;
		strcpy(student.facultyNumber, "0SU0000000");
		student.takenCourses = 0;
		student.hasPassedAllCourses = false;
	}
	
	char* firstName = readStringFromFile(stream, ',');
	char* lastName = readStringFromFile(stream, ',');
	char* facultyNumber = readStringFromFile(stream, ',');

	unsigned takenCourses;
	stream >> takenCourses;
	stream.get();

	double averageGrade;
	stream >> averageGrade;
	stream.get();

	bool hasPassedAllCourses;
	stream >> hasPassedAllCourses;
	stream.get();

	Name name{ firstName, lastName };
	Student student = createStudent(name, facultyNumber, takenCourses, averageGrade, hasPassedAllCourses);

	deleteName(name);
	delete[] facultyNumber;

	return student;
}

size_t getNewLinesCount(std::ifstream& stream)
{
	if (!stream.is_open() || !stream.good())
		return 0;

	size_t count = 0;
	char currentChar = stream.get();

	while (stream.good() && !stream.eof())
	{
		if (currentChar == '\n')
			count++;

		currentChar = stream.get();
	}

	return count;
}

Student* readStudentsFromFile(std::ifstream& stream, size_t& size)
{
	size = getNewLinesCount(stream);

	if (size == 0)
		return nullptr;

	stream.clear();
	stream.seekg(0, std::ios::beg);

	Student* readStudents = new Student[size];

	for (size_t i = 0; i < size; i++)
	{
		if (!stream.good())
		{
			size = 0;
			for (size_t deleteIt = 0; deleteIt < i; deleteIt++)
			{
				deleteStudent(readStudents[deleteIt]);
			}

			return nullptr;
		}

		readStudents[i] = readStudentFromFile(stream);
	}

	return readStudents;
}

void printStudent(const Student& student)
{
	std::cout << "Name: " << student.name.firstName << " " << student.name.lastName << "\n";
	std::cout << "FN: " << student.facultyNumber << "\n";
	std::cout << "Average grade: " << student.averageGrade << "\n";
	std::cout << "Taken courses: " << student.takenCourses << "\n";
	std::cout << "Has passed all courses " << std::boolalpha << student.hasPassedAllCourses << std::endl;
}

int main()
{
	Name firstName = createName("Ivan", "Marinov");
	Name secondName = createName("Kiril", "Ivanov");
	Name thirdName = createName("Monika", "Stefanova");

	Student students[3]{
		createStudent(firstName, "2MI0724156", 5, 5.23, true),
		createStudent(secondName, "0MI0726156", 2, 4.23, false),
		createStudent(thirdName, "2MI0725156", 10, 4.23, true)
	};

	// Don't forget to delete the names
	// This design is made on purpose
	// In order tho show how easy you can
	// Make unoptimized code :))
	deleteName(firstName);
	deleteName(secondName);
	deleteName(thirdName);

	std::ofstream outStream("students.txt", std::ios::out, std::ios::trunc);

	if (!outStream.is_open())
		return -1;

	for (size_t i = 0; i < 3; i++)
	{
		writeStudentToFile(students[i], outStream);
		deleteStudent(students[i]);
	}

	outStream.close();

	std::ifstream inStream("students.txt", std::ios::in);

	if (!inStream.is_open())
		return -1;

	size_t studentsSize = 0;
	Student* readStudents = readStudentsFromFile(inStream, studentsSize);

	for (int i = 0; i < studentsSize; i++)
	{
		printStudent(readStudents[i]);
		std::cout << "\n";
		deleteStudent(readStudents[i]);
	}

	if (readStudents != nullptr)
		delete[] readStudents;

	inStream.close();
}
```

</p>
</details>

### Задача 2 - 1 точка

Реализирайте функция със следната сигнатура:
void replace(const char* fileName, const char* find, const char* replace);
която да замества всички срещания на думата find с думата replace в текстов файл с име fileName.

- Пример (извикваме функцията с параметри "princesa.txt", "princesa", "strandzhanka"):

 Преди излълнение на програмата:

Prepechena filiq s kaima se naricha princesa i tova ne podlezhi na komentar.
Sinut na princesa Diana se kazva Harry.
Princ Karl i princesa Klara krali klarineti...
След излълнение на програмата:

Prepechena filiq s kaima se naricha strandzhanka i tova ne podlezhi na komentar.
Sinut na strandzhanka Diana se kazva Harry.
Princ Karl i strandzhanka Klara krali klarineti...

### Задача 3 - 1 точка

а)Напишете програма която прочита два текстови файла и създава трети със съдържанието на първия и втория.
б)Напишете програма която премахва всички празни редове от новополучения текстов файл.
в)Напишете програма, която променя текстов файл като - преобразува всички главни букви в малки и обратното, ако има такива.

### Задача 4 - 1 точка

Да се напише програма, която  прочита своя код и изписва на екрана колко променливи има от целочислен тип,
колко от дробен тип и колко от символен тип.

<details><summary><b>Solution</b></summary> 
<p>

```cpp
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstring>
#include <fstream>

struct TypesCount
{
	unsigned int boolCount = 0;
	unsigned int integerCount = 0;
	unsigned int floatingCount = 0;
	unsigned int charcterCount = 0;
};

bool isWordType(const char* type, std::ifstream& stream)
{
	if (type == nullptr)
		return false;

	if (stream.peek() != *type)
		return false;

	std::ios::streampos begPos = stream.tellg();
	while (stream.good() && !stream.eof())
	{
		if (*type == '\0')
			break;

		if (*type != stream.get())
		{
			stream.seekg(begPos, std::ios::beg);
			return false;
		}

		type++;
	}

	if (*type != '\0' || stream.peek() != ' ')
	{
		stream.seekg(begPos, std::ios::beg);
		return false;
	}

	return true;
}

TypesCount calculateTypesCount()
{
	std::ifstream sourceCode("week2t4.cpp", std::ios::in);

	TypesCount count;

	if (!sourceCode.is_open())
		return count;

	while (sourceCode.good() && !sourceCode.eof())
	{
		if (isWordType("bool", sourceCode)) count.boolCount++;
		else if (isWordType("int", sourceCode)) count.integerCount++;
		else if (isWordType("double", sourceCode)) count.floatingCount++;
		else if (isWordType("char", sourceCode)) count.charcterCount++;
		else sourceCode.get();
	}

	sourceCode.close();
	
	return count;
}

int main()
{
	TypesCount count = calculateTypesCount();

	std::cout << "Bool count " << count.boolCount << "\n";
	std::cout << "Int count " << count.integerCount << "\n";
	std::cout << "Double count " << count.floatingCount << "\n";
	std::cout << "Char count " << count.charcterCount << std::endl;

	double test;
	double test2;
	bool damnItIsTrue;
	char myChar;
}
```

</p>
</details>