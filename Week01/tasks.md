### Задача 1 - 1 точка

а) Реализирайте структура, описваща филм (Movie) със следните характеристики:

- Име на филм
- Продължителност в минути
- Жанр (Възможните стойности са описани с множеството { Comedy, Action, Horror, Romantic })
- Рейтинг

б) Създайте масив от филми и имплементирайте следната функционалност:

- Функция, която създава филм по подадени параметри.
  Spoiler: По принцип тази задача се делегира на конструкторите, които ще изучаваме скоро.
- Направете масив от филми и добавете 3 филма по ваш избор.
- Изведете всички филми в масива.
- Изведете топ филма в масива - този с най-много рейтинг.

<details><summary><b>Solution</b></summary> 
<p>

```cpp
#include <iostream>
#include <cstring>

int main()
{
  enum class Genre : short
  {
    COMEDY,
    ACTION,
    HORROR,
    ROMANTIC
  };

  const static char GENRE_STRINGS[][20] = { "Comedy", "Action", "Horror", "Romantic" };

  struct Movie
  {
    char* title;
    unsigned length;
    Genre genre;
    double rating;
  };

  void printMovie(const Movie& movie)
  {
    std::cout << "Title: " << movie.title << ", ";
    std::cout << "Length: " << movie.length << ", ";
    std::cout << "Genre: " << GENRE_STRINGS[(short)movie.genre] << ", ";
    std::cout << "Rating: " << movie.rating << std::endl;
  }

  Movie createMovie(const char* title, unsigned length, Genre genre, double rating)
  {
    char* movieTitle = nullptr;

    if (title == nullptr || strlen(title) == 0)
    {
        movieTitle = new char[8];
        strcpy(movieTitle, "NO NAME");
    }
    else
    {
        movieTitle = new char[strlen(title) + 1];
        strcpy(movieTitle, title);
    }

    return Movie{ movieTitle, length, genre, rating };
    }

    const Movie* getTopRatedMovie(const Movie* movies, size_t size)
    {
    if (size <= 0)
        return nullptr;

    double topRating = movies[0].rating;
    const Movie* topRatedMovie = &movies[0];

    for (int i = 0; i < size; i++)
    {
        const Movie& currMovie = movies[i];

        if (topRating < currMovie.rating)
        {
            topRating = currMovie.rating;
            topRatedMovie = &currMovie;
        }
    }

    return topRatedMovie;
  }

  void deleteMovie(Movie& movie)
  {
    delete[] movie.title;
  }

  int main()
  {
    Movie movies[3] = {
      createMovie("Terminator", 120, Genre::ACTION, 8.90),
      createMovie("Titanic", 240, Genre::ROMANTIC, 9.90),
      createMovie("Fred", 87, Genre::COMEDY, 3.12)
    };

    for (size_t i = 0; i < 3; i++)
    {
      printMovie(movies[i]);
    }

    std::cout << "Top rated movie is: \n";
    const Movie* topRatedMovie = getTopRatedMovie(movies, 3);
    printMovie(*topRatedMovie);

    for (size_t i = 0; i < 3; i++)
    {
      deleteMovie(movies[i]);
    }
  }
}
```

</p>
</details>

### Задача 2 - 0.5 точки

а) Да се напише структура, описваща лаптоп, която съдържа информация за:

- неговата цена
- марка
- големина на екрана
- капацитет на хард диска
- модел видеокарта
- дали съдържа ssd
- операционна система

б) Да се напише функция, която чете въведени от потребителя данни и ги задава като стойности на полетата на даден обект от горния тип.

в) Да се напише функция, която отпечатва информацията за даден обект от горния тип.

г) В магазин се продават лаптопи от горния вид. Да се напише програма, която въвежда информация за наличните 5 лаптопа в магазина и извежда:

- информация за най-скъпия лаптоп в магазина
- средната цена на наличните лаптопи
- лаптопите, които са с операционна система windows

<details><summary><b>Solution</b></summary> 
<p>

