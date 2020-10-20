/* Ляшун Дмитрий Сергеевич, М8О-207Б-19 */
#include <vector>
#pragma once
struct Point {
    double x;
    double y;
};
class Figure {
    public :
        Figure(int count)  { points.resize(count);}
        Point Get_center();
        virtual double Get_square() = 0;
        virtual void Output();
        void Input();
        double Get_side();
    private :
        std::vector<Point> points;
};
class Square : public Figure {
    public :
        Square() : Figure(4) {}
        virtual double Get_square() override;
        virtual void Output() override;
};
class Triangle : public Figure {
    public :
       Triangle() : Figure(3) {}
       virtual double Get_square() override;
       virtual void Output() override;
};
class Octagon : public Figure {
    public :
        Octagon() : Figure(8) {}
        virtual double Get_square() override;
        virtual void Output() override;
};


