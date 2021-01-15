/* Ляшун Дмитрий Сергеевич, группа М8О-207Б-19 */
/* Вариант 24, фигуры: 8-угольник, квадрат, треугольник */
#include <iostream>
#include <cmath>
#include <utility>
#include <tuple>

using namespace std;
template<class T> ostream& operator<<(ostream& os, const pair<T, T> out) {
    os << "(" << out.first << ", " << out.second << ")";
    return os;
}
template<class T>  double get_length(const T& x1, const T& y1, const T& x2, const T& y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
template<class T> struct Octagon {
    using type = T;
    pair<T, T> vertex[8];
};
template<class T> struct Triangle {
    using type = T;
    pair<T, T> v1, v2, v3;
};
template<class T> struct Square {
    using type = T;
    pair<T, T> a, b;
};

template<class T> typename enable_if<(sizeof(T::a)>0 && sizeof(T::b)>0), void>::type print(T& f) {
    cout << "Квадрат: ";
    pair<typename T::type, typename T::type> c{f.a.first, f.b.second}, d{f.b.first, f.a.second};
    cout << f.a << ", " << f.b << ", " << c << ", " << d << "." << endl;
}
template<class T> typename enable_if<(sizeof(T::v1)>0 && sizeof(T::v2)>0 && sizeof(T::v3)>0), void>::type print(T& f) {
    cout << "Треугольник: ";
    cout << f.v1 << ", " << f.v2 << ", " << f.v3 << "." << endl;
}
template<class T> typename enable_if<(sizeof(T::vertex)>0), void>::type print(T& f) {
    cout << "Восьмиугольник: ";
    for (int i = 0; i < 8; ++i) {
        cout << f.vertex[i];
        if (i != 7) {
            cout << ", ";
        }
        else {
            cout << "." << endl;
        }
    }
}
template<class T>  typename enable_if<(sizeof(T::a)>0 && sizeof(T::b)>0), typename T::type>::type square(T& f) {
    auto side = get_length(f.a.first, f.b.second, f.b.first, f.a.second);
    return static_cast<typename T::type>(side*side);
}
template<class T> typename enable_if<(sizeof(T::v1)>0 && sizeof(T::v2)>0 && sizeof(T::v3)>0), typename T::type>::type square(T& f) {
    auto side = get_length(f.v1.first, f.v1.second, f.v2.first, f.v2.second);
    return static_cast<typename T::type>(side*side*sqrt(3)/4);
}
template<class T> typename enable_if<(sizeof(T::vertex)>0), typename T::type>::type square(T& f) {
    auto side = get_length(f.vertex[0].first, f.vertex[0].second, f.vertex[1].first, f.vertex[1].second);
    return static_cast<typename T::type>(8*side*side/(4*tan(acos(-1)/8)));
}
template<class T, size_t index> void print_tuple(T& tuple) {
    if constexpr (index < tuple_size<T>::value) {
        auto figure = get<index>(tuple);
        print(figure);
        print_tuple<T, index+1>(tuple);
    }
}
template <class T,size_t index>  double square_tuple(T& tuple){
    auto item = std::get<index>(tuple);
    double value = square(item);
    if constexpr ((index+1) < std::tuple_size<T>::value) {
        return value + square_tuple<T,index+1>(tuple);
    }
    return value;
}