```cpp
#include <iostream>
 
enum OperationSystem
{
    NONE = -1,
    WINDOWS,
    LINUX,
    MACOS
};
 
struct Laptop
{
    double price;
    char model[32];
    int sizeOfScreen;
    int capacityOfHDD;
    char videocard[32];
    bool hasSSD;
    OperationSystem operationSystem;
};
 
void initialize(Laptop& l)
{
 
    char os[10];
    std::cout << "Enter laptop specifications:" << std::endl;
    std::cin >> l.price >> l.model >> l.sizeOfScreen >> l.capacityOfHDD >> l.videocard >> l.hasSSD >> os;
    switch (os[0])
    {
    case 'W': l.operationSystem = WINDOWS; break;
    case 'M': l.operationSystem = MACOS; break;
    case 'L': l.operationSystem = LINUX; break;
    default: l.operationSystem = NONE; break;
    }
}
 
void print(const Laptop& l)
{
    std::cout << "Laptop specifications: " << std::endl;
    std::cout << l.price << std::endl;
    std::cout << l.model << std::endl;
    std::cout << l.sizeOfScreen << std::endl;
    std::cout << l.capacityOfHDD << std::endl;
    std::cout << l.videocard << std::endl;
    std::cout << l.hasSSD << std::endl;
    switch (l.operationSystem)
    {
    case WINDOWS: std::cout << "Windows" << std::endl; break;
    case LINUX: std::cout << "Linux" << std::endl; break;
    case MACOS: std::cout << "MACOS" << std::endl; break;
    default: std::cout << "None" << std::endl;
    }
}
 
const size_t AMOUNT_OF_LAPTOPS = 5;
 
void showMostExpensiveLaptop(const Laptop* laptops, const size_t size)
{
    size_t highestPrice = laptops[0].price;
    size_t index = 0;
    for (size_t i = 1; i < AMOUNT_OF_LAPTOPS; i++)
    {
        if (laptops[i].price > highestPrice)
        {
            highestPrice = laptops[i].price;
            index = i;
        }
    }
    print(laptops[index]);
}
 
double averagePrice(const Laptop* laptops, const size_t size)
{
    double sum = 0;
    for (size_t i = 0; i < AMOUNT_OF_LAPTOPS; i++)
    {
        sum += laptops[i].price;
    }
    return sum / AMOUNT_OF_LAPTOPS;
}
 
void printLaptopsWindows(const Laptop* laptops, const size_t size)
{
    for (size_t i = 0; i < AMOUNT_OF_LAPTOPS; i++)
    {
        if (laptops[i].operationSystem == WINDOWS)
        {
            print(laptops[i]);
        }
    }
}

int main()
{
    Laptop laptops[AMOUNT_OF_LAPTOPS];
    for (size_t i = 0; i < AMOUNT_OF_LAPTOPS; i++)
    {
        initialize(laptops[i]);
    }
 
    showMostExpensiveLaptop(laptops, AMOUNT_OF_LAPTOPS);
 
    std::cout << averagePrice(laptops, AMOUNT_OF_LAPTOPS) << std::endl;
 
    printLaptopsWindows(laptops, AMOUNT_OF_LAPTOPS);
 
    return 0;
}
```

</p>
</details>

### Задача 3 - 0.5 точки

а) Да се дефинира структура Planet, определяща планета по име (символен низ), разстояние от слънцето, диаметър и маса (реални числа).

б) Да се дефинират функции, изпълняващи следните действия:

- въвежда данни за планета от клавиатурата;
- извежда данните за планета;
- връща като резултат броя секунди, които са необходими на светлината да достигне от слънцето до планетата (да се приеме,
  че светлината има скорост 299792 km/s и че разстоянието на планетата до слънцето е зададено в километри).
- създава едномерен масив от планети с фиксиран размер и въвежда данните за тях от стандартния вход;
- извежда данните за планетите от масив, подаден на функцията като параметър;

<details><summary><b>Solution</b></summary> 
<p>

```cpp
#include<iostream>
 
struct Planet
{
    char name[20];
    long double distance;
    double mass;
};
 
void enterPlanet(Planet& planet)
{
    std::cin.ignore();
    std::cout << "enter planet name: ";
    std::cin.getline(planet.name, 19);
    std::cout << '\n';
    std::cout << "enter distance from the sun: ";
    std::cin >> planet.distance;
    std::cout << '\n';
    std::cout << "enter mass: ";
    std::cin >> planet.mass;
    std::cout << '\n';
}
 
void printPlanet(Planet& planet)
{
    std::cout << planet.name << " " << planet.distance << " " << planet.mass << std::endl;
}
 
double calculateSeconds(Planet& planet)
{
    return (planet.distance / (double)299792);
}
 
int main()
{
    Planet* planets = nullptr;
    int numberOfPlanets;
    std::cout << "neter number of planets: ";
    std::cin >> numberOfPlanets;
 
    planets = new Planet[numberOfPlanets];
    for (int i = 0; i < numberOfPlanets; ++i)
    {
        enterPlanet(planets[i]);
    }
    double count;
    for (int i = 0; i < numberOfPlanets; ++i)
    {
        printPlanet(planets[i]);
        count = calculateSeconds(planets[i]);
        std::cout << count << std::endl;
    }
 
    delete[] planets;
 
    return 0;
}
```

