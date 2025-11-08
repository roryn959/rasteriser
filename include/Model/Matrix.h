#pragma once

#include <math.h>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <stdexcept>

#include "Core/Point.h"

template <typename T, int N, int M>
class Matrix {
public:
    Matrix(std::initializer_list<std::initializer_list<T>> values) {
        size_t i = 0;
        for (auto const& row : values) {
            size_t j = 0;
            for (auto const& val : row )
                m_array[i][j++] = val;
            ++i;
        }
    }

    T& operator()(size_t i, size_t j) { return m_array[i][j]; }
    const T& operator()(size_t i, size_t j) const { return m_array[i][j]; }

    template <int L>
    Matrix<T, N, L> operator*(const Matrix<T, M, L>& rhs) const {
        Matrix<T, N, L> result{};
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < L; ++j) {
                T curr{0};
                for (int k = 0; k < M; ++k) {
                    curr += m_array[i][k] * rhs.m_array[k][j];
                }
                result.m_array[i][j] = curr;
            }
        }
        return result;
    }

    Matrix<T, N, M> operator*(const T& scalar) const {
        Matrix<T, N, M> result{};
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                result.m_array[i][j] = m_array[i][j] * scalar;
            }
        }
        return result;
    }

    Point operator*(const Point& point) const {
        if (N != 3 || M != 3)
            throw std::runtime_error("Matrix must be 3x3 to transform a Point.");

        return Point {
            m_array[0][0] * point.m_x + m_array[0][1] * point.m_y + m_array[0][2] * point.m_z,
            m_array[1][0] * point.m_x + m_array[1][1] * point.m_y + m_array[1][2] * point.m_z,
            m_array[2][0] * point.m_x + m_array[2][1] * point.m_y + m_array[2][2] * point.m_z,
        };
    }

    Matrix<T, N, M> operator+(const Matrix<T, N, M>& rhs) const {
        Matrix<T, N, M> result{};
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < M; ++j) {
                result.m_array[i][j] = m_array[i][j] + rhs.m_array[i][j] ;
            }
        }
    }



private:
    T m_array[N][M];
};

template<typename T, int N, int M>
Matrix<T, N, M> operator*(T scalar, const Matrix<T, N, M>& mat) {
    return mat * scalar;
}

template<typename T, int N, int M>
std::ostream& operator<<(std::ostream& os, const Matrix<T, N, M>& mat) {
    os << std::fixed << std::setprecision(3); 
    for (int i = 0; i < N; ++i) {
        os << "[ ";
        for (int j = 0; j < M; ++j) {
            os << std::setw(8) << mat(i, j);
            if (j < M - 1) os << ", ";
        }
        os << " ]\n";
    }
    return os;
}

// Commonly used matrices

const Matrix<float, 3, 3> IDENTITY {
    { 1, 0, 0 },
    { 0, 1, 0 },
    { 0, 0, 1 }
};