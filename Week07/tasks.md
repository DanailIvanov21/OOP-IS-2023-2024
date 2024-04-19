### Задача 1 (2 точки):

Реализирайте клас `Logger`, който може да има само една инстанция.

Задачата на този клас е да логва различна информация в предварително зададен файл със следното име `log.txt`.

Класът трябва да има метод, който да логва определено съобщение, както и да има метод, който да дава информация за това колко съобщения са записани до сега.

Реализирайте следните предефинирани оператори:

* Оператор `<<`, който да изкарва в подаден поток всички записани съобщения от файла.
* Оператор `>>`, който да приема обект от тип `Logger` в лявата си страна и някакъв текст отдясната страна. Неговата задача е да бъде алтернативен начин за логване на съобщение във файла.
* Оператор *(дереференция), който връща последното записано съобщение във файла под формата на символен низ

<details><summary><b>Solution</b></summary> 
<p>

Logger.h
```cpp
#pragma once

#include <iostream>

class Logger
{
public:
	Logger(const Logger&) = delete;
	Logger& operator=(const Logger&) = delete;
	~Logger();

	static Logger& getInstance();

	size_t getLogCount() const;
	const char* operator*() const;
	const char* getFilePath() const;

	void logMessage(const char* logMessage);
	size_t calibrateLogCount();

private:
	Logger(const char* filePath = "log.txt");

	const char* m_FilePath;
	size_t m_LogCount;
};

std::ostream& operator<<(std::ostream& outStream, const Logger& logger);
void operator<<(Logger& logger, const char* logMessage);
```

Logger.cpp
```cpp
#define _CRT_SECURE_NO_WARNINGS

#include "Logger.h"

#include <cstring>
#include <fstream>
#include <stdexcept>

Logger::~Logger()
{
    delete[] m_FilePath;
}

Logger& Logger::getInstance()
{
    static Logger loggerInstance;
    return loggerInstance;
}

void Logger::logMessage(const char* logMessage)
{
    if (logMessage == nullptr)
        return;

    if (strlen(logMessage) >= 2048) // We can also return here!
        throw std::invalid_argument("Log messages must not be longer than 2047 symbols!");

    std::ofstream outStream(m_FilePath, std::ios::out | std::ios::app);

    if (!outStream.is_open())
        throw std::ios_base::failure("Error opening the file for writing!");

    outStream << logMessage << "\n";
    m_LogCount++;
}

size_t Logger::calibrateLogCount()
{
    size_t logCount = 0;

    std::ifstream inFileStream(m_FilePath, std::ios::in);

    if (!inFileStream.is_open())
        throw std::ios_base::failure("Error opening the log file for reading!");

    char currSymbol = '\0';
    while (!inFileStream.eof())
    {
        currSymbol = inFileStream.get();
        if (currSymbol == '\n')
            logCount += 1;
    }

    m_LogCount = logCount;
    return logCount;
}

size_t Logger::getLogCount() const
{
    return m_LogCount;
}

const char* Logger::operator*() const
{
    if (m_LogCount == 0)
        return nullptr;

    size_t newLineCounter = m_LogCount - 1;
    std::ifstream inFileStream(m_FilePath, std::ios::in);

    if (!inFileStream.is_open())
        throw std::ios_base::failure("Error opening the log file for reading!");

    char currSymbol = '\0';
    while (newLineCounter > 0 && !inFileStream.eof())
    {
        currSymbol = inFileStream.get();
        if (currSymbol == '\n')
            newLineCounter -= 1;
    }

    if (inFileStream.eof() || !inFileStream.good())
        return nullptr;

    currSymbol = '\0';

    char buffer[2048];
    inFileStream.getline(buffer, 2048);

    return strcpy(new char[strlen(buffer) + 1], buffer);
}

const char* Logger::getFilePath() const
{
    return m_FilePath;
}

Logger::Logger(const char* filePath)
    : m_FilePath(nullptr), m_LogCount(0)
{
    if (filePath == nullptr)
        throw std::invalid_argument("Invalid file path!");

    m_FilePath = strcpy(new char[strlen(filePath) + 1], filePath);

    std::ofstream(m_FilePath, std::ios::out | std::ios::trunc);
}

std::ostream& operator<<(std::ostream& outStream, const Logger& logger)
{
    std::ifstream inFileStream(logger.getFilePath(), std::ios::in);

    if (!inFileStream.is_open())
        throw std::ios_base::failure("Error opening the file for reading!");

    while (!inFileStream.eof())
        outStream << (char)inFileStream.get();

    return outStream;
}

void operator<<(Logger& logger, const char* logMessage)
{
    logger.logMessage(logMessage);
}
```

</p>
</details>

### Задача 2 (2 точки):

Направете клас `Array`, който няма конструктор по подразбиране и приема естествено число, което ще бъде размера на елементите, които може да съдържа `Array`. Нека тези данни бъдат от тип `double`. Вашата задача да имплементирате следните методи:

* pushBack(...)
* pushFront(...)
* getBack();
* getFront()
* operator[](...)
* at(...)

Основната задача е да използвате на изключения и тяхното прехващане, само там където е нужно за да подобрите използваемостта на вашия клас.

