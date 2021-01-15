/* Ляшун Дмитрий Сергеевич, М8О-207Б-19 */
#pragma once
#include <vector>
#include <stack>
#include <stdio.h>
#include <cstdlib>
#include "figures.hpp"
enum OPERATION_TYPE { INSERT, ERASE };
class Document {
    public:
        void Insert(Figure* figure, const int& index);
        void Erase(const int& index);
        void LoadFromFile(FILE* file);
        void SaveInFile(FILE* file);
        void Undo();
        void Print();
        void NewDocument(FILE* file);
        bool Empty() {
            return data.empty();
        }
        ~Document() {
            for (int i = 0; i < data.size(); ++i) {
                delete data[i];
            }
            while (!undo.empty()) {
                std::pair<Figure*, int> t = undo.top();
                if (t.second == INSERT) {
                    delete t.first;
                }
                undo.pop();
            }
        }
    private:
        std::vector<Figure*> data;
        Factory adder;
        std::stack<std::pair<Figure*,int> > undo;
};
void Document::Insert(Figure* figure, const int& index) {
    if (index < 0 || index > data.size()) {
        throw(std::runtime_error("Ошибка! Указана некорректная позиция удаления!"));
    }
    if (data.empty()) {
        data.push_back(figure);
    }
    else {
        data.insert(data.begin() + index, figure);
    }
    undo.push(std::make_pair(figure, ERASE));
}
void Document::Erase(const int& index) {
    if (index < 0 || index >= data.size()) {
        throw(std::runtime_error("Ошибка! Указана некорректная позиция удаления!"));
    }
    undo.push(std::make_pair(data[index], INSERT));
    data.erase(data.begin() + index);
}
void Document::LoadFromFile(FILE* file) {
    int n;
    fscanf(file, "%d", &n);
    for (int i = 0; i < data.size(); ++i) {
        delete data[i];
    }
    while (!undo.empty()) {
        std::pair<Figure*, int> t = undo.top();
        if (t.second == INSERT) {
            delete t.first;
        }
        undo.pop();
    }
    data.resize(n);
    int type;
    for (int i = 0; i < n; ++i) {
        fscanf(file, "%d", &type);
        std::vector<double> figuresData;
        if (type == 1) {
            figuresData.resize(4);
        }
        else if (type == 2) {
            figuresData.resize(6);  
        }
        else if (type == 3) {
            figuresData.resize(4);
        }
        for (int j = 0; j < figuresData.size(); ++j) {
            fscanf(file, "%lf", &figuresData[j]);
        }
        data[i] = adder.Create(type, figuresData);
    }
}
void Document::SaveInFile(FILE* file) {
    int size = data.size();
    fprintf(file, "%d\n", size);
    for (int i = 0; i < data.size(); ++i) {
        fprintf(file, "%d ", data[i]->type);
        if (data[i]->type == 1) {
            Square* sq = dynamic_cast<Square*>(data[i]);
            fprintf(file, "%lf ", sq->point1.x);
            fprintf(file, "%lf ", sq->point1.y);
            fprintf(file, "%lf ", sq->point2.x);
            fprintf(file, "%lf\n", sq->point2.y);
        }
        else if (data[i]->type == 2) {
            Triangle* tr = dynamic_cast<Triangle*>(data[i]);
            fprintf(file, "%lf ", tr->point1.x);
            fprintf(file, "%lf ", tr->point1.y);
            fprintf(file, "%lf ", tr->point2.x);
            fprintf(file, "%lf ", tr->point2.y);
            fprintf(file, "%lf ", tr->point3.x);
            fprintf(file, "%lf\n", tr->point3.y);
        }
        else if (data[i]->type == 3) {
            Octagon* oc = dynamic_cast<Octagon*>(data[i]);
            fprintf(file, "%lf ", oc->center.x);
            fprintf(file, "%lf ", oc->center.y);
            fprintf(file, "%lf ", oc->vec_x);
            fprintf(file, "%lf\n", oc->vec_y);
        }
    }
}
void Document::Undo() {
    if (undo.empty()) {
        return;
    }
    std::pair<Figure*, int> oper = undo.top();
    undo.pop();
    if (oper.second == ERASE) {
        for (int i = 0; i < data.size(); ++i) {
            if (Equals(oper.first, data[i])) {
                data.erase(data.begin() + i);
                return;
            }
        }
    }
    else if (oper.second == INSERT) {
        data.push_back(oper.first);
    }
}
void Document::Print() {
    if (data.empty()) {
        std::cout << "Документ пустой!" << std::endl;
        return;
    }
    std::cout << "Содержимое документа: " << std::endl;
    for (int i = 0; i < data.size(); ++i) {
        data[i]->Output();
    }
}
void Document::NewDocument(FILE* file) {
    if (file != NULL) {
        SaveInFile(file);
    }
    data.clear();
    while (!undo.empty()) {
        undo.pop();
    }
}

