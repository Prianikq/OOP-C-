/* Ляшун Дмитрий Сергеевич, М8О-207Б-19 */
/* Задание: Спроектировать простейший «графический» векторный редактор. Требование к функционалу редактора: создание нового документа; импорт документа из файла; экспорт документа в файл; создание графического примитива; удаление графического примитива; отображение документа на экране; реализовать операцию undo, отменяющую последнее сделанное действие.
Вариант №24: Фигуры - 8-угольник, треугольник, квадрат. */
#include "figures.hpp"
#include "document.hpp"
#include <iostream>
#include <stdio.h>
#include <string>
using namespace std;
int main() {
    Document work;
    Factory adder;
    int oper;
    cout << "Список поддерживаемых команд (для вызова необходимо ввести номер): " << endl;
    cout << "1 - Создание нового документа" << endl;
    cout << "2 - Импорт документа из файла" << endl;
    cout << "3 - Экспорт документа в файл" << endl;
    cout << "4 - Добавление фигуры" << endl;
    cout << "5 - Удаление фигуры" << endl;
    cout << "6 - Печать документа" << endl;
    cout << "7 - Отмена последнего действия" << endl;
    cout << "8 - Выход из программы" << endl;
    while (true) {
        cout << "> ";
        cin >> oper;
        switch (oper) {
            case 1:
            {
                if (!work.Empty()) {
                    cout << "Вы хотите сохранить старый документ в файл перед созданиием нового? (y/n)" << endl << "> ";
                    char ans;
                    cin >> ans;
                    if (ans == 'y') {
                        cout << "Введите имя файла для записи документа > ";
                        string name;
                        cin >> name;
                        FILE* output = fopen(name.c_str(), "w");
                        if (output == NULL) {
                            cout << "Произошла ошибка при открытии файла!" << endl;
                        }
                        else {
                            work.NewDocument(output);
                            cout << "Новый документ успешно создан." << endl;
                            fclose(output);
                        }
                    }
                    else if (ans == 'n') {
                        work.NewDocument(NULL);
                        cout << "Новый документ успешно создан." << endl;
                    }
                    else {
                        cout << "Новый документ успешно создан." << endl;
                    }
                }
                else {
                    cout << "Ошибка! Документ пустой!" << endl;
                }
                break;
            }
            case 2:
            {
                cout << "Введите имя файла для импорта документа > ";
                string name;
                cin >> name;
                FILE* input = fopen(name.c_str(), "r");
                if (input == NULL) {
                    cout << "Произошла ошибка при открытии файла!" << endl;
                }
                else {
                    work.LoadFromFile(input);
                    cout << "Документ успешно загружен из файла." << endl;
                    fclose(input);
                }
                break;
            }
            case 3:
            {
                cout << "Введите имя файла для экспорта документа > ";
                string name;
                cin >> name;
                FILE* output = fopen(name.c_str(), "w");
                if (output == NULL) {
                    cout << "Произошла ошибка при открытии файла!" << endl;
                }
                else {
                    work.SaveInFile(output);
                    cout << "Документ успешно записан в файл." << endl;
                    fclose(output);
                }
                break;
            }
            case 4:
            {
                cout << "Введите тип добавляемой фигуры (1 - Квадрат, 2 - Треугольник, 3 - Восьмиугольник) > ";
                int type;
                cin >> type;
                vector<double> data;
                if (type == 1) {
                    cout << "Введите координаты противоположных вершин квадрата > ";
                    data.resize(4);
                }
                else if (type == 2) {
                    cout << "Введите координаты вершин треугольника > ";
                    data.resize(6);
                }
                else if (type == 3) {
                    cout << "Введите координаты центра восьмиугольника и вектора описанной окружности > ";
                    data.resize(4);
                }
                else {
                    cout << "Ошибка! Введен неправильный тип фигуры!" << endl;
                    break;
                }
                for (int i = 0; i < data.size(); ++i) {
                    cin >> data[i];
                } 
                Figure* figure = adder.Create(type, data);
                cout << "Введите позицию вставки фигуры > ";
                int pos;
                cin >> pos;
                --pos;
                try {
                    work.Insert(figure, pos);
                    cout << "Фигура успешно вставлена." << endl;
                }
                catch (std::exception& e) {
                    cout << e.what() << endl;
                }
                break;
            }
            case 5:
            {
                cout << "Введите позицию удаляемой фигуры > ";
                int pos;
                cin >> pos;
                --pos;
                try {
                    work.Erase(pos);
                    cout << "Фигура успешно удалена." << endl;
                }
                catch (std::exception& e) {
                    cout << e.what() << endl;
                }
                break;
            }
            case 6:
            {
                work.Print();
                break;
            }
            case 7:
            {
                work.Undo();
                cout << "Последнее действие успешно отменено!" << endl;
                break;
            }
            case 8:
                return 0;
            default:
                cout << "Ошибка! Неправильный ввод!" << endl;
        }
    }
}
