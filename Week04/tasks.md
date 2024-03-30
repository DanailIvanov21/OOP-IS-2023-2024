### Задача 1 - 1т.


Да се създаде клас Alcohol, съдържащ полета за цена и име на алкохола - символен низ, заделен с произволна големина. Да се реализират следните функции:

- конструктор по подразбиране
- конструктор с параметри
- сетъри и гетъри за член-данните
- деструктор, грижещ се за динамичната памет
- метод за отпечатване на стандартния изход
  Бонус - Можете да направите функции за четене и записване в текстови и бинарни файлове.

### Задача 2 - 1т.

Да се реализира клас EventLog, който съдържа списък от събития/Event (описани от един низ,примерно името на събитието).
Класът да предоставя възможност за регистриране на ново събитие и да има възможност да регистрира произволен брой събития.
Да се реализират подходящи селектори, мутатори, конструктори и деструктори за класовете, както и метод addEvent, който регистрира събитие.
Да се реализира и метод print, който отпечатва на екрана всички събития.
Забележка: Не е нужно събитията да могат да бъдат редактирани и премахвани.

### Задача 3 - 2т.

Да се напише клас String, който да има следните характеристики:

- Конструктор по подразбиране, който да създава низ с текст "";
- Конструктор, който приема случаен низ.
- Конструктор, който приема обект от тип String и копира подадения обект
- Конструктор, който приема символ.
- Деструктор, който да се погрижи са освобождаването на всякакъв вид динамична памет(ако има такава)

---

Метод е същото като член-фунция

- Метод, който връща указател към вътрешносъдържащият се низ
- Метод, който позволява за добавяне на един символ, най-отзад на вътрешния низ на обекта
- Метод, който позволява за добавяне на символен низ, най-отзад на вътрешния низ на обекта
- Метод, който приема обект от тип String и прибавя неговото съдържане най-отзад на вътрепния низ
- Метод, който връща дължината на низа в обекта
- Метод, който връща капацитета на низа в обекта
- Метод, който намалява кашпацитета до такъв размер, който да побира само текущия низ и нищо друго.
- Метод, който позволява за добавяне на един символ, най-отпред на вътрешния низ на обекта
- Метод, който позволява за добавяне на символен низ, най-отпред на вътрешния низ на обекта
- Метод, който приема обект от тип String и прибавя неговото съдържане най-отпред на вътрепния низ
- Метод, който намира първото срещане на символ в низа и връща указател към него. Ако няма такъв, то да се връща nullptr.
- Метод, който намира първото срещане на дума в низа и връща указател към началото на думата. Ако не съществува такава дума, то да се върне nullptr.
- Метод, който позволява същото нещо като метода по-горе, но приема обект от тип String.
- Метод, който приема две цели неотрицателни числа и създава нов String, който има за съдържание низа, който се намира между първия и втория индекс. Трябва извикването на този метод винаги да връща валиден обект, независимо от подадените числа.
- Метод, който изчиства съдържанието на оебкта и го прави равно на празен низ("")
- Метод, който позволява да се направи сравненеие с друг обект от тип String и връща булев резултат в зависимост от това дали двата низа в обектите са еднакви.

---

Създайте и една такава фунцкия, която да създава нов обект от тип String от конзолзата с произволна дължина до натискане на бутона Enter.

Демонстрирайте работа с низа в един main файл.

<details><summary><b>Solution</b></summary> 
<p>

Author: Dimitar Donkov

MyString.h
```cpp
#pragma once
#include <cstring>
#include <iostream>

class MyString
{
	size_t capacity = 2;
	size_t size = 0;
	char* data = nullptr;

public:
	MyString();

	MyString(const char* str);

	MyString(char ch);	

	MyString(const MyString& other);

	MyString& operator=(const MyString& other);

	size_t length() const;

	size_t getCapacity() const;

	const char* getData() const;

	void append(char ch);

	void append(const char* str);

	void append(const MyString& other);

	void shrink();

	void addFront(char ch);

	void addFront(const char* str);

	void addFront(const MyString& other);

	const char* findChar(char ch) const;

	const char* findWord(const char* word) const;

	const char* findString(const MyString& other) const;

	MyString substr(size_t start, size_t end) const;

	void clear();

	bool isEqual(const MyString& other) const;

	~MyString();

private:
	void free();

	void copyFrom(const MyString& other);

	void resize(size_t increase=0);
};

```

