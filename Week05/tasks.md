### Задача 1

Да се напиша такава програма, която описва бар с 1024 места.
Барът разполага с 8 на брой напитки:

* Вода
* Сок
* Бира
* Уиски
* Вино
* Водка
* Джин
* Ром

Всяко място има диспенсер, което предлага една, няколко или всички напитки.
Всеки бар се характеризира с име с произволна дължина.

Всеки бар трябва да има функционалност по подадени напитки, да заема първото свободно място на което се предлагат всички от подадените напитки. Трябва да можем по подадени място да добавяме или премахваме напитки от бара. Също трябва да можем да принтираме статуса на всяко място.

<details><summary><b>Solution</b></summary> 
<p>

```cpp
// This is a partial solution
// TODO: Finish the solution

#include <cstring>

enum class Drink : unsigned char
{
	WATER  = 1 << 0,
	JUICE  = 1 << 1,
	BEER   = 1 << 2,
	WISKEY = 1 << 3,
	WINE   = 1 << 4,
	VODKA  = 1 << 5,
	GIN    = 1 << 6,
	RUM    = 1 << 7
};

class Bar
{
public:
	Bar(const char* barName, unsigned seed = 100)
		: name(setString(barName)), seats{0}
	{
		for (size_t i = 0; i < 1024; i++)
		{
			setDrinks(i, seed % 256);

			if (seed % 2 == 0)
				seed *= 2.5;
			else
				seed /= 1.5;
		}
	}

	Bar(const Bar& bar)
	{
		copyData(bar);
	}

	~Bar()
	{
		delete[] name;
	}

	Bar& operator=(const Bar& other)
	{
		if (this != &other)
		{
			delete[] name;
			copyData(other);
		}

		return *this;
	}

	void setDrink(size_t seat, Drink drink)
	{
		if (seat >= 1024)
			return;

		drinks[seat] |= (unsigned char)drink;
	}

	void removeDrink(size_t seat, Drink drink)
	{
		if (seat >= 1024)
			return;

		drinks[seat] &= ~(unsigned char)drink;
	}

	void setDrinks(size_t seat, unsigned char drink)
	{
		if (seat >= 1024)
			return;

		drinks[seat] = drink;
	}

	void takePlace(size_t seatIndex)
	{
		if (seatIndex >= 1024)
			return;

		unsigned char seatOffset = seatIndex % 8;
		seats[seatIndex / 8] |= 1 << seatOffset;
	}

	void removePlace(size_t seatIndex)
	{
		if (seatIndex >= 1024)
			return;

		size_t clusterIndex = seatIndex / 8;
		unsigned char seatOffset = seatIndex % 8;
		seats[clusterIndex] &= ~(1 << seatOffset);
	}

	bool isSeatTaken(size_t seatIndex) const
	{
		if (seatIndex >= 1024)
			return false;

		size_t clusterIndex = seatIndex / 8;
		unsigned char seatOffset = seatIndex % 8;

		return seats[clusterIndex] & (1 << seatOffset);
	}

private:
	char* name;
	unsigned char seats[1024 / 8];
	unsigned char drinks[1024];

	char* setString(const char* str)
	{
		if (str == nullptr)
			return strcpy(new char[8], "Unknown");
		else
			return strcpy(new char[strlen(str) + 1], str);
	}

	void copyData(const Bar& other)
	{
		name = setString(other.name);

		for (size_t i = 0; i < 128; i++)
		{
			seats[i] = other.seats[i];
		}

		for (size_t i = 0; i < 1024; i++)
		{
			drinks[i] = other.drinks[i];
		}
	}
};

int main()
{
	Bar bar("The shots", 234);
	Bar bar2("The shots 2", 2324);
	Bar copyBar(bar);

	copyBar = bar2;
	copyBar = copyBar;
}
```

</p>
</details>


### Задача 2

Реализирайте клас person, който се характеризира с две имена (всяко от тях е символен низ с произволна дължина), пол(мъж или жена), година на раждане.
Дефинирайте методи за достъп до всяка от характеристиките на обект от класа person.


Реализирайте Клас car, който се характеризира с марка(символен низ с дължина, нейнадминаваща 127 символа), собственик (обект от клас person) и година на регистрация.

