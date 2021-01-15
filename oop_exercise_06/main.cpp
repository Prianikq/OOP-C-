/* Ляшун Дмитрий Сергеевич, группа М8О-207Б-19 */
/* ЛР №6, Вариант №24: Фигура: 8-угольник, Контейнер: очередь, Контейнер аллокатора: очередь*/
/* Назначение программы: работа с коллекцией восьмиугольников: добавление и удаление фигур, их печать, подсчет количества фигур с площадью меньше заданной. */
#include "queue.hpp"
#include "octagon.hpp"
#include <algorithm>
using namespace std;
const size_t ALLOCATOR_SIZE = 10000;
auto main() -> int {
    Myqueue<Octagon<int>, my_allocator<Octagon<int>, ALLOCATOR_SIZE> > queue;
    cout << "Поддерживаемые операции (для вызова необходимо ввести ее номер): " << endl;
    cout << "1 - Добавить восьмиугольник в коллекцию. " << endl;
    cout << "2 - Удалить восьмиугольник из коллекции. " << endl;
    cout << "3 - Вывод всех восьмиугольников в коллекции. " << endl;
    cout << "4 - Выход из программы. " << endl;
    while (true) {
        int choice;
        cout << "> ";
        cin >> choice;
        if (choice == 1) {
            cout << "Введите восьмиугольник (коорд. центра и вектор радиуса описан. окружн.): ";
            pair<int,int> vx, vec;
            cin >> vx.first >> vx.second >> vec.first >> vec.second;
            Octagon<int> oct(vx, vec);
            cout << "Введите позицию добавления: ";
            int pos;
            cin >> pos;
            try {
                --pos;
                auto iter = queue.Begin();
                while (pos != 0) {
                    ++iter;
                    --pos;
                }
                queue.Insert(iter, oct);
                cout << "Восьмиугольник добавлен в коллекцию." << endl;
            }
            catch (std::exception& exception) {
                cout << exception.what() << endl;
            }
        }
        else if (choice == 2) {
            cout << "Введите позицию удаления: ";
            int pos;
            cin >> pos;
            try {
                --pos;
                auto iter = queue.Begin();
                while (pos != 0) {
                    ++iter;
                    --pos;
                }
                queue.Erase(iter);
                cout << "Восьмиугольник удален из коллекции." << endl;
            }
            catch (std::exception& exception) {
                cout << exception.what() << endl;
            }
        }
        else if (choice == 3) {
        	int count = 0;
            for_each(queue.Begin(), 
                     queue.End(), 
                     [&count](Octagon<int> & iter) {
                        ++count;
                        cout << "Восьмиугольник №" << count << " : ";
                        iter.print();
                     });
        }
        else if (choice == 4) {
            break;
        }
        else {
            cout << "Ошибка! Неправильный ввод!" << endl;
        }
    }
}