MyString.cpp
```cpp
#include "MyString.h"

MyString::MyString() : data(new char[capacity]), size(0), capacity(2)
{
	data[0] = '\0';
}

MyString::MyString(const char* str)
{
	if (!str)
	{
		size = 0;
		capacity = 2;
		data = new char[capacity];
		data[0] = '\0';
	}
	else
	{
		size = strlen(str);
		capacity = strlen(str) + 1;
		data = new char[capacity];
		strcpy(data, str);
	}
}

MyString::MyString(char ch)
	: data(new char[2]), size(1), capacity(2)
{
	data[0] = ch;
	data[1] = '\0';
}

MyString::MyString(const MyString& other)
{
	copyFrom(other);
}

MyString& MyString::operator=(const MyString& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

size_t MyString::length() const
{
	return size;
}

size_t MyString::getCapacity() const
{
	return capacity;
}

const char* MyString::getData() const
{
	return data;
}

void MyString::append(char ch)
{
	if (capacity - size <= 1)
		resize();

	data[size++] = ch;
	data[size] = '\0';
}

void MyString::append(const char* str)
{
	if (capacity - size <= strlen(str))
		resize(strlen(str));

	size += strlen(str);
	strcat(data, str);
}

void MyString::append(const MyString& other)
{
	append(other.data);
}

void MyString::shrink()
{
	if (capacity - size == 1)
		return;

	size_t newCapacity = size + 1;
	char* newData = new char[size + 1];
	strcpy(newData, data);
	
	delete[] data;
	data = newData;
	capacity = newCapacity;
}

void MyString::addFront(char ch)
{
	if (capacity - size <= 1)
		resize();

	char* newData = new char[capacity];
	newData[0] = ch;
	newData[1] = '\0';
	strcat(newData, data);

	delete[] data;
	data = newData;
	++size;
}

void MyString::addFront(const char* str)
{
	if (capacity - size <= strlen(str))
		resize(strlen(str));

	char* newData = new char[capacity];
	strcpy(newData, str);
	strcat(data, str);
	size += strlen(str);
}

void MyString::addFront(const MyString& other)
{
	addFront(other.data);
}

const char* MyString::findChar(char ch) const
{
	const char* curr = data;
	while (curr)
	{
		if (*curr == ch)
			return curr;
		++curr;
	}

	return nullptr;
}

const char* MyString::findWord(const char* word) const
{
	if (word == nullptr || *word == '\0')
		return nullptr;

	size_t wordLength = strlen(word);
	const char* curr = data;
	size_t index = 0;

	while (*curr != '\0')
	{
		if (strncmp(curr, word, wordLength) == 0)
			return curr;

		++curr;
	}

	return nullptr;
}

const char* MyString::findString(const MyString& other) const
{
	return findWord(other.data);
}

MyString MyString::substr(size_t start, size_t end) const
{
	if (start >= size || end <= start)
	{
		MyString result;
		return result;
	}

	if (end >= size)
		end = size;

	size_t subLength = end - start;
	char* newData = new char[subLength + 1];
	strncpy(newData, data + start, subLength);
	newData[subLength] = '\0';

	MyString result(newData);

	return result;
}

void MyString::clear()
{
	free();
	capacity = 2;
	size = 0;
	data = new char[capacity];
	data[0] = '\0';
}

bool MyString::isEqual(const MyString& other) const
{
	return strcmp(data, other.data) == 0;
}

MyString::~MyString()
{
	free();
}

void MyString::free()
{
	delete[] data;
	data = nullptr;
}

void MyString::copyFrom(const MyString& other)
{
	size = other.size;
	capacity = other.capacity;
	data = new char[capacity];
	strcpy(data, other.data);
}

void MyString::resize(size_t increase)
{
	size_t newCapacity = (capacity + increase) * 2;
	char* newData = new char[newCapacity];
	strcpy(newData, data);

	delete[] data;
	data = newData;
	capacity = newCapacity;
}

```

main.cpp
```cpp
#include <iostream>
#include "MyString.h"

MyString readFromConsole()
{
	MyString s;
	char ch = std::cin.get();
	while (ch != '\n')
	{
		s.append(ch);
		std::cin.get(ch);
	}

	return s;
}

int main()
{
	MyString s1("Zdravei, martin");
	s1.append(", vsichko e po med i margarin!");

	MyString s2("vsichko");
	const char* word2 = s1.findString(s2);
	if (word2)
		std::cout << word2 << std::endl;
	else
		std::cout << "nullptr\n";

	const char* word1 = s1.findWord("Aasfa");
	if (word1)
	{
		std::cout << word1 << std::endl;
	}
	else
	{
		std::cout << "nullptr\n";
	}
}
```

</p>
</details>
