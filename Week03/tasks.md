### Задача 1 - 0,5 точка

а) Направете структура Student с име, фак. номер и имейл адрес,брой взети изпити, брой невзети изпити
и средно аритметично от положените изпити през изминалия семестър.

б) Напишете програма, която oтвaря поток за записване в бинарен файл, използвайки данните на предварително
дефинирани променливи от тип Student, след което напишете функция,която прочита данните от бинарния файл
и сортира студентите по успех и връща масив с факултетните номера, където първи е студентът с най-нисък успех.
 
 в) Изведете информацията от върнатия масив в конзолата.

### Задача 2 - 1,5 точка

а)Създайте структурите описващи Животно/Animal и Зоопарк/Zoo.
Структурата Person/Човек - име на човека и отдела, в който работи в зоопарка.
Структурата Animal/Животно трябва да съдържа име на животното и вид на животното(влечуго, бозайник, хищник).

б)Структурата Zoo/Зоопарк трябва да съдържа персонал(масив от Person/Хора), който се грижи за видовете животни
и също така масив от животни. Напишете функция, която прочита n на брой животни от стандартния вход.
Животните се запазват в двоичен файл. Напишете функция, която прочита персонал от стандартния вход.
Персонала се запазват в двоичен файл. Със запазениете данни на животните и персонала, да се създаде зоопарк.
Напишете функция, която запазва данните на зоопарка в нов файл.
Напишете функция, която чете данните на зоопарка от новия файл и принтира данните в конзолата. 

### Задача 3 - 2 точки

Да се създаде такава програма, която описва данни за търговски регистър на спедиторски компании.

За целта си направете две структури, които представляват динамичен масив от цели числа, както и динамичен символен низ.
Динамичният масив представлява такава структура, към която могат да се добавят и махат произволен брой елементи. (Погледнете задачата от първото упражнение)

Дианамичният символен низ е такава структура към която могат да се прибавят произволен брои символи. При този вид структура може да се подаде
цял нов низ, който да се прибави най-отзад на сегашния.

Да се направи функция, която може да чете низ с произволна дължина от конзолата. (Подсказка: използвайте `cin.get()`). Тази фунция трябва да върне обект от динамичен символен низ.

Динамичният масив и динамичният низ трябва да разполагат с функции, които да им позволят да прочетат и запишат информация от/в бинарен файл.

Всяка компания разполага с име, списък с произволен размер състоящ се от идентификационни номера на извършените поръчки, титла, както и низ, който дава информация за статуса на копманията. Статусите представялват символен низ, който се състои от следния формат:
"*<името на спедиторксата компания>*_*<титла>*". Титлата зависи от броя на извършените поръчки.

Титлите се разадават по следния начин:

* < 100 - Junior
* < 10,000 - Mid
* < 100,000 - Senior
* по-голямо или равно от 100,000 - Maxi

Всяка компания трябва да може да бъде записана и прочетена от бинарен файл.

Вашата задача е да създадете масив с произволна дължина от спедиторски компании, които да запишете в бинарен файл
и след това да ги прочетете успешно.

> Бонус: Направете система с която да могат да се прибавят, редактират и премахват спедиторски копмпании. Също така функционалност
> с която да зареждате спедиторски компании от файл, както и да записвате текущото състояние на компаниите във файл. Трябва да може
> да записва данните и в текстов формат. - 1т.

<details><summary><b>Solution</b></summary> 
<p>