</p>
</details>

### Задача 4 - 0.25

Да се дефинират структурите: Person, определяща лице по собствено име и фамилия и Client, определяща клиент като лице ,
притежаващо банкова сметка с дадена сума.
Да се дефинират функции, които въвеждат и извеждат данни за лице и клиент.
Да се напише програма, която:

а) въвежда имената и банковите сметки на множество от клиенти, зададено чрез едномерен масив.

б) извежда имената и банковите сметки на клиентите от множеството.

в) намира сумата от задълженията на клиентите от множеството.

<details><summary><b>Solution</b></summary> 
<p>

```cpp
#include<iostream>
 
const int SIZE = 16;
const int SIZE1 = 20;
 
struct Person
{
    char firstname[SIZE];
    char lastname[SIZE];
 
};
 
struct Client
{
    Person name;
    double amount;
};
 
void readPerson(Person& p)
{
    std::cout << "First ime: ";
    std::cin >> p.firstname;
    std::cout << "Last name: ";
    std::cin >> p.lastname;
 
}
 
void printPerson(const Person& p)
{
    std::cout << "First ime: " << p.firstname << std::endl << "Last name: " << p.lastname << std::endl;
}
 
void readClients(Client& c)
{
    std::cout << "ime na klienta" << std::endl;
    readPerson(c.name);
    std::cout << "Suma na klienta: ";
    std::cin >> c.amount;
}
 
void printClient(const Client& c)
{
    std::cout << "ime na klient" << std::endl;
    printPerson(c.name);
    std::cout << "Sume na klienta: " << c.amount << std::endl;
}
 
int main()
{
    std::cout << "Vivedete stoinost za n ot 1 do " << SIZE1 << ": ";
    int n;
    std::cin >> n;
    Client a[SIZE1];
    int i;
    for (int i = 0; i < n; i++)
    {
        readClients(a[i]);
    }
    std::cout << "Klienti na bankata" << std::endl;
    for (int i = 0; i < n; i++)
    {
        printClient(a[i]);
    }
    double s = 0;
    for (int i = 0; i < n; i++)
    {
        if (a[i].amount < 0)
        {
            s += a[i].amount;
        }
    }
    std::cout << "Sumata ot zadylveniqta" << s << std::endl;
    return 0;
}
```

</p>
</details>

### Задача 5 - 0.25 точки

Изкарайте на екрана битовете на един `char` с помощта на `union` и битовите полета.

<details><summary><b>Solution</b></summary> 
<p>

```cpp
#include <iostream>

union
{
 struct {
     unsigned char bit0 : 1;
     unsigned char bit1 : 1;
     unsigned char bit2 : 1;
     unsigned char bit3 : 1;
     unsigned char bit4 : 1;
     unsigned char bit5 : 1;
     unsigned char bit6 : 1;
     unsigned char bit7 : 1;
 } bytes;

 unsigned char symbol;
} charRepr;

int main()
{
 charRepr.symbol = '^'; // 37 -  0b01011110
 
 std::cout << (short)charRepr.bytes.bit7;
 std::cout << (short)charRepr.bytes.bit6;
 std::cout << (short)charRepr.bytes.bit5;
 std::cout << (short)charRepr.bytes.bit4;
 std::cout << (short)charRepr.bytes.bit3;
 std::cout << (short)charRepr.bytes.bit2;
 std::cout << (short)charRepr.bytes.bit1;
 std::cout << (short)charRepr.bytes.bit0;
}
```

</p>
</details>

### Задача 6 - 0.25 точки

Направете структура, която да представя две различни видове дати :

а) кратка дата състояща се от:

* ден - число до 31
* месец - число до около 12

* година - число до около 99

**или**

б) дълга дата състояща се от

* ден - число до 31

* месец низ до 3 символа (Jan, Feb, Mar ...)
* година - число до 4095

> Направете структурата така, че да заема възможно най-малко памет

<details><summary><b>Solution</b></summary> 
<p>

