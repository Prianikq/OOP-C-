/* Ляшун Дмитрий Сергеевич, М8О-207Б-19 */
#pragma once
#include <iostream>
#include <cmath>
#include <vector>
struct Point {
    double x;
    double y;
};
std::ostream& operator<<(std::ostream& os, const Point& p) {
    return os << "( " << p.x << ", " << p.y << " )";
}
bool operator==(const Point& first, const Point& second) {
    return (first.x == second.x && first.y == second.y);
}
class Figure {
    public :
        Figure(int type) : type(type) {}
        virtual void Output() = 0;
        int GetType() {
            return type;
        }
        void SetSquare(const double& sq) {
            square = sq;
        }
        double GetSquare() {
            return square;
        }
        friend bool Equals(Figure* first, Figure* second);
        int type;
        double square;
};
class Square : public Figure {
    public :
        Square(const Point& point1, const Point& point2) : Figure(1), point1(point1), point2(point2) {
            double square = abs(point1.x - point2.x);
            square = pow(square, 2);
            SetSquare(square);
        }
        virtual void Output() override;
        friend bool Equals(Figure* first, Figure* second);
        Point point1, point2;
};
class Triangle : public Figure {
    public :
       Triangle(const Point& point1, const Point& point2, const Point& point3) : Figure(2), point1(point1), point2(point2), point3(point3) {
           double side = sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
           double square = sqrt(3) * pow(side, 2) / 4;
           SetSquare(square);
       }
       virtual void Output() override;
       friend bool Equals(Figure* first, Figure* second);
       Point point1, point2, point3;
};
class Octagon : public Figure {
    public :
        Octagon(const Point& center, const double& vec_x, const double& vec_y) : Figure(3), center(center), vec_x(vec_x), vec_y(vec_y) {
            double side = pow(vec_x, 2) + pow(vec_y, 2);
            double square = 4.0 * sin(acos(-1) / 4.0) * side;
            SetSquare(square);
        }
        virtual void Output() override;
        friend bool Equals(Figure* first, Figure* second);
        Point center;
        double vec_x, vec_y;
};
class Factory {
    public:
        Figure* Create(int type, const std::vector<double>& p) {
            Figure* ans;
            if (type == 1) {
                ans = new Square({p[0], p[1]}, {p[2], p[3]});
            }
            else if (type == 2) {
                ans = new Triangle({p[0], p[1]}, {p[2], p[3]}, {p[4], p[5]});
            }
            else if (type == 3) {
                ans = new Octagon({p[0], p[1]}, p[2], p[3]);
            }
            return ans;
        }
};
void Square::Output() {
    std::cout << "Квадрат: ";
    std::cout << point1 << ", " << point2 << ", S = " << GetSquare() << std::endl;
}
void Triangle::Output() {
    std::cout << "Треугольник: ";
    std::cout << point1 << ", " << point2 << ", " << point3 << ", S = " << GetSquare() << std::endl;
}
void Octagon::Output() {
    std::cout << "Восьмиугольник: ";
    std::cout << center << ", ( " << vec_x << ", " << vec_y << " )" << ", S = " << GetSquare() << std::endl;
}
bool Equals(Figure* first, Figure* second) {
    if (first->type != second->type) {
        return false;
    }
    if (first->type == 1) {
        Square* f = dynamic_cast<Square*>(first);
        Square* s = dynamic_cast<Square*>(second);
        return (f->point1 == s->point1 && f->point2 == s->point2);
    }
    else if (first->type == 2) {
        Triangle* f = dynamic_cast<Triangle*>(first);
        Triangle* s = dynamic_cast<Triangle*>(second);
        return (f->point1 == s->point1 && f->point2 == s->point2 && f->point3 == s->point3);
    }
    else if (first->type == 3) {
        Octagon* f = dynamic_cast<Octagon*>(first);
        Octagon* s = dynamic_cast<Octagon*>(second);
        return (f->center == s->center && f->vec_x == s->vec_x && f->vec_y == s->vec_y);
    }
}
