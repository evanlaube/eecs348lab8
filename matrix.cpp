#include "matrix.hpp"
#include <iomanip>
#include <iostream>
#include <stdexcept>

// implementation of functions declared in matrix.hpp goes here
// function definitions for a class have their names prefixed with
// the class name and "::"

// e.g. for the constructor:

Matrix::Matrix(size_t N) {
    // initialize an empty NxN matrix
    data = std::vector<int>(N*N);
    size = N;
}

Matrix::Matrix(std::vector<std::vector<int> > nums) {
    size = nums.size();
    data = std::vector<int>(size*size);

    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            data[i*size+j] = nums[i][j];
        }
    }
}

void Matrix::print_matrix() const {
    // Get largest number of digits of number in matrix
    int maxDigits = 0;
    for(int i = 0; i < size*size; i++) {
        int number = data[i];
        if(number < 0) {
            number = -number;
        }
        int digits = 0;
        if(number == 0) {
            digits = 0;
        } else {
            while (number != 0) {
                number /= 10;
                digits++;
            }
        }

        maxDigits = std::max(digits, maxDigits);
    }

    for(int i = 0; i < size; i++) {
        for(int n = 0; n < size; n++) {
            std::cout << std::setw(maxDigits) << std::setfill('0') << data[size*i + n] << " ";
        }
        std::cout << std::endl;
    }
}

Matrix Matrix::operator+(const Matrix &rhs) const {
    if(size != rhs.size) {
        throw std::runtime_error("Attempted to add matrices of different sizes");
    }
    Matrix result(size);
    for(int i = 0; i < size; i++) {
        for(int n = 0; n < size; n++) {
            result.data[i*size + n] = data[i*size+n] + rhs.data[i*size+n];
        }
    }

    return result;
}

Matrix Matrix::operator*(const Matrix &rhs) const {
    if(size != rhs.size) {
        throw std::runtime_error("Attempted to multiply matrices of different sizes");
    }

    Matrix result(size);

    for(int row = 0; row < size; row++) {
        for(int col = 0; col < size; col++) {
            for(int k = 0; k < size; k++) {
                result.data[row*size + col] += data[row * size + k] * rhs.data[k * size + col];
            }
        }
    }

    return result;
}

void Matrix::set_value(std::size_t i, std::size_t j, int n) {
    if(i >= size || j >= size) {
        throw std::out_of_range("Attempted to set matrix cell out of bounds");
    }

    data[i*size+j] = n;
}

int Matrix::get_value(std::size_t i, std::size_t j) const {
    if(i >= size || j >= size) {
        throw std::out_of_range("Attempted to get matrix cell out of bounds");
    }

    return data[i*size+j];
}

int Matrix::get_size() const {
    return size;
}


int Matrix::sum_diagonal_major() const {
    int sum = 0;
    for(int i = 0; i < size; i++) {
        sum += data[i*size + i];
    }
    return sum;
}

int Matrix::sum_diagonal_minor() const {
    int sum = 0;
    for(int i = 0; i < size; i++) {
        sum += data[i*size + (size-1-i)];
    }
    return sum;
}

void Matrix::swap_rows(std::size_t r1, std::size_t r2) {
    for(int i = 0; i < size; i++) {
        int temp = data[r1*size + i];
        data[r1*size+i] = data[r2*size+i];
        data[r2*size+i] = temp;
    }
}

void Matrix::swap_cols(std::size_t c1, std::size_t c2) {
    for(int i =0; i < size; i++) {
        int temp = data[i*size + c1];
        data[i*size+c1] = data[i*size+c2];
        data[i*size+c2] = temp;
    }
}

