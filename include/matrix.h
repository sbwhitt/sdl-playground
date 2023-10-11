#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

template <typename T>
class Matrix {
private:
    std::vector<std::vector<T>> outer;

public:
    Matrix() {}
    Matrix(int r, int c) {
        for (int i = 0; i < r; i++) {
            outer.push_back(std::vector<T>(c));
        }
    }
    int Build(int r, int c) {
        for (int i = 0; i < r; i++) {
            outer.push_back(std::vector<T>(c));
        }

        return 0;
    }
    int Fill(T t) {
        if (outer.size() < 1) return 1;
        for (int i = 0; i < outer.size(); i++) {
            for (int j = 0; j < outer[i].size(); j++) {
                outer[i][j] = t;
            }
        }

        return 0;
    }
    int FillAlternate(T t1, T t2) {
        if (outer.size() < 1) return 1;
        bool first = true;
        for (int i = 0; i < outer.size(); i++) {
            for (int j = 0; j < outer[i].size(); j++) {
                if (first) {
                    outer[i][j] = t1;
                }
                else {
                    outer[i][j] = t2;
                }
                first = !first;
            }
        }

        return 0;
    }
    std::vector<T>& operator[](int i) {
        return outer[i];
    }
};

#endif