<details><summary><b>Solution</b></summary> 
<p>

Array.h
```cpp
#pragma once

class Array
{
public:
	Array(size_t capacity);
	Array(const Array& other);
	Array(Array&& other) noexcept;
	~Array();

	Array& operator=(const Array& other);
	Array& operator=(Array&& other) noexcept;

	double& operator[](size_t index);
	double operator[](size_t index) const;

	double& at(size_t index);
	double at(size_t index) const;

	void pushBack(double value);
	void pushFront(double value);
	
	double& getBack();
	double& getFront();

	double getBack() const;
	double getFront() const;

	size_t getSize() const;

private:
	double* m_Data;
	size_t m_Size;
	size_t m_Capacity;

	void free();
	void copy(const Array& other);
};
```

Array.cpp
```cpp
#include "Array.h"

#include <stdexcept>

Array::Array(size_t capacity) :
    m_Data(capacity > 0 ? new double[capacity] : nullptr),
    m_Capacity(capacity), m_Size(0)
{
    if (m_Data == nullptr)
        throw std::invalid_argument("A capacity of 0 is invalid!");
}

Array::Array(const Array& other) :
    m_Data(new double[other.m_Capacity]),
    m_Size(other.m_Size), m_Capacity(other.m_Capacity)
{
    for (size_t i = 0; i < other.m_Size && i < other.m_Capacity; i++)
        m_Data[i] = other.m_Data[i];
}

Array::Array(Array&& other) noexcept :
    m_Data(other.m_Data),
    m_Size(other.m_Size), m_Capacity(other.m_Capacity)
{
    other.m_Data = nullptr;
}

Array::~Array()
{
    free();
}

Array& Array::operator=(const Array& other)
{
    if (this != &other)
    {
        free();
        copy(other);
    }

    return *this;
}

Array& Array::operator=(Array&& other) noexcept
{
    m_Data = other.m_Data;
    m_Size = other.m_Size;
    m_Capacity = other.m_Capacity;

    return *this;
}

double& Array::operator[](size_t index)
{
    return m_Data[index];
}

double Array::operator[](size_t index) const
{
    return m_Data[index];
}

double& Array::at(size_t index)
{
    if (index >= m_Size)
        throw std::invalid_argument("Index out of bounds!");

    return m_Data[index];
}

double Array::at(size_t index) const
{
    if (index >= m_Size)
        throw std::invalid_argument("Index out of bounds!");

    return m_Data[index];
}

void Array::pushBack(double value)
{
    if (m_Size >= m_Capacity)
        throw std::invalid_argument("Array is already full!");

    m_Data[m_Size++] = value;
}

void Array::pushFront(double value)
{
    if (m_Size >= m_Capacity)
        throw std::invalid_argument("Array is already full!");

    for (size_t i = 0; i < m_Size; i++)
        m_Data[i + 1] = m_Data[i];

    m_Data[0] = value;
    m_Size++;
}

double& Array::getBack()
{
    if (m_Size == 0)
        throw std::invalid_argument("Array is empty!");

    return m_Data[m_Size - 1];
}

double& Array::getFront()
{
    if (m_Size == 0)
        throw std::invalid_argument("Array is empty!");

    return m_Data[0];
}

double Array::getBack() const
{
    return const_cast<Array*>(this)->getBack();
}

double Array::getFront() const
{
    return const_cast<Array*>(this)->getFront();
}

size_t Array::getSize() const
{
    return m_Size;
}

void Array::copy(const Array& other)
{
    m_Size = other.m_Size;
    m_Capacity = other.m_Capacity;
    m_Data = new double[m_Capacity];

    for (size_t i = 0; i < m_Size && i < m_Capacity; i++)
        m_Data[i] = other.m_Data[i];
}

void Array::free()
{
    delete[] m_Data;
}

```

</p>
</details>

### Задача 3 (2 точки):

Напишете клас `Set` за работа с множество от естествени числа , като елементите му се състоят от цели числа в предварително зададен интервал `[a...b]` `(a<=b)`. Класът трябва да бъде оптимален по памет за стойностите на `a `и `b`.

Съществува конструктор по подразбиране, който задава следните стойности `a = 0`; `b = 255`.

Друг конструктор, който приема и `a` и `b`. Нужно е да се валидира, че `a <= b`;

Предефиниран оператор `^` и `^=` за премахване/добавяне на елемент, както и премахване/добавяне на елементи от друг `Set`

Предефиниран оператор `~`, който премахва всички добавени елементи към множеството и добавя всички елементи, които не са добавени към него.

Предефинирани оператори `|, |=, &, &=`, които следователно правят операциите "Union" и "Intersect на два сета."

Метод, който връща броя на елементите в множеството.

Може да добавите още интересни оператори като `<<, >>, [], <, >, <=, >=, ==, !=` и така нататък, които ще донесат бонус точки :)

<details><summary><b>Solution</b></summary> 
<p>

