# Задача 1 - 2т.
Да се напише програма, която поддържа сцена от много фигури от произволен тип.
 
Всяка фигура трябва да съдържа функционалности за достъпване на информация за
	- Нейното име
	- Нейната дължина
	- Нейната широчина
	- Цвят (3 RGB стойности)
	- Информация за горен ляв, горен десен, долен ляв и долен десен ъгъл на фигурата под формата на 2D координати
          (Ако се разглежда триъгълник или кръг, то това са координатите на квадрата, който ги заобикаля)
	- Метод за отпечатване на фигурата на екрана (да се принтира нейното име)
 
Фигурите, които трябва да се поддържат са:
	- Квадрат
	- Правоъгълник
	- Кръг
	- Триъгълник
 
Всяка фигура се характеризира със стойности в двуизмерното пространство.
(Пример: кръга с радиус и координати за центъра, квадрата с 4 координати и тн.)
 
Сцената трябва да съдържа:
	- Списъка от фигурите за чертане
	- Информация за нейната широчина и височина
	- Начин за отпечатване на нейното съдържание на екрана
 
Използвайте всички научени до момента неща, които са приложими за задачата.
 
Трябва да може сцената да се сериализира във файл и да се десериализира от файла.
Формата на файла е по ваш избор.



### Задача 2  -2т.
За задачата можете да използвате класа string реализиран на семинари. Windows forms е UI framework за лесно създаване на приложения за windows. Той представя лесен начин за създаване на приложения графично и се поддържа от езикци като C#. Приложенията представляват множество от форми в които има контроли. Да се създаде клас, който представя форма. Формата има размер (широчина и дъл- жина), както и име. Всяка форма поддържа колекция от контроли. Всеки контрол има размер и локация във формата. Също така, всеки контрол има функция setDataDialog(); която позволява на потребителя да промени контрола по подходящ начин. Всеки контрол може да променя размерите си. Имаме следните контроли:

Label - Това е просто етикетче. То има текст в него. setDataDialog() променя текста му. CheckBox - Контрол, който има текст и състояние (включен или изключен). setDataDialog() променя дали е включен или изключен по подразбиране. За промяна на текста може да добавите допълнителна функция. Radio Button - Контрол, който има няколко опции, но само една е избрана. setDataDialog() променя избраната опция. Може да добавите допълнителна логика за промяната на опциите. Броят им, веднъж зададен, не се променя. Реализирайте хетерогенен контейнер, който съдържа различните контроли, които вашата форма притежава. Трябва да имате метод за добавяне на контрола към кон- тейнера. Също така трябва да имате метод за променяне на размера на формата както и на всеки от контролите (може да достъпвате контролите по индекс). Напишете функция за промяна на локацията на контролите, като те не трябва да излизат извън формата. Реализирайте метод change(size_t index); който променя контрола на подадения индекс. Промяната става чрез извикване на setDataDialog функцията на съответния контрол.
