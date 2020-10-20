/* Ляшун Дмитрий Сергеевич, М8О-207Б-19 */
#include "figures.hpp"
#include <iostream>
#include <vector>
using namespace std;
int main() {
    cout << "Введите номер необходимой операции: " << endl;
    cout << "\t1 - Добавить новую фигуру в массив. " << endl;
    cout << "\t2 - Вывести координаты фигур. " << endl;
    cout << "\t3 - Вывести геометрические центры фигур. " << endl;
    cout << "\t4 - Вывести площади фигур. " << endl;
    cout << "\t5 - Вывести общую площадь фигур. " << endl;
    cout << "\t6 - Удалить фигуру из массива." << endl;
    cout << "\t0 - Выход из программы." << endl;
    vector<Figure*> figures;
    while (true) {
        int oper;
        cout << "> ";
        cin >> oper;
        switch (oper) {
            case 0:
                return 0;
            case 1: {
                cout << "Введите тип фигуры (1 - квадрат, 2 - треугольник, 3 - восьмиугольник) и координаты её вершин: ";
                int type;
                cin >> type;
                switch (type) {
                    case 1: {
                        Square* sq = new Square;
                        sq->Input();
                        figures.push_back(sq);
                        break;
                    }
                    case 2: {
                        Triangle* tr = new Triangle;
                        tr->Input();
                        figures.push_back(tr);
                        break;
                    }
                    case 3: {
                        Octagon* oc = new Octagon;
                        oc->Input();
                        figures.push_back(oc);
                        break;
                    }
                    default:
                        cout << "Ошибка! Указан некорректный тип фигуры!" << endl;
                        break;
                }
                break;
            }
            case 2: {
                for (int i = 0; i < figures.size(); ++i) {
                    cout << "[" << i+1 << "] ";
                    figures[i]->Output();
                    cout << endl;
                }
                break;
            }
            case 3: {
                for (int i = 0; i < figures.size(); ++i) {
                    Point center = figures[i]->Get_center();
                    cout << "[" << i+1 << "]: " << "( " << center.x << " , " << center.y << " ) ." << endl;
                }
                break;
            }
            case 4: {
                for (int i = 0; i < figures.size(); ++i) {
                    cout << "[" << i+1 << "] S = " << figures[i]->Get_square() << endl;
                }
                break;
            }
            case 5: {
                double all_square = 0;
                for (int i = 0; i < figures.size(); ++i) {
                    all_square += figures[i]->Get_square();
                }
                cout << "Общая площадь фигур S = " << all_square << endl;
                break;
            }
            case 6: {
                cout << "Введите номер удаляемой фигуры: ";
                int number;
                cin >> number;
                --number;
                if (0 <= number && number < figures.size()) {
                    figures.erase(figures.begin() + number);
                    cout << "Фигура №" << number+1 << " удалена. " << endl;
                }
                else {
                    cout << "Ошибка! Указан некорректный номер фигуры!" << endl;
                }
                break;
            }
            default:
                cout << "Ошибка! Указан некорректный номер опреации!" << endl;
                break;
        }
    }
}
