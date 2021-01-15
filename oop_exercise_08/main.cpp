/* Ляшун Дмитрий Сергеевич, М8О-207Б-19 */
/* Задание: Создать приложение, которое будет считывать из стандартного ввода данные фигур, согласно варианту задания, выводить их характеристики на экран и записывать в файл. Фигуры могут задаваться как своими вершинами, так и другими характеристиками (например, координата центра, количество точек и радиус). 
Вариант №24: Фигуры: 8-угольник, треугольник, квадрат. */
#include "figures.hpp"
#include "pubsub.hpp"
#include <iostream>
#include <stdlib.h>
#include <thread>
#include <memory>
#include <functional>
using workType = double;
using pointerType = std::shared_ptr<Figure<workType > >;
PubSubMQ<std::vector<pointerType> > messages;
FILE* file;
int fileCount = 0;
const std::string FOLDER = "files/";
void ThreadFunc() {
    using functionType = std::function<void(pointerType)>;
    functionType OutputInConsole = [](pointerType fg) {
        fg->OutputInConsole();
    };
    functionType OutputInFile = [](pointerType fg) {
        fg->OutputInFile(file);
    };
    std::vector<functionType> funcs({OutputInConsole, OutputInFile});
    bool awake = true;
    while (awake) {
        if (!messages.Empty()) {
            std::vector<pointerType> mes = messages.Front();
            if (mes.empty()) {
                awake = false;
                break;
            }
            file = fopen((FOLDER+std::to_string(fileCount)+std::string(".txt")).c_str(), "w");
            if (file == NULL) {
                std::cout << "Ошибка создания файла!" << std::endl;
                return;
            }
            ++fileCount;
            for (int i = 0; i < mes.size(); ++i) {
                for (auto func : funcs) {
                    func(mes[i]);
                }
            }
            fclose(file);
            messages.Pop();
        }
    }
}
const int OCTAGON_ID = 1;
const int TRIANGLE_ID = 2;
const int SQUARE_ID = 3;
int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Ошибка! При запуске программы необходимо указать размер буфера!" << std::endl;
        return -1;
    }
    size_t sizeBuffer;
    try {
        sizeBuffer = stoi(std::string(argv[1]));
    } 
    catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        return -1;
    }
    std::thread thr(ThreadFunc);
    std::vector<pointerType> figures;
    unsigned int type;
    std::cout << "Введите номер типа добавляемой фигуры (1 - Восьмиугольник, 2 - Треугольник, 3 - Квадрат, 0 - выход из программы)." << std::endl;
    while (true) {
        std::cout << "> ";
        std::cin  >> type;
        if (type == 0) {
            break;
        }
        if (type == SQUARE_ID) {
            std::vector<workType> data(4);
            std::cout << "Введите координаты противоположных вершин квадрата > ";
            for (int i = 0; i < 4; ++i) {
                std::cin >> data[i];
            }
            std::shared_ptr<Square<workType> > sq(new Square<workType>({data[0], data[1]}, {data[2], data[3]}));
            figures.push_back(sq);
        }
        else if (type == TRIANGLE_ID) {
            std::cout << "Введите координаты вершин треугольника > ";
            std::vector<workType> data(6);
            for (int i = 0; i < 6; ++i) {
                std::cin >> data[i];
            }
            std::shared_ptr<Triangle<workType> > tr(new Triangle<workType>({data[0], data[1]}, {data[2], data[3]}, {data[4], data[5]}));
            figures.push_back(tr);
        }
        else if (type == OCTAGON_ID) {
            std::cout << "Введите координаты центра восьмиугольника и вектора описанной окружности > ";
            std::vector<workType> data(4);
            for (int i = 0; i < 4; ++i) {
                std::cin >> data[i];
            }
            std::shared_ptr<Octagon<workType> > oc(new Octagon<workType>({data[0], data[1]}, data[2], data[3]));
            figures.push_back(oc);
        }
        else {
            std::cout << "Ошибка! Неверный ввод!" << std::endl;
            continue;
        }
        std::cout << "Фигура успешно добавлена." << std::endl;
        if (figures.size() == sizeBuffer) {
            messages.Push(figures);
            while (!messages.Empty()) {}
            figures.clear();
        }
    }
    messages.Push(figures);
    figures.clear();
    messages.Push(figures);
    figures.clear();
    thr.join();
    return 0;
}

