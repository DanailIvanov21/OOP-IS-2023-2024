
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
const size_t MAX_LENGTH = 100;
enum class AnimalType
{
	UNKNOWN,
	REPTILE,
	MAMMAL,
	PREDATOR
};

struct Animal
{
	char* name;
	AnimalType animalType;
};

struct Person
{
	char* name;
	char* department;
};

struct Zoo
{
	Person* employees;
	Animal* animals;
	size_t animalCount;
	size_t employeeCount;
};

void writeAnimals(const char* fileName, const size_t animalCount, const Animal* animals)
{
	std::ofstream out(fileName, std::ios::binary);
	if (out.is_open())
	{
		std::cout << "Error: Could not open file: " << fileName << std::endl;
		return;
	}

	out.write((const char*)&animalCount, sizeof(animalCount));
	for (size_t i = 0; i < animalCount; ++i)
	{
		size_t nameLength = strlen(animals[i].name);
		out.write((const char*)&nameLength, sizeof(size_t));
		out.write(animals[i].name, nameLength);

		out.write((const char*)&animals[i].animalType, sizeof(AnimalType));
	}

	out.close();
}

void writeEmployees(const char* fileName, const size_t employeeCount, const Person* employees)
{
	std::ofstream out(fileName, std::ios::binary);
	if (out.is_open())
	{
		std::cout << "Error: Could not open file: " << fileName << std::endl;
		return;
	}

	out.write((const char*)&employeeCount, sizeof(employeeCount));
	for (size_t i = 0; i < employeeCount; ++i)
	{
		size_t nameLength = strlen(employees[i].name);
		out.write((const char*)&nameLength, sizeof(size_t));
		out.write(employees[i].name, nameLength);

		size_t depLength = strlen(employees[i].department);
		out.write((const char*)&depLength, sizeof(size_t));
		out.write(employees[i].department, depLength);
	}

	out.close();
}

void writeZoo(const char* fileName, const Zoo& zoo)
{
	std::ofstream out(fileName, std::ios::binary);
	if (!out.is_open())
	{
		std::cout << "Error: Could not open file: " << fileName << std::endl;
		return;
	}

	// write employees
	out.write((const char*)(&zoo.employeeCount), sizeof(zoo.employeeCount));
	for (size_t i = 0; i < zoo.employeeCount; ++i)
	{
		size_t nameLength = strlen(zoo.employees[i].name);
		out.write((const char*)(&nameLength), sizeof(size_t));
		out.write(zoo.employees[i].name, nameLength);

		size_t depLength = strlen(zoo.employees[i].department);
		out.write((const char*)(&depLength), sizeof(size_t));
		out.write(zoo.employees[i].department, depLength);
	}

	// write animals
	out.write((const char*)&zoo.animalCount, sizeof(zoo.animalCount));
	for (size_t i = 0; i < zoo.animalCount; ++i)
	{
		size_t nameLength = strlen(zoo.animals[i].name);
		out.write((const char*)(&nameLength), sizeof(size_t));
		out.write(zoo.animals[i].name, nameLength);

		out.write((const char*)(&zoo.animals[i].animalType), sizeof(AnimalType));
	}

	out.close();
}

Person* readEmployees(const char* fileName)
{
	std::ifstream in(fileName, std::ios::binary);
	if (in.is_open())
	{
		std::cout << "Error: Could not open file: " << fileName << std::endl;
		return nullptr;
	}

	size_t employeeCnt;
	in.read((char*)&employeeCnt, sizeof(employeeCnt));

	Person* employees = new Person[employeeCnt];

	for (size_t i = 0; i < employeeCnt; i++)
	{
		size_t nameSize;
		in.read((char*)&nameSize, sizeof(size_t));
		employees[i].name = new char[nameSize];
		in.read(employees[i].name, nameSize);

		size_t departmentSize;
		in.read((char*)&departmentSize, sizeof(size_t));
		employees[i].department = new char[departmentSize];
		in.read(employees[i].department, departmentSize);
	}

	return employees;
}

Animal* readAnimals(const char* fileName)
{
	std::ifstream in(fileName, std::ios::binary);
	if (in.is_open())
	{
		std::cout << "Error: Could not open file: " << fileName << std::endl;
		return nullptr;
	}

	size_t animalCnt;
	in.read((char*)&animalCnt, sizeof(size_t));
	Animal* animals = new Animal[animalCnt];

	for (size_t i = 0; i < animalCnt; i++)
	{
		size_t nameSize;
		in.read((char*)&nameSize, sizeof(size_t));
		animals[i].name = new char[nameSize];
		in.read(animals[i].name, nameSize);

		in.read((char*)&animals[i].animalType, sizeof(AnimalType));
	}

	return animals;
}

