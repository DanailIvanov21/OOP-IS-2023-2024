#define _CRT_SECURE_NO_WARNINGS

#include "String.h"

#include <cstring>
#include <stdexcept>

String::String()
{
	m_Size = 0;
	m_Capacity = 2;
	m_Str = new char[m_Capacity];
	m_Str[0] = '\0';
}

String::String(const char* string)
{
	if (string == nullptr)
		string = "";

	m_Size = strlen(string);
	m_Capacity = calculateCapacity(m_Size);
	m_Str = new char[m_Capacity];
	strcpy(m_Str, string);
}

String::String(char symbol)
{
	m_Size = 1;
	m_Capacity = 4;
	m_Str = new char[m_Capacity];
	m_Str[0] = symbol;
	m_Str[1] = '\0';
}

String::String(const String& other)
{
	copy(other);
}

String::~String()
{
	freeMemory();
}

String& String::operator=(const String& other)
{
	if (this != &other)
	{
		freeMemory();
		copy(other);
	}

	return *this;
}

String& String::operator+=(const String& other)
{
	return this->append(other);
}

bool String::operator==(const String& other)
{
	if (this == &other)
		return true;

	return strcmp(m_Str, other.m_Str) == 0;
}

bool String::operator!=(const String& other)
{
	return !(*this == other);
}

char& String::operator[](size_t index)
{
	return m_Str[index];
}

char String::operator[](size_t index) const
{
	return m_Str[index];
}

char& String::at(size_t index)
{
	if (index < 0 || index >= m_Size)
		throw std::out_of_range("Index out of range exception!");

	return m_Str[index];
}

char String::at(size_t index) const
{
	if (index < 0 || index >= m_Size)
		throw std::out_of_range("Index out of range exception!");

	return m_Str[index];
}

char& String::back()
{
	if (m_Size == 0)
		throw std::invalid_argument("The string is empty!");

	return m_Str[m_Size - 1];
}

char& String::front()
{
	if (m_Size == 0)
		throw std::invalid_argument("The string is empty!");

	return m_Str[0];
}

char String::back() const
{
	if (m_Size == 0)
		throw std::invalid_argument("The string is empty!");

	return m_Str[m_Size - 1];
}

char String::front() const
{
	if (m_Size == 0)
		throw std::invalid_argument("The string is empty!");

	return m_Str[0];
}

const char* String::c_str() const
{
	return m_Str;
}

size_t String::size() const
{
	return m_Size;
}

size_t String::length() const
{
	return m_Size;
}

size_t String::capacity() const
{
	return m_Capacity;
}

bool String::empty() const
{
	return m_Size == 0;
}

String& String::append(const String& other)
{
	const char* otherStr = other.c_str();

	if (this != &other)
	{
		while (*otherStr != '\0')
			pushBack(*otherStr);
	}
	else
	{
		size_t oldSize = m_Size;
		for (size_t i = 0; i < oldSize; i++)
			pushBack(otherStr[i]);
	}

	return *this;
}

void String::clear()
{
	freeMemory();
	copy("");
}

void String::pushBack(char symbol)
{
	if (m_Size + 1 >= m_Capacity)
		resize(m_Capacity);

	m_Str[m_Size++] = symbol;
	m_Str[m_Size] = '\0';
}

size_t String::calculateCapacity(const size_t& newSize)
{
	if (newSize <= 2)
		return 4;

	if (newSize <= 8)
		return 16;

	if (newSize <= 16)
		return 32;

	return ((newSize / 16) + 1) * 16;
}

void String::resize(const size_t& newSize)
{
	size_t newCapacity = calculateCapacity(newSize);
	char* newStr = new char[newCapacity];

	size_t i;
	for (i = 0; m_Str[i] != '\0' && i < newCapacity - 1; ++i)
	{
		newStr[i] = m_Str[i];
	}

	newStr[i] = '\0';

	delete[] m_Str;

	m_Str = newStr;
	m_Capacity = newCapacity;
	m_Size = strlen(newStr);
}

void String::freeMemory()
{
	delete[] m_Str;
}

void String::copy(const String& other)
{
	m_Size = other.m_Size;
	m_Capacity = other.m_Capacity;
	m_Str = new char[m_Capacity];
	strcpy(m_Str, other.m_Str);
}

std::ostream& operator<<(std::ostream& out, const String& str)
{
	return out << str.c_str();
}

std::istream& operator>>(std::istream& in, String& str)
{
	str = String();
	char c;

	do
	{
		c = in.get();
		if (c != '\n' && c != ' ')
			str.pushBack(c);
		else
			break;
	} while (true);

	return in;
}

std::istream& getLine(std::istream& in, String& str, char delimiter)
{
	str = String();
	char c;

	do
	{
		c = in.get();
		if (c == delimiter)
			break;

		str.pushBack(c);
	} while (true);

	return in;
}

String operator+(const String& lhs, const String& rhs)
{
	String newStr = lhs;
	return newStr.append(rhs);
}