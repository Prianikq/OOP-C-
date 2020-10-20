/* Ляшун Дмитрий Сергеевич, группа М8О-207Б-19 */
#include "unsignedll.hpp"
#include <string>
#include <iostream>
using namespace std;
int main() {
    cout << "Введите выражения в формате: <число1> <оператор> <число2> " << endl;
    cout << "Поддерживаемые операторы: +, -, *, /, %, >, <, ==, != " << endl;
    while (true)
    {
        string operate;
        UnsignedLL number1, number2;
        cout << "> ";
        cin >> number1 >> operate >> number2;
        if (operate == "+") {
            cout << "Результат: " << number1 + number2 << endl;
        }
        else if (operate == "-") {
            cout << "Результат: " << number1 - number2 << endl;
        }
        else if (operate == "*") {
            cout << "Результат: " << number1 * number2 << endl;
        }
        else if (operate == "/") {
            cout << "Результат: " << number1 / number2 << endl;
        }
        else if (operate == "%") {
            cout << "Результат: " << number1 % number2 << endl;
        }
        else if (operate == ">") {
            cout << "Результат: " << (number1 > number2? "Истина" : "Ложь") << endl;
        }
        else if (operate == "<") {
            cout << "Результат: " << (number1 < number2? "Истина" : "Ложь") << endl;
        }
        else if (operate == "==") {
            cout << "Результат: " << (number1 == number2? "Истина" : "Ложь") << endl;
        }
        else if (operate == "!=") {
            cout << "Результат: " << (number1 != number2? "Истина" : "Ложь") << endl;
        }
        else {
            cout << "Ошибка! Неправильный ввод!" << endl;
        }
    }
}