Set.h
```cpp
#pragma once

#include <cstdint>
#include <iostream>

// lhs is short ofr left hand side
// rhs is short for right hand side

class Set
{
public:
	Set(size_t start = 0, size_t end = 255);
	Set(const Set& other);
	~Set();

	Set& operator=(const Set& other);

	bool operator[](size_t number) const;
	
	size_t getStart() const;
	size_t getEnd() const;

	Set operator~();
	
	Set& operator^=(size_t rhs);
	Set& operator^=(const Set& rhs);

	Set& operator|=(const Set& rhs);
	Set& operator&=(const Set& rhs);

private:
	size_t m_Start;
	size_t m_End;
	size_t m_BucketCount;
	uint8_t* m_Data;

	static const uint8_t s_ElementSize;

	void copy(const Set& other);
};

Set operator^(Set lhs, const Set& rhs);
Set operator^(Set lhs, size_t rhs);

Set operator|(Set lhs, const Set& rhs);
Set operator&(Set lhs, const Set& rhs);

std::ostream& operator<<(std::ostream& outStream, const Set& set);
```

Set.cpp
```cpp
#include "Set.h"

#include <stdexcept>

const uint8_t Set::s_ElementSize = 8;

Set::Set(size_t start, size_t end) :
    m_Start(start),
    m_End(end)
{
    if (m_Start > m_End)
    {
        m_Start ^= m_End;
        m_End ^= m_Start;
        m_Start ^= m_End;
    }

    m_BucketCount = ((m_End - m_Start + 1) / s_ElementSize) + 1;
    m_Data = new uint8_t[m_BucketCount];

    for (size_t i = 0; i < m_BucketCount; i++)
        m_Data[i] = 0;
}

Set::Set(const Set& other) :
    m_Start(other.m_Start),
    m_End(other.m_End),
    m_BucketCount(other.m_BucketCount),
    m_Data(new uint8_t[m_BucketCount])
{
    for (size_t i = 0; i < m_BucketCount; i++)
        m_Data[i] = other.m_Data[i];
}

Set::~Set()
{
    delete[] m_Data;
}

Set& Set::operator=(const Set& other)
{
    if (this != &other)
    {
        delete[] m_Data;
        copy(other);
    }

    return *this;
}

bool Set::operator[](size_t number) const
{
    if (number < m_Start || number > m_End)
        return false;

    size_t numIndex = number - m_Start;
    size_t bucketIndex = numIndex / s_ElementSize;
    size_t internalIndex = numIndex % s_ElementSize;
    return m_Data[bucketIndex] >> internalIndex & 1;
}

size_t Set::getStart() const
{
    return m_Start;
}

size_t Set::getEnd() const
{
    return m_End;
}

Set Set::operator~()
{
    Set inversedSet = *this;

    for (size_t i = 0; i < m_BucketCount; i++)
        inversedSet.m_Data[i] = ~m_Data[i];

    return inversedSet;
}

Set& Set::operator^=(size_t rhs)
{
    if (rhs < m_Start || rhs > m_End)
        return *this;

    size_t numIndex = rhs - m_Start;
    size_t bucketIndex = numIndex / s_ElementSize;
    size_t internalIndex = numIndex % s_ElementSize;
    m_Data[bucketIndex] ^= 1 << internalIndex;

    return *this;
}

Set& Set::operator^=(const Set& rhs)
{
    if (m_Start != rhs.m_Start || m_End != rhs.m_End)
        throw std::invalid_argument("Sets of different values can not ber XORd!");

    for (size_t i = 0; i < m_BucketCount; i++)
        m_Data[i] ^= rhs.m_Data[i];

    return *this;
}

Set& Set::operator|=(const Set& rhs)
{
    if (m_Start != rhs.m_Start || m_End != rhs.m_End)
        throw std::invalid_argument("Sets of different values can not ber ORd!");

    for (size_t i = 0; i < m_BucketCount; i++)
        m_Data[i] |= rhs.m_Data[i];

    return *this;
}

Set& Set::operator&=(const Set& rhs)
{
    if (m_Start != rhs.m_Start || m_End != rhs.m_End)
        throw std::invalid_argument("Sets of different values can not ber ANDd!");

    for (size_t i = 0; i < m_BucketCount; i++)
        m_Data[i] &= rhs.m_Data[i];

    return *this;
}

void Set::copy(const Set& other)
{
    m_Start = other.m_Start;
    m_End = other.m_End;
    m_BucketCount = other.m_BucketCount;
    m_Data = new uint8_t[m_BucketCount];

    for (size_t i = 0; i < m_BucketCount; i++)
        m_Data[i] = other.m_Data[i];
}

Set operator^(Set lhs, const Set& rhs)
{
    return lhs ^= rhs;
}

Set operator^(Set lhs, size_t rhs)
{
    return lhs ^= rhs;
}

Set operator|(Set lhs, const Set& rhs)
{
    return lhs |= rhs;
}

Set operator&(Set lhs, const Set& rhs)
{
    return lhs &= rhs;
}

std::ostream& operator<<(std::ostream& outStream, const Set& set)
{
    for (size_t i = set.getStart(); i < set.getEnd(); i++)
    {
        if (set[i])
        {
            outStream << i;
            outStream << ' ';
        }
    }

    return outStream;
}

```

</p>
</details>