```cpp
#include <iostream>
#include <cstring>
#include <fstream>

struct IntArray
{
	int* arr;
	size_t size;
	size_t capacity;
};

IntArray createArray()
{
	IntArray intArray;

	intArray.size = 0;
	intArray.capacity = 8;
	intArray.arr = new int[intArray.capacity];

	return intArray;
}

void appendInt(IntArray& intArr, int toAppend)
{
	if (intArr.size >= intArr.capacity)
	{
		int* oldArr = intArr.arr;
		intArr.capacity *= 2;
		intArr.arr = new int[intArr.capacity];

		for (size_t i = 0; i < intArr.size; i++)
		{
			intArr.arr[i] = oldArr[i];
		}

		delete[] oldArr;
	}

	intArr.arr[intArr.size] = toAppend;
	intArr.size += 1;
}

int popBack(IntArray& intArr)
{
	if (intArr.size == 0)
		return -1;

	int toReturn = intArr.arr[intArr.size - 1];
	intArr.size -= 1;

	return toReturn;
}

void print(const IntArray& intArr)
{
	for (int i = 0; i < intArr.size; i++)
	{
		std::cout << intArr.arr[i] << " ";
	}

	std::cout << std::endl;
}

void deleteArray(IntArray& intArr)
{
	delete[] intArr.arr;
	intArr.size = 0;
	intArr.capacity = 0;
}

struct String
{
	char* str;
	size_t length;
	size_t capacity;
};

String createString(const char* str)
{
	if (str == nullptr)
	{
		return createString("");
	}

	String string;

	string.length = strlen(str);
	string.capacity = string.length + 1;
	string.str = new char[string.capacity];
	strcpy(string.str, str);

	return string;
}

String createString(const String& string)
{
	return createString(string.str);
}

void appendChar(String& string, char toAppend)
{
	if (string.length + 1 >= string.capacity)
	{
		char* oldStr = string.str;
		string.capacity *= 2;
		string.str = new char[string.capacity];
		strcpy(string.str, oldStr);
		delete[] oldStr;
	}

	string.str[string.length] = toAppend;
	string.length += 1;
	string.str[string.length] = '\0';
}

void appendString(String& string, const char* toAppend)
{
	if (toAppend == nullptr)
		return;

	size_t newLength = string.length + strlen(toAppend);
	size_t newCapacity = newLength + 1;

	char* oldStr = string.str;
	string.str = new char[newCapacity];

	strcpy(string.str, oldStr);
	strcat(string.str, toAppend);

	string.length = newLength;
	string.capacity = newCapacity;

	delete[] oldStr;
}

void appendString(String& string, const String& toAppend)
{
	appendString(string, toAppend.str);
}

void deleteString(String& string)
{
	delete[] string.str;
	string.length = 0;
	string.capacity = 0;
}

void printString(const String& string)
{
	std::cout << string.str;
}

String readFromConsole(char delimiter = '\n')
{
	String string = createString(nullptr);
	char currChar = std::cin.get();

	while (currChar != delimiter)
	{
		appendChar(string, currChar);
		currChar = std::cin.get();
	}

	return string;
}

void writeIntArrayToBinary(const IntArray intArr, std::ofstream& stream)
{
	if (!stream.is_open() || !stream.good())
		return;

	stream.write((const char*)&intArr.size, sizeof(intArr.size));
	
	for (size_t i = 0; i < intArr.size; i++)
	{
		stream.write((const char*)&intArr.arr[i], sizeof(int));
	}
}

IntArray readIntArrayFromBinary(std::ifstream& stream)
{
	if (!stream.is_open() || !stream.good())
		return IntArray{ nullptr, 0, 0 };

	size_t size = 0;
	stream.read((char*)&size, sizeof(size_t));

	IntArray intArr = createArray();

	for (int i = 0; i < size; i++)
	{
		if (!stream.good())
		{
			deleteArray(intArr);
			return IntArray{ nullptr, 0, 0 };
		}

		int number = 0;
		stream.read((char*)&number, sizeof(number));
		appendInt(intArr, number);
	}

	return intArr;
}

void writeStringToBinary(const String string, std::ofstream& stream)
{
	if (!stream.is_open() || !stream.good())
		return;

	stream.write(string.str, string.length + 1);
}

String readStringFromBinary(std::ifstream& stream)
{
	if (!stream.is_open() || !stream.good())
		return String{ nullptr, 0, 0 };

	String string = createString(nullptr);

	char currSymbol = '\0';
	stream.read(&currSymbol, sizeof(char));

	while (currSymbol != '\0')
	{
		if (!stream.good())
		{
			deleteString(string);
			return String{ nullptr, 0, 0 };
		}

		appendChar(string, currSymbol);
		stream.read(&currSymbol, sizeof(char));
	}

	return string;
}

enum class Title
{
	JUNIOR,
	MID,
	SENIOR,
	MAXI
};

struct Speditor
{
	String name;
	IntArray orders;
	Title title;
	String stringTitle;
};

void deleteSpeditor(Speditor& speditor)
{
	deleteString(speditor.name);
	deleteString(speditor.stringTitle);
	deleteArray(speditor.orders);
}

String getTitleString(Title title)
{
	switch (title)
	{
	case Title::JUNIOR:
		return createString("Junior");
	case Title::MID:
		return createString("Mid");
	case Title::SENIOR:
		return createString("Senior");
	case Title::MAXI:
		return createString("Maxi");
	default:
		return createString("No Such Title");
	}
}

void fillSpeditor(Speditor& speditor, size_t orders)
{
	for (size_t i = 0; i < orders; i++)
	{
		appendInt(speditor.orders, i);
	}
}

void setTitle(Speditor& speditor)
{
	size_t ordersCount = speditor.orders.size;

	if (speditor.stringTitle.capacity != 0)
		deleteString(speditor.stringTitle);

	speditor.stringTitle = createString(nullptr);

	if (speditor.name.str == nullptr)
		return;

	appendString(speditor.stringTitle, speditor.name);
	appendString(speditor.stringTitle, "_");

	if (ordersCount < 100)
		speditor.title = Title::JUNIOR;
	else if (ordersCount < 10'000)
		speditor.title = Title::MID;
	else if (ordersCount < 100'000)
		speditor.title = Title::SENIOR;
	else
		speditor.title = Title::MAXI;

	String title = getTitleString(speditor.title);
	appendString(speditor.stringTitle, title);

	deleteString(title);
}

void printSpeditor(Speditor& speditor)
{
	std::cout << "Name: ";
	printString(speditor.name);
	std::cout << "\n";

	std::cout << "Orders count: ";
	std::cout << speditor.orders.size << "\n";

	std::cout << "Title: ";
	printString(speditor.stringTitle);
	std::cout << std::endl;
}

void deleteSpeditors(Speditor* speditors, size_t size)
{
	for (size_t i = 0; i < 4; i++)
	{
		deleteSpeditor(speditors[i]);
	}
}

void writeSpeditorToBinary(const Speditor& speditor, std::ofstream& stream)
{
	writeStringToBinary(speditor.name, stream);
	writeIntArrayToBinary(speditor.orders, stream);
}

Speditor readSpeditorFromBinary(std::ifstream& stream)
{
	Speditor speditor;

	speditor.name = readStringFromBinary(stream);
	speditor.orders = readIntArrayFromBinary(stream);
	speditor.stringTitle = createString(nullptr);

	setTitle(speditor);

	return speditor;
}

void writeSpeditorsToBinary(const Speditor* speditors, size_t size, std::ofstream& stream)
{
	stream.write((const char*)&size, sizeof(size_t));

	for (size_t i = 0; i < size; i++)
	{
		writeSpeditorToBinary(speditors[i], stream);
	}
}

Speditor* readSpeditorsFromBinary(std::ifstream& stream, size_t& size)
{
	if (!stream.good() || !stream.is_open())
	{
		size = 0;
		return nullptr;
	}
	
	stream.read((char*)&size, sizeof(size_t));

	Speditor* speditors = new Speditor[size];

	for (size_t i = 0; i < size; i++)
	{
		if (!stream.good())
		{
			deleteSpeditors(speditors, size);
			delete[] speditors;
			size = 0;

			return nullptr;
		}

		speditors[i] = readSpeditorFromBinary(stream);
	}

	return speditors;
}

void printSpeditors(Speditor* speditors, size_t size)
{
	for (size_t i = 0; i < 4; i++)
	{
		printSpeditor(speditors[i]);
		std::cout << "\n";
	}
}

int main()
{
	Speditor speditors[] =
	{
		{
			createString("Econt"),
			createArray(),
			Title::JUNIOR,
			createString(nullptr)
		},
		{
			createString("Speedy"),
			createArray(),
			Title::JUNIOR,
			createString(nullptr)
		},
		{
			createString("DHL"),
			createArray(),
			Title::JUNIOR,
			createString(nullptr)
		},
		{
			createString("UPS"),
			createArray(),
			Title::JUNIOR,
			createString(nullptr)
		}
	};

	fillSpeditor(speditors[0], 50'000);
	setTitle(speditors[0]);

	fillSpeditor(speditors[1], 9'800);
	setTitle(speditors[1]);

	fillSpeditor(speditors[2], 120'000);
	setTitle(speditors[2]);

	fillSpeditor(speditors[3], 200'000);
	setTitle(speditors[3]);

	std::ofstream outStream("speditors.bin", std::ios::out | std::ios::binary);
	writeSpeditorsToBinary(speditors, 4, outStream);
	outStream.close();

	deleteSpeditors(speditors, 4);

	std::ifstream inStream("speditors.bin", std::ios::in | std::ios::binary);
	inStream.clear();

	size_t speditorsSize = 0;
	Speditor* readSpeditors = readSpeditorsFromBinary(inStream, speditorsSize);

	printSpeditors(readSpeditors, speditorsSize);
	deleteSpeditors(readSpeditors, speditorsSize);

	delete[] readSpeditors;
}
```

</p>
</details>