#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

template <typename T>
class Matrix {
private:
    std::vector<std::vector<T>> outer;

public:
    Matrix(int r, int c) {
        for (int i = 0; i < r; i++) {
            outer.push_back(std::vector<T>(c));
        }
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
    std::vector<T>& operator[](int i) {
        return outer[i];
    }
};

#endif