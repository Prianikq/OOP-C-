/* Ляшун Дмитрий Сергеевич, М8О-207Б-19 */
#include "figures.hpp"
#include <iostream>
#include <cmath>
Point Figure::Get_center() {
    Point answer{0, 0};
    for (int i = 0; i < points.size(); ++i)
    {
        answer.x += points[i].x;
        answer.y += points[i].y;
    }
    answer.x /= points.size();
    answer.y /= points.size();
    return answer;
}
double Figure::Get_side() {
    double v_x = points[1].x - points[0].x;
    double v_y = points[1].y - points[0].y;
    return sqrt(v_x*v_x+v_y*v_y);
}
void Figure::Input() {
    for (int i = 0; i < points.size(); ++i) {
        std::cin >> points[i].x >> points[i].y;
    }
}
void Figure::Output() {
    for (int i = 0; i < points.size(); ++i) {
        std::cout << "( " << points[i].x << " , " << points[i].y << " )";
        if (i != points.size()-1)  {
            std::cout << ", ";
        }
    }
    std::cout << ".";
}
void Square::Output() {
    std::cout << "Квадрат: ";
    Figure::Output();
}
double Square::Get_square() {
    return pow(Get_side(), 2);
}
double Triangle::Get_square() {
    return pow(Get_side(), 2)*sqrt(3)/4;
}
void Triangle::Output() {
    std::cout << "Треугольник: ";
    Figure::Output();
}
double Octagon::Get_square() {
    return 8*pow(Get_side(), 2) / (4*tan(acos(-1)/8));
}
void Octagon::Output() {
    std::cout << "Восьмиугольник: ";
    Figure::Output();
}
