### Задача 1
Ще създадем система за обработка на поръчки. Идеята е добре позната - клиент
поръчва нещо за вкъщи.
Създайте клас който  описва ресторант. Всеки ресторант има име, което може да направите 
като статичен масив с най- много 25 символа. Също така има и списък с произволна дължина
(която се подава в конструктора) от продукти. Всеки продукт е низ с произволна дължина.
Поддържаме добавяне на продукт. Поддържаме и метод за получаване на поръчка.
Създайте клас, който описва поръчка. Всяка поръчка има име на ресторанта за когото е,
брой продукти и списък с продуктите. Ако в поръчката има продукт, който ресторанта
не предлага, той хвърля грешка. В противен случай връща времето за доставка(време в минути,
вие избирате каква точно да е логиката). 
Създайте клас Foodpandа, който има списък с ресторанти(отново с произволна дължина,
която се задава в конструктора) и който прочита поръчки от конзолата.
Класът намира за кой ресторант е поръчката, ако има такъв, в противен случай изписва,
че поръчката е невалидна понеже такъв ресторант не съществува. Ако ресторантът
съществува му я изпраща. Ако той хвърли грешка Foodpanda я хваща и съобщава, че даденият
ресторант не предлага някой продукт от тези в поръчката.
За всеки клас реализирайте нужните конструктори. Реализирайте move семантики.

### Бонус:
1. Направете метод за добавяне на нови продукти в ресторанта.
2. Направете метод за добавяне на нови ресторанти в Foodpanda.
