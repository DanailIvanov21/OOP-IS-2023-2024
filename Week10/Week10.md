### Задача1
Да се дефинира абстрактен клас Device, който поддържа следните данни:

Модел – символен низ
Марка – символен низ
Цена – цяло число
Да се дефинират методи за принтиране на информацията на едно устройство, писане и четене във файл.

Нека класът Phone наследи Device като го надгражда със следните характеристики:

Брой камери - цяло число
SecurityLockType – избор между лицево разпознаване и пръстов отпечатък
Нека класът Laptop също наследи Device като за него има следната информация:

Операционна система – MacOS, Linux, Windows
Дали е с USB портове или с Thunderbolt
Брой портове-цяло число
Нека Phone и Laptop имат свои имплементации на методите за принтиране на информацията, писането и четенето от файл.
Да се реализира клас TechnoShop, който представлява магазин за техника. Нека той има име и съдържа списък от устройства. Да се напишат методи за добавяне и премахване на устройство, премахването да става по подадени модел и марка, записване на информацията на всички устройства във файл и четене на информация за магазин и неговите артикули от файл.
Помислете какво още ще ви е нужно, за да реализирате класа TechnoShop.

### Задача2
Да се реализира йерархия от компютри.

Да се реализира:

Абстрактен клас Computer. В себе си той съдържа:

Мощност на процесора (число тип double)
Модел на видео картата (масив от символи)
Мощност на захранването (цяло число)
Количество RAM памет (цяло число)
Методи за промяна но компонентите на компютъра
Функция, която изписва на стандартния изход какъв тип е компютъра (PC, лаптоп или геймърска конзола)
Функция, която връща с какви периферни устройства разполага компютъра.
Нека перферните устройства са масиви от символи.

Класове PC, Laptop и GamingConsole

PC: разполага с мишка, клавиатура, микрофон и слушалки.
Laptop: разполага с mouse pad, клавиатура и монитор.
GamingConsole: разполага с джойстик и монитор.



