/* Ляшун Дмитрий Сергеевич, группа М8О-207Б-19 */
#include <cmath>
#include <iostream>
const double EPS = 1e-7;
class Complex {
    public:
        Complex(double r1, double phi1): r(r1), phi(phi1) {}
        double get_r() { return r; }
        double get_phi() { return phi; }
        void write() { std::cout << "(r = " << r << " , phi = " << phi << ")"; }
    private:
        double r;
        double phi;
};
void Convert_to_norm(Complex& arg, double& a, double& b) {
    a = arg.get_r() * cos(arg.get_phi());
    b = arg.get_r() * sin(arg.get_phi());
}
Complex Convert_to_trig(const double a, const double b) {
    double r, phi;
    double cosn = a / sqrt(a*a+b*b);
    double sinn = b / sqrt(a*a+b*b);
    if (abs(cosn) > EPS) {
        r = a / cosn;
    }
    else {
        r = b / sinn;
    }
    phi = acos(cosn);
    return Complex(r, phi);
}
Complex Add(Complex &first, Complex &second) {
    double a1, b1, a2,b2, a3, b3;
    Convert_to_norm(first, a1, b1);
    Convert_to_norm(second, a2, b2);
    a3 = a1 + a2;
    b3 = b1 + b2;
    return Convert_to_trig(a3, b3);
}
Complex Sub(Complex &first, Complex &second) {
    double a1, b1, a2, b2, a3, b3;
    Convert_to_norm(first, a1, b1);
    Convert_to_norm(second, a2, b2);
    a3 = a1 - a2;
    b3 = b1 - b2;
    return Convert_to_trig(a3, b3);
}
Complex Mul(Complex& first, Complex& second) {
    double r = first.get_r() * second.get_r(); // Для комплексных чисел в тригоном. записи умножение можно представить как: сложение углов и произведение радиусов
    double phi = first.get_phi() + second.get_phi();
    return Complex(r, phi);
}
Complex Div(Complex& first, Complex& second) {
    double r = first.get_r() / second.get_r();
    double phi = first.get_phi() - second.get_phi(); // Для комплексных чисел в тригоном. записи деление можно представить как: вычитание углов и деление радиусов
    return Complex(r, phi);
}
bool Equ(Complex& first, Complex& second) {
    return (abs(first.get_r() - second.get_r()) < EPS && abs(first.get_phi() - second.get_phi()) < EPS); // При сравнении double чисел важно учитывать их погрешность
}
Complex Conj(Complex& arg) {
    return Complex(arg.get_r(), -arg.get_phi());
}
bool Equal_valid(Complex& first,  Complex& second) {
    double a1 = first.get_r()*cos(first.get_phi());
    double a2 = second.get_r()*cos(second.get_phi());
    return (abs(a1-a2) < EPS);
}
bool Less_valid(Complex& first, Complex& second) {
    double a1 = first.get_r()*cos(first.get_phi());
    double a2 = second.get_r()*cos(second.get_phi());
    return (a1 < a2);
}
