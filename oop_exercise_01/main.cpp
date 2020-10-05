/* Ляшун Дмитрий Сергеевич, группа М8О-207Б-19 */
#include <string>
#include "complex.cpp"
using namespace std;
int main() {
    double r1, phi1, r2, phi2;
    string oper;
    cout << "Для работы с комплексными числами в тригонометрической записи введите: " << endl;
    cout << "\t\tadd - сложение двух чисел." << endl;
    cout << "\t\tsub - вычитание двух чисел." << endl;
    cout << "\t\tmul - умножение двух чисел." << endl;
    cout << "\t\tdiv - деление двух чисел." << endl;
    cout << "\t\tequ - проверки на равенство двух чисел." << endl;
    cout << "\t\tconj - найти сопряженное число." << endl;
    cout << "\t\tcomp - сравнение двух чисел по действительной части." << endl;
    cout << "Введите exit - для выхода из программы." << endl;
    while (true) {
    	cout << "> ";
    	cin >> oper;
    	if (oper == "exit") break;
    	cout << "Введите 1-ое число (r1, phi1): ";
        cin >> r1 >> phi1;
        if (oper != "conj") {
            cout << "Введите 2-ое число (r2, phi2): ";
            cin >> r2 >> phi2;
        }
        Complex first(r1, phi1), second(r2, phi2);
        if (oper == "add") { 
            first.write(); 
            cout << " + "; 
            second.write(); 
            cout << " = "; 
            Add(first, second).write(); 
            cout << endl; 
        }
        else if (oper == "sub") { 
            first.write(); 
            cout << " - "; 
            second.write(); 
            cout << " = "; 
            Sub(first, second).write(); 
            cout << endl; 
        }
        else if (oper == "mul") { 
            first.write(); 
            cout << " * "; 
            second.write(); 
            cout << " = "; 
            Mul(first,second).write(); 
            cout << endl; 
        }
        else if (oper == "div") { 
            first.write(); 
            cout << " / "; 
            second.write(); 
            cout << " = "; 
            Div(first,second).write();
            cout << endl; 
        }
        else if (oper == "equ") { 
            first.write(); 
            cout << ( Equ(first, second) ? " = " : " <> "); 
            second.write(); 
            cout << endl; 
        }
        else if (oper == "conj") { 
            cout << "conjugate of "; 
            first.write(); cout  << " is "; 
            Conj(first).write(); 
            cout << endl; 
        }
        else if (oper == "comp") {
            double a1, b1, a2, b2;
            Convert_to_norm(first, a1, b1);
            Convert_to_norm(second, a2, b2);
            cout << "valid part of "; first.write(); cout << " = " << a1;
            if (Equal_valid(first, second)) cout << " EQUAL ";
            else if (Less_valid(first, second)) cout << " LESS ";
            else cout << " MORE ";
            cout << "valid part of "; second.write();  cout << " = " << a2 << endl;
        }
        else cout << "ERROR! WRONG INPUT!" << endl;
    }
}
