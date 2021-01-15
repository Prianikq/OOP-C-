/* Ляшун Дмитрий Сергеевич, группа М8О-207Б-19 */
/* Вариант 24, фигуры: 8-угольник, квадрат, треугольник */
#include "figure.hpp"
int main() {
    Square<int> s1{{0, 0}, {1, 1}};
    Square<double> s2{{0, 0}, {4.5, 4.5}};
    Triangle<double> t1{{1, 1}, {3, 1}, {2, 2.73205}};
    Octagon<int> o1{{{1, 0}, {1, 3}, {2, 6}, {5, 6}, {6, 3}, {6, 0}, {5, -3}, {2, -3}}};
    Octagon<double> o2{{{0.5, 0}, {1.5, 0}, {2, -1}, {2, -2}, {1.5, -3}, {0.5, -3}, {0, -2}, {0, -1}}};
    tuple<decltype(s1), decltype(s2), decltype(t1), decltype(o1), decltype(o2)> tuple {s1, s2, t1, o1, o2};
    cout << "Введенные фигуры: " << endl;
    print_tuple<decltype(tuple), 0>(tuple);
    cout << "Общая площадь фигур: " << square_tuple<decltype(tuple), 0>(tuple) << endl;
    return 0;
}
