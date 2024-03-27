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