Реализирайте методи за запис и четене на данни за автомобил е текстов файл. Данните във файла трябва да бъдат поддържани валидни според спецификацията на класовете. Вашият код трябва да може да запише в такъв файл данни за масив от автомобили и след това успешно да го прочете

Реализирайте функция, която прочита от такъв текстов файл множество автомобили и връща като резултат най често срещата марка (марката, от която има най голям брой автомобили).

Ако има повече от една марка с максимален брой автомобили, да се върна лексикографски най малката от най често срещаните

<details><summary><b>Solution</b></summary> 
<p>

Person.h
```cpp
#pragma once

#include <fstream>

enum Gender {
	UNKNOWN = -1,
	MALE,
	FEMALE
};

class Person
{
public:
	Person(const char* firstName, const char* lastName, Gender gender, unsigned short yearOfBirth);
	Person(const Person& other);
	~Person();

	Person& operator=(const Person& other);

	const char* getFirstName() const;
	const char* getLastName() const;
	Gender getGender() const;
	unsigned short getYearOfBirth() const;

	void serialize(std::ofstream& stream) const;
	void deserialize(std::ifstream& stream);

	void setFirstName(const char* firstName);
	void setLastName(const char* lastName);
	void setGender(Gender gender);
	void setYearOfBirth(unsigned short yearOfBirth);

private:
	char* firstName;
	char* lastName;
	Gender gender;
	unsigned short yearOfBirth;

	void freeMemory();
	void copyFrom(const Person& other);
	char* copyStringOrEmpty(const char* str);
	char* getNextStringEntry(std::ifstream& stream);
};
```

Person.cpp
```cpp
#define _CRT_SECURE_NO_WARNINGS

#include "Person.h"

#include <cstring>

Person::Person(const char* firstName, const char* lastName, Gender gender, unsigned short yearOfBirth) :
    firstName(copyStringOrEmpty(firstName)),
    lastName(copyStringOrEmpty(lastName)),
    gender(gender), yearOfBirth(yearOfBirth)
{
}

Person::Person(const Person& other)
{
    copyFrom(other);
}

Person::~Person()
{
    freeMemory();
}

Person& Person::operator=(const Person& other)
{
    if (this != &other)
    {
        freeMemory();
        copyFrom(other);
    }

    return *this;
}

const char* Person::getFirstName() const
{
    return firstName;
}

const char* Person::getLastName() const
{
    return lastName;
}

Gender Person::getGender() const
{
    return gender;
}

unsigned short Person::getYearOfBirth() const
{
    return yearOfBirth;
}

void Person::serialize(std::ofstream& stream) const
{
    if (!stream.is_open() || !stream.good())
        return;

    stream << firstName;
    stream << ',';
    stream << lastName;
    stream << ',';
    stream << gender;
    stream << ',';
    stream << yearOfBirth;
}

void Person::deserialize(std::ifstream& stream)
{
    if (!stream.is_open() || !stream.good())
        return;

    delete[] firstName;
    firstName = getNextStringEntry(stream);
    stream.get(); // Getting rid of ','

    delete[] lastName;
    lastName = getNextStringEntry(stream);
    stream.get(); // Getting rid of ','

    int genderIndex;
    stream >> genderIndex;

    gender = genderIndex == 0 || genderIndex == 1 ? Gender(genderIndex) : Gender::UNKNOWN;
    stream.get(); // Getting rid of ','

    stream >> yearOfBirth;
}

void Person::setFirstName(const char* firstName)
{
    if (firstName == nullptr)
        return;

    delete[] this->firstName;
    this->firstName = copyStringOrEmpty(firstName);
}

void Person::setLastName(const char* lastName)
{
    if (lastName == nullptr)
        return;

    delete[] this->lastName;
    this->lastName = copyStringOrEmpty(lastName);
}

void Person::setGender(Gender gender)
{
    this->gender = gender;
}

void Person::setYearOfBirth(unsigned short yearOfBirth)
{
    this->yearOfBirth = yearOfBirth;
}

void Person::freeMemory()
{
    delete[] firstName;
    delete[] lastName;
}

void Person::copyFrom(const Person& other)
{
    firstName = copyStringOrEmpty(other.firstName);
    lastName = copyStringOrEmpty(other.lastName);
    gender = other.gender;
    yearOfBirth = other.yearOfBirth;
}

char* Person::copyStringOrEmpty(const char* str)
{
    if (str == nullptr)
        return copyStringOrEmpty("");

    return strcpy(new char[strlen(str) + 1], str);
}

char* Person::getNextStringEntry(std::ifstream& stream)
{
    std::streampos currentPos = stream.tellg();
    size_t stringLength = 0;

    while (stream.get() != ',')
        stringLength++;

    stream.seekg(currentPos, std::ios::beg);

    char* readString = new char[stringLength + 1];

    size_t currStringPos = 0;
    while (stream.peek() != ',' && currStringPos < stringLength)
    {
        readString[currStringPos] = stream.get();
        currStringPos++;
    }

    readString[currStringPos] = '\0';
    return readString;
}

```

