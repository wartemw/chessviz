# chessviz [![Build Status](https://travis-ci.org/wartemw/chessviz.svg?branch=master)](https://travis-ci.org/wartemw/chessviz)
Приложение принимает на вход запись партии в шахматной нотации и выводит последовательность шахматных досок с 
расположением фигур после каждого хода. Сложность проекта регулируется за счет реализации проверок корректности
входных данных и соблюдения правил игры. Так, в простейшем случае достаточно проверять, что фигуры перемещаются в 
пределах доски и не покидают ее пределы. Более полная реализация должна проверять корректность ходов согласно правилам
игры, например, допустимость рокировки.

#Варианты считавание информации

1) Считывание со стандартного потока ввода. Наиболее простой в реализации, но наименее удобный вариант. Ввод больших 
массивов данных слишком трудоемок, поэтому удобнее хранить их в файле, а для ввода использовать перенаправление.

2) Считывание данных из файла. В этом случае синтаксис запуска приложения выглядит следующим образом:

        chessviz <FILE>
    
    При невозможности открыть файл приложение должно выводить человекопонятное сообщение об ошибке и завершаться с 
ненулевым кодом.

3) Гибридный вариант. Если в командной строке указан путь к файлу, то ходы считываются из него. Иначе приложение 
считывает данные из stdin. Аналогичное поведение можно наблюдать у многих стандартных утилит, например, cat

Синтаксис запуска в этом случае:

    chessviz [FILE]
    
#Функциональность приложения

Существует ряд шахматных нотаций для записи партии. Однако текстовая запись может быть неудобна для анализа. 
Вам необходимо разработать приложение chessviz для визуализации расположения фигур на доске по записи партии в 
алгебраической нотации. Запись ходов может содержать ошибки, ваше приложение должно сообщать о них пользователю.

Формат входных данных
На вход приложение принимает список ходов, разделенных символом перевода строки. Запись хода состоит из таких компонентов:

1) Тип фигуры, выполняющей ход (король, конь и т. д.).
2) Поле, с которого сделан ход.
3) Для тихого хода — дефис (-). Для взятия — буква x.
4) Поле, на которое сделан ход.
5) Если пешка совершила превращение, после целевого поля указывается фигура, которой она стала.
6) Для взятия на проходе — знак e.p. (фр. en passant).
7) Для шаха — знак плюс (+). Для мата — решётка (#).

**Грамматика (pseudo-EBNF):**

    СписокХодов = {ЗаписьХода ПереводСтроки}
    ЗаписьХода = НомерХода. Ход Ход
    Ход = [ТипФигуры] Поле ТипХода Поле [ТипФигуры | 'e.p.' | '+' | '#']
        | Рокировка
    ТипФигуры = 'K' | 'Q' | 'R' | 'B' | 'N'
    Поле = /[a-h][1-8]/
    ТипХода = '-' | 'x'
    Рокировка = '0-0-0' | '0-0'
    
**Пример:**
    
    1. e2-e4 e7-e5
    2. Bf1-c4 Nb8-c6
    3. Qd1-h5 Ng8-f6
    4. Qh5xf7#
    
#Проверки корректности входных данных

При обнаружении ошибки во входных данных приложение прекращает свою работу, выводит человекопонятное сообщение, достаточное для диагностики ошибки, и завершается с ненулевым кодом.

**Easy**

Проверки диапазонов: все поля (начало и конец хода) должны быть в пределах доски.

**Normal**

В дополнение к проверкам из предыдущих пунктов:

1) Обозначения фигур должны соответствовать фактическим (нельзя взять коня с поля, на котором стоял слон).
2) Тип хода должен соответствовать фактическому. Например, если во входных данных записано взятие, а в конечной ячейке 
нет фигуры соперника, то сообщить об ошибке. Взятие на проходе не рассматриваем.

**Hard**

В дополнение к проверкам из предыдущих пунктов:

1) Проверки соблюдения правил движения фигур (слон движется только по диагонали, только конь может перешагивать 
через фигуры и т. д.).
2) Проверка очередности ходов.

**Nightmare**

В дополнение к проверкам из предыдущих пунктов:

1) Проверки допустимости рокировки, см. Рокировка (wiki)
2) Нарушения формата входных данных: отсутствие любого обязательного компонента записи хода или наличие лишних 
элементов, некорректные символы (например, недопустимые обозначения фигур) и т. д.

#Формат выходных данных

После запуска приложение выводит в stdout номер хода, ход и состояние доски после него. Вывод может быть в текстовом
формате и/или html. В случае реализации двух форматов вывода пользователь может выбрать формат с помощью опции 
командной строки. Возможные варианты синтаксиса:

    chessviz [--text|--html]
    chessviz [--output=<text|html>]