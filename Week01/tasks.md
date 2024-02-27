### Задача 1

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

### Задача 2

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

### Задача 3

а) Да се дефинира структура Planet, определяща планета по име (символен низ), разстояние от слънцето, диаметър и маса (реални числа).

б) Да се дефинират функции, изпълняващи следните действия:

- въвежда данни за планета от клавиатурата;
- извежда данните за планета;
- връща като резултат броя секунди, които са необходими на светлината да достигне от слънцето до планетата (да се приеме,
  че светлината има скорост 299792 km/s и че разстоянието на планетата до слънцето е зададено в километри).
- създава едномерен масив от планети с фиксиран размер и въвежда данните за тях от стандартния вход;
- извежда данните за планетите от масив, подаден на функцията като параметър;

### Задача 4

Да се дефинират структурите: Person, определяща лице по собствено име и фамилия и Client, определяща клиент като лице ,
притежаващо банкова сметка с дадена сума.
Да се дефинират функции, които въвеждат и извеждат данни за лице и клиент.
Да се напише програма, която:

а) въвежда имената и банковите сметки на множество от клиенти, зададено чрез едномерен масив.

б) извежда имената и банковите сметки на клиентите от множеството.

в) намира сумата от задълженията на клиентите от множеството.


### Задача 5

Изкарайте на екрана битовете на един `char` с помощта на `union` и битовите полета.


### Задача 6

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

### Задача 7

Да се направи такава функция, която приема обект(който съдържа масив от дробни числа и неговия размер), предикат и друга функция. Трябва за всеки елемент на масива да се провери дали предиката е изпълнен, ако е изпълнен, то за този елемент се прилага подадената функция.

> Бонус: направете функцията такава, че да връща нов обект с елементите, за които е изпълнен предиката и с приложена функцията върху тях. Тоест не трябва да се променя масива намиращ се в подадената структура.

### Задача 8 (Важна!)

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