Car.h
```cpp
#pragma once

#include "Person.h"

#include <fstream>

class Car
{
public:
	Car(const char* brand, const Person& owner, unsigned short yearOfRegsitration);

	const char* getBrand() const;
	const Person& getOwner() const;
	unsigned short getYearOfRegistration() const;

	void serialize(std::ofstream& stream) const;
	void deserialize(std::ifstream& stream);

private:
	char brand[128];
	Person owner;
	unsigned short yearOfRegistration;

	void setBrand(const char* brand);
	char* getNextStringEntry(std::ifstream& stream);
	unsigned short clamp(unsigned short value, unsigned short min, unsigned short max);
};
```

Car.cpp
```cpp
#define _CRT_SECURE_NO_WARNINGS

#include "Car.h"

Car::Car(const char* brand, const Person& owner, unsigned short yearOfRegsitration) :
    owner(owner),
    yearOfRegistration(clamp(yearOfRegsitration, 1800, 2024))
{
    setBrand(brand);
}

const char* Car::getBrand() const
{
    return brand;
}

const Person& Car::getOwner() const
{
    return owner;
}

unsigned short Car::getYearOfRegistration() const
{
    return yearOfRegistration;
}

void Car::serialize(std::ofstream& stream) const
{
    if (!stream.is_open() || !stream.good())
        return;

    stream << brand;
    stream << ',';
    stream << yearOfRegistration;
    stream << ',';
    owner.serialize(stream);
    stream << "\n";
}

void Car::deserialize(std::ifstream& stream)
{
    if (!stream.is_open() || !stream.good())
        return;

    char* brand = getNextStringEntry(stream);
    setBrand(brand);
    delete[] brand;
    stream.get();
    
    unsigned short registartionYear;
    stream >> registartionYear;
    yearOfRegistration = clamp(registartionYear, 1800, 2024);
    stream.get();
    
    owner.deserialize(stream);
}

void Car::setBrand(const char* brand)
{
    if (brand == nullptr)
    {
        setBrand("Unknown");
        return;
    }

    strncpy(this->brand, brand, 128);
}

char* Car::getNextStringEntry(std::ifstream& stream)
{
    std::streampos currentPos = stream.tellg();
    size_t stringLength = 0;

    while (stream.get() != ',')
        stringLength++;

    stream.seekg(currentPos, std::ios::beg);

    char* readString = new char[stringLength + 1];

    size_t currStringPos = 0;
    while (stream.peek() != ',' && currStringPos < stringLength)
    {
        readString[currStringPos] = stream.get();
        currStringPos++;
    }

    readString[currStringPos] = '\0';
    return readString;
}

unsigned short Car::clamp(unsigned short value, unsigned short min, unsigned short max)
{
    if (value < min)
        return min;

    if (value > max)
        return max;

    return value;
}
```

