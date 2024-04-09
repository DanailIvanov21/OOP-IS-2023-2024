#pragma once

#include <iostream>

class String
{
public:
	String();
	String(char symbol);
	String(const char* string);
	String(const String& other);
	~String();

	String& operator= (const String& other);

	String& operator+= (const String& other);
	bool operator== (const String& other);
	bool operator!= (const String& other);

	char& operator[] (size_t index);
	char operator[] (size_t index) const;

	char& at(size_t index);
	char at(size_t index) const;

	char& back();
	char& front();
	char back() const;
	char front() const;

	const char* c_str() const;
	size_t size() const;
	size_t length() const;
	size_t capacity() const;
	bool empty() const;

	String& append(const String& other);

	void clear();
	void pushBack(char symbol);

private:
	char* m_Str;
	size_t m_Size;
	size_t m_Capacity;

	void resize(const size_t& newSize);
	size_t calculateCapacity(const size_t& num);

	void freeMemory();
	void copy(const String& other);
};

std::istream& getLine(std::istream& in, String& str, char delimiter = '\n');
std::ostream& operator<< (std::ostream& out, const String& str);
std::istream& operator>>(std::istream& in, String& str);
String operator+ (const String& lhs, const String& rhs);
