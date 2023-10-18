#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

enum ExtendDir {
    UP = 0,
    LEFT = 1,
    DOWN = 2,
    RIGHT = 3
};

template <typename T>
class Matrix {
private:
    std::vector<std::vector<T>> outer;

public:
    int rows;
    int cols;

    Matrix() {}
    Matrix(int r, int c) {
        rows = r;
        cols = c;
        for (int i = 0; i < r; i++) {
            outer.push_back(std::vector<T>(c));
        }
    }
    int Build(int r, int c) {
        rows = r;
        cols = c;
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
    std::vector<T> GetRow(int r) {
        // if (r < 0 || r >= rows) return NULL;
        return outer[r];
    }
    std::vector<T> GetCol(int c) {
        std::vector<T> col;
        for (int i = 0; i < rows; i++) {
            col.push_back(outer[i][c]);
        }
        return col;
    }
    int Extend(ExtendDir dir, std::vector<T> add) {
        if (rows <= 1 || add.size() != cols) return 1;
        switch (dir) {
            case UP:
                for (int i = rows-2; i >= 0; i--) {
                    outer[i+1] = outer[i];
                }
                outer[0] = add;
                break;
            case DOWN:
                for (int i = 1; i < rows; i++) {
                    outer[i-1] = outer[i];
                }
                outer[rows-1] = add;
                break;
            case LEFT:
                for (int i = 0; i < rows; i++) {
                    for (int j = cols-2; j >= 0; j--) {
                        outer[i][j+1] = outer[i][j];
                    }
                    outer[i][0] = add[i];
                }
                break;
            case RIGHT:
                for (int i = 0; i < rows; i++) {
                    for (int j = 1; j < cols; j++) {
                        outer[i][j-1] = outer[i][j];
                    }
                    outer[i][cols-1] = add[i];
                }
                break;
        }

        return 0;
    }
    std::vector<T>& operator[](int i) {
        return outer[i];
    }
};

#endif