```cpp
#include <iostream>

union Date {
 struct {
     unsigned short day : 5;
     unsigned short month : 4;
     unsigned short year : 7;
 } shortDate;

 struct {
     unsigned day : 5;
     unsigned year : 12;
     char month[3];
 } longDate;
}
```

</p>
</details>

### Задача 7 - 0.25 точки

Да се направи такава функция, която приема обект(който съдържа масив от дробни числа и неговия размер), предикат и друга функция. Трябва за всеки елемент на масива да се провери дали предиката е изпълнен, ако е изпълнен, то за този елемент се прилага подадената функция.

> Бонус: направете функцията такава, че да връща нов обект с елементите, за които е изпълнен предиката и с приложена функцията върху тях. Тоест не трябва да се променя масива намиращ се в подадената структура.

<details><summary><b>Solution</b></summary> 
<p>

```cpp
#include <iostream>

struct DoubleArray
{
 double* arr;
 size_t size;
};

void mapIf(DoubleArray& doubleArr, bool (*pred)(double), double (*func)(double))
{
 for (int i = 0; i < doubleArr.size; i++)
 {
     double* arr = doubleArr.arr;
     if (pred(arr[i]))
     {
         arr[i] = func(arr[i]);
     }
 }
}

bool isBiggerThanFive(double num)
{
 return num > 5.0;
}

double multiplyByTwo(double num)
{
 return num * 2.0;
}

int main()
{
 DoubleArray arr;
 arr.arr = new double[5];
 arr.size = 5;

 arr.arr[0] = 1.22;
 arr.arr[1] = 3.24;
 arr.arr[2] = 7.26;
 arr.arr[3] = 2.35;
 arr.arr[4] = 10.25;

 mapIf(arr, isBiggerThanFive, multiplyByTwo);

 for (int i = 0; i < arr.size; i++)
 {
     std::cout << arr.arr[i] << " ";
 }

 delete[] arr.arr;
}
```

</p>
</details>

### Задача 8 (Важна!) - 1 точка

Да се направи структура, която съдържа информация за един масив състоящ се от 32 битови цели числа. Информацията, която се съдържа трябва да бъде:

- масива
- големина на масива
- число, което показва размера на заделената памет за масива

Да се създадат следните функции:

- createArray, цяло неотрицателно число, което задава размера на първоначално заделената памет в обект на структурата и се заделя такова количество памет за масива в обекта
- append, която приема обект структурата и цяло число. Това цяло число трябва да може да се добави в масива в структурата на следващото свободно място. Ако не може, то трябва да се задели допълнително памет
- find, която приема обект на структурата и предикат и връща първото такова число от масива на обекта, което удовлетворява предиката. Ако не съществува такова, върнете -1 като разултат
- popBack, която приема обект на структурата и премахва последният елемент от масива в структурата и го връща. Ако масивът на обекта ни е празен, то тогава върнете -1
- print, която приема обект на структурата и изкарва на екрана всички елементи на масива намиращ се в структурата
- deleteArray, която приема обект на структурата и освобождава заделената динамична памет в нея

> Може да си измислте и свои функционалности

<details><summary><b>Solution</b></summary> 
<p>

```cpp
#include <iostream>

struct IntArray
{
 int* arr;
 size_t size;
 size_t capacity;
};

IntArray createArray(size_t capacity)
{
 int* arr = new int[capacity];
 size_t cap = capacity;
 size_t size = 0;

 return IntArray{ arr, size, cap };
}

void append(IntArray& intArr, int toAppend)
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

int find(const IntArray& intArr, bool (*pred)(int))
{
 for (size_t i = 0; i < intArr.size; i++)
 {
     if (pred(intArr.arr[i]))
     {
         return intArr.arr[i];
     }
 }

 return -1;
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

bool isPrime(int num)
{
 if (num <= 1)
     return false;

 for (size_t i = 2; i < num / 2; i++)
 {
     if (num % i == 0)
         return false;
 }

 return true;
}

int main()
{
 IntArray arr = createArray(20);

 for (int i = 0; i < 1000; i++)
 {
     append(arr, i + 100);
 }

 print(arr);

 for (int i = 0; i < 990; i++)
 {
     popBack(arr);
 }

 std::cout << "--------- Prime Num ----------\n";
 std::cout << find(arr, isPrime) << "\n";
 std::cout << "------------------------------\n";


 print(arr);

 deleteArray(arr);
}
```

</p>
</details>