Zoo readZoo(const char* fileName)
{
	std::ifstream in(fileName, std::ios::binary);

	Zoo zoo;
	if (!in.is_open())
	{
		std::cout << "Error: Could not open file: " << fileName << std::endl;

		zoo.animalCount = 0;
		zoo.employeeCount = 0;
		zoo.animals = nullptr;
		zoo.employees = nullptr;

		return zoo;
	}

	size_t animalCount, employeeCount;

	// read emoloyees
	in.read((char*)&employeeCount, sizeof(size_t));
	zoo.employeeCount = employeeCount;
	zoo.employees = new Person[employeeCount];

	for (size_t i = 0; i < employeeCount; i++)
	{
		size_t nameSize;
		in.read((char*)&nameSize, sizeof(size_t));
		zoo.employees[i].name = new char[nameSize + 1];
		in.read(zoo.employees[i].name, nameSize);
		zoo.employees[i].name[nameSize] = '\0';

		size_t departmentSize;
		in.read((char*)&departmentSize, sizeof(size_t));
		zoo.employees[i].department = new char[departmentSize + 1];
		in.read(zoo.employees[i].department, departmentSize);
		zoo.employees[i].department[departmentSize] = '\0';
	}

	// read animals
	in.read((char*)&animalCount, sizeof(animalCount));
	zoo.animalCount = animalCount;
	zoo.animals = new Animal[animalCount];

	for (size_t i = 0; i < animalCount; i++)
	{
		size_t nameSize;
		in.read((char*)&nameSize, sizeof(size_t));
		zoo.animals[i].name = new char[nameSize + 1];
		in.read(zoo.animals[i].name, nameSize);
		zoo.animals[i].name[nameSize] = '\0';

		in.read((char*)&zoo.animals[i].animalType, sizeof(AnimalType));
	}

	return zoo;
}

void initializeAnimal(Animal& animal)
{
	std::cin.ignore();
	std::cout << "\tEnter animal name: ";
	char name[MAX_LENGTH];
	std::cin.getline(name, MAX_LENGTH);

	animal.name = new char[strlen(name) + 1];
	strcpy(animal.name, name);

	std::cout << "\tEnter animal type(1 - Reptile, 2 - Mammal, 3 - Predator): ";
	int type;
	std::cin >> type;

	if (type < 1 || type > 3)
		type = 0;

	animal.animalType = (AnimalType)type;
}

void initializeEmployee(Person& employee)
{
	char name[MAX_LENGTH];
	char department[MAX_LENGTH];

	std::cout << "\tEnter person name: ";
	std::cin.getline(name, MAX_LENGTH);

	employee.name = new char[strlen(name) + 1];
	strcpy(employee.name, name);

	std::cout << "\tEnter person department: ";
	std::cin.getline(department, MAX_LENGTH);

	employee.department = new char[strlen(department) + 1];
	strcpy(employee.department, department);
}

void initializeAnimals(Animal* animals, const size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		initializeAnimal(animals[i]);
		std::cout << std::endl;
	}
}

void initializeEmployees(Person* employee, const size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		initializeEmployee(employee[i]);
		std::cout << std::endl;
	}
}

void initializeZoo(Zoo& zoo, const Animal* animals, const size_t animalCnt, const Person* employees, const size_t employeeCnt)
{
	zoo.animalCount = animalCnt;
	zoo.employeeCount = employeeCnt;

	zoo.animals = new Animal[animalCnt];
	zoo.employees = new Person[employeeCnt];

	for (size_t i = 0; i < animalCnt; i++)
	{
		zoo.animals[i].animalType = animals[i].animalType;

		zoo.animals[i].name = new char[strlen(animals[i].name) + 1];
		strcpy(zoo.animals[i].name, animals[i].name);
	}

	for (size_t i = 0; i < employeeCnt; i++)
	{
		zoo.employees[i].department = new char[strlen(employees[i].department) + 1];
		strcpy(zoo.employees[i].department, employees[i].department);

		zoo.employees[i].name = new char[strlen(employees[i].name) + 1];
		strcpy(zoo.employees[i].name, employees[i].name);
	}
}

void printAnimals(const Animal* animals, const size_t animalCnt)
{
	for (size_t i = 0; i < animalCnt; i++)
	{
		std::cout << "Animal name: " << animals[i].name << std::endl;
		std::cout << "Animal type: ";

		switch (animals[i].animalType)
		{
		case AnimalType::REPTILE:
			std::cout << "Reptile\n";
			break;
		case AnimalType::MAMMAL:
			std::cout << "Mammal\n";
			break;
		case AnimalType::PREDATOR:
			std::cout << "Predator\n";
			break;
		case AnimalType::UNKNOWN:
			std::cout << "Unknown\n";
			break;
		}

		std::cout << std::endl;
	}
}

void printEmployees(const Person* empoyees, const size_t employeeCnt)
{
	for (size_t i = 0; i < employeeCnt; i++)
	{
		std::cout << "Employee name: " << empoyees[i].name << std::endl;
		std::cout << "Employee department: " << empoyees[i].department << std::endl;
		std::cout << std::endl;
	}
}

void printZoo(const Zoo& zoo)
{
	std::cout << "List of zoo employees\n";
	printEmployees(zoo.employees, zoo.employeeCount);

	std::cout << "\nList of zoo animals\n";
	printAnimals(zoo.animals, zoo.animalCount);
}

void freeAnimal(Animal* animals, const size_t animalCnt)
{
	for (size_t i = 0; i < animalCnt; i++)
	{
		delete[] animals[i].name;
	}
}

void freePerson(Person* employees, const size_t employeeCnt)
{
	for (size_t i = 0; i < employeeCnt; i++)
	{
		delete[] employees[i].name;
		delete[] employees[i].department;
	}
}

void freeZoo(Zoo& z)
{
	for (size_t i = 0; i < z.animalCount; i++)
	{
		delete[] z.animals[i].name;
	}

	for (size_t i = 0; i < z.employeeCount; i++)
	{
		delete[] z.employees[i].name;
		delete[] z.employees[i].department;
	}
}

int main()
{
	
	
	//trqbva dannite da se prochetat ot konzolata i sled tova
	// da se zapishat dannite ot zooparka vuv faila zoo.bin.
	Zoo zoo2 = readZoo("zoo.bin");
	printZoo(zoo2);

	freeZoo(zoo2);

	return 0;
}