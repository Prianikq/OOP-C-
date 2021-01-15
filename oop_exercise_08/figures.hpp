/* Ляшун Дмитрий Сергеевич, М8О-207Б-19 */
#pragma once
#include <iostream>
#include <cmath>
#include <vector>
template<class T>
struct Point {
    T x;
    T y;
};
template<class T>
std::ostream& operator<<(std::ostream& os, const Point<T>& p) {
    return os << "( " << p.x << ", " << p.y << " )";
}
template<class T>
bool operator==(const Point<T> first, const Point<T> second) {
    return (first.x == second.x && first.y == second.y);
}
template<class T>
class Figure {
    public :
        virtual void OutputInConsole() = 0;
        virtual void OutputInFile(FILE* file) = 0;
        T GetSquare();
        void SetSquare(T sq);
    private :
        T square;
};
template<class T>
T Figure<T>::GetSquare() {
    return square;
}
template<class T>
void Figure<T>::SetSquare(T sq) {
    square = sq;
}
template<class T>
class Square : public Figure<T> {
    public :
        Square(const Point<T>& point1, const Point<T>& point2) :  point1(point1), point2(point2) {
            T square = abs(point1.x - point2.x);
            square = pow(square, 2);
            this->SetSquare(square);
        }
        virtual void OutputInConsole() override;
        virtual void OutputInFile(FILE* file) override;
    private:
        Point<T> point1, point2;
};
template<class T>
class Triangle : public Figure<T> {
    public :
       Triangle(const Point<T> point1, const Point<T> point2, const Point<T> point3) : point1(point1), point2(point2), point3(point3) {
           T side = sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
           T square = sqrt(3) * pow(side, 2) / 4;
           this->SetSquare(square);
       }
       virtual void OutputInConsole() override;
       virtual void OutputInFile(FILE* file) override;
    private:
       Point<T> point1, point2, point3;
};
template<class T>
class Octagon : public Figure<T> {
    public :
        Octagon(const Point<T>& center, const T vec_x, const T vec_y) : center(center), vec_x(vec_x), vec_y(vec_y) {
            T side = pow(vec_x, 2) + pow(vec_y, 2);
            T square = 4.0 * sin(acos(-1) / 4.0) * side;
            this->SetSquare(square);
        }
        virtual void OutputInConsole() override;
        virtual void OutputInFile(FILE* file) override;
    private :
        Point<T> center;
        T vec_x, vec_y;
};
template<class T>
void Square<T>::OutputInFile(FILE* file) {
    fprintf(file, "Квадрат: ");
    fprintf(file, "%lf ", point1.x);
    fprintf(file, "%lf ", point1.y);
    fprintf(file, "%lf ", point2.x);
    fprintf(file, "%lf\n", point2.y);
}
template<class T>
void Triangle<T>::OutputInFile(FILE* file) {
    fprintf(file, "Треугольник: ");
    fprintf(file, "%lf ", point1.x);
    fprintf(file, "%lf ", point1.y);
    fprintf(file, "%lf ", point2.x);
    fprintf(file, "%lf ", point2.y);
    fprintf(file, "%lf ", point3.x);
    fprintf(file, "%lf\n", point3.y);
}
template<class T>
void Octagon<T>::OutputInFile(FILE* file) {
    fprintf(file, "Восьмиугольник: ");
    fprintf(file, "%lf ", center.x);
    fprintf(file, "%lf ", center.y);
    fprintf(file, "%lf ", vec_x);
    fprintf(file, "%lf\n", vec_y);
}
template<class T>
void Square<T>::OutputInConsole() {
    std::cout << "Квадрат: ";
    std::cout << point1 << ", " << point2 << ", S = " << Figure<T>::GetSquare() << std::endl;
}
template<class T>
void Triangle<T>::OutputInConsole() {
    std::cout << "Треугольник: ";
    std::cout << point1 << ", " << point2 << ", " << point3 << ", S = " << Figure<T>::GetSquare() << std::endl;
}
template<class T>
void Octagon<T>::OutputInConsole() {
    std::cout << "Восьмиугольник: ";
    std::cout << center << ", ( " << vec_x << ", " << vec_y << " )" << ", S = " << Figure<T>::GetSquare() << std::endl;
}