main.cpp
```cpp
#include <iostream>
#include <fstream>

#include "Car.h"
#include <cstring>

size_t countNewLines(std::ifstream& stream)
{
	size_t linesCount = 0;
	std::streampos currPos = stream.tellg();

	if (!stream.is_open() || !stream.good())
		return linesCount;

	char currChar = '\0';
	while (!stream.eof())
	{
		currChar = stream.get();
		if (currChar == '\n')
			linesCount++;
	}

	stream.clear();
	stream.seekg(currPos, std::ios::beg);

	return linesCount;
}

void writeCarsToTextFile(const char* textFile, Car** cars, size_t carsSize)
{
	if (textFile == nullptr)
		return;

	std::ofstream outStream(textFile, std::ios::out);

	if (!outStream.is_open())
		return;

	for (size_t i = 0; i < carsSize; i++)
	{
		cars[i]->serialize(outStream);
	}
}

Car** readCarsFromTextFile(const char* textFile, size_t& carsSize)
{
	if (textFile == nullptr)
		return nullptr;

	std::ifstream inStream(textFile, std::ios::in);

	if (!inStream.is_open())
		return nullptr;

	carsSize = countNewLines(inStream);
	Car** cars = new Car*[carsSize];

	for (size_t i = 0; i < carsSize && !inStream.eof(); i++)
	{
		cars[i] = new Car(nullptr, Person(nullptr, nullptr, Gender::UNKNOWN, 0), 0); // We need an empty object in order to use deserialize!
		cars[i]->deserialize(inStream);
		inStream.get();
	}

	return cars;
}

void deleteCars(Car** cars, size_t carsSize)
{
	for (size_t i = 0; i < carsSize; i++)
	{
		delete cars[i];
	}

	delete[] cars;
}

void printCar(const Car& car)
{
	std::cout << "Brand: " << car.getBrand() << "\n";
	std::cout << "Year of Registration: " << car.getYearOfRegistration() << "\n";
	std::cout << "Owner Name: ";
	std::cout << car.getOwner().getFirstName() << " " << car.getOwner().getLastName() << "\n";
	std::cout << "Owner gender index: " << car.getOwner().getGender() << "\n";
	std::cout << "Owner year of birth: " << car.getOwner().getYearOfBirth() << "\n";
}

void printCars(const Car** cars, size_t carsSize)
{
	for (size_t i = 0; i < carsSize; i++)
	{
		printCar(*cars[i]);
		std::cout << "\n\n";
	}
}

size_t getOwnersCount(const char* brand, const Car** cars, size_t carsCount)
{
	size_t count = 0;

	if (brand == nullptr)
		return count;

	for (size_t i = 0; i < carsCount; i++)
	{
		if (strcmp(brand, cars[i]->getBrand()) == 0)
			count++;
	}

	return count;
}

const char* getMostOwnedBrand(const Car** cars, size_t carsCount)
{
	const char* mostOwnedBrand = nullptr;
	size_t maxCount = 0;

	for (size_t i = 0; i < carsCount; i++)
	{
		size_t currentBrandCount = getOwnersCount(cars[i]->getBrand(), cars, carsCount);
		
		if (currentBrandCount > maxCount)
		{
			mostOwnedBrand = cars[i]->getBrand();
			maxCount = currentBrandCount;
		}
	}

	return mostOwnedBrand;
}

int main()
{
	Person p1("Ivan", "Ivanov", Gender::MALE, 2002);
	Person p2("Georgi", "Gospodinov", Gender::MALE, 1996);
	Person p3("Emilia", "Stefanova", Gender::FEMALE, 1998);

	constexpr size_t CARS_SIZE = 4;
	Car** cars = new Car*[CARS_SIZE];
	cars[0] = new Car("Audi", p1, 2003);
	cars[1] = new Car("Mercedes", p2, 2020);
	cars[2] = new Car("Nissan", p3, 2004);
	cars[3] = new Car("Audi", p1, 2018);

	writeCarsToTextFile("cars.txt", cars, CARS_SIZE);
	deleteCars(cars, CARS_SIZE);

	size_t newCarsSize = 0;
	Car** newCars = readCarsFromTextFile("cars.txt", newCarsSize);
	
	printCars((const Car**)newCars, newCarsSize);

	const char* mostOwnedCar = getMostOwnedBrand((const Car**)newCars, newCarsSize);
	std::cout << "Most owned car brand: " << mostOwnedCar;

	deleteCars(newCars, newCarsSize);
}
```

</p>
</details>