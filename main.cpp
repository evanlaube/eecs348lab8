#include "matrix.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

int main(int argc, char *argv[]) {
    std::cout << "Enter name of file to process: ";
    std::string filename;
    std::cin >> filename;

    std::ifstream inputFile(filename);

    Matrix a(0);
    Matrix b(0);

    if(inputFile.is_open()) {
        std::string line;

        int size = 0;
        try {
            std::string sizeString;
            std::getline(inputFile, sizeString);

            size = stoi(sizeString);
            a = Matrix(size);
            b = Matrix(size);
        } catch(...) {
            std::cerr << "Input file in invalid format." << std::endl;
            return 1;
        }
        // Get next line
        std::getline(inputFile, line);

        // Skip all blank lines that may have been inserted
        while(line == "\n") {
            std::getline(inputFile, line);
        }

        // Build first matrix
        Matrix a(size);
        for(int i = 0; i < size; i++) {
            // Add line data to Matrix
            std::vector<int> data(size);
            std::stringstream ss(line);
            int number;
            int n = 0;
            while(ss >> number) {
                a.set_value(i, n, number);
                n++;
            }
            std::getline(inputFile, line);
        }

        // Build second matrix
        Matrix b(size);
        for(int i = 0; i < size; i++) {
            // Add line data to Matrix
            std::vector<int> data(size);
            std::stringstream ss(line);
            int number;
            int n = 0;
            while(ss >> number) {
                b.set_value(i, n, number);
                n++;
            }
            std::getline(inputFile, line);
        }

        // Print matrices to the user
        std::cout << "Matrix A:" << std::endl;
        a.print_matrix();
        std::cout << std::endl;

        std::cout << "Matrix B:" << std::endl;
        b.print_matrix();
        std::cout << std::endl;

        std::cout << "Result of A + B: " << std::endl;
        (a+b).print_matrix();
        std::cout << std::endl;

        std::cout << "Result of A * B: " << std::endl;
        (a*b).print_matrix();
        std::cout << std::endl;

        std::cout << "Sum of major diagonal elements in A: " << a.sum_diagonal_major() << std::endl;
        std::cout << "Sum of major diagonal elements in B: " << b.sum_diagonal_major() << std::endl;
        std::cout << std::endl;

        std::cout << "Sum of minor diagonal elements in A: " << a.sum_diagonal_minor() << std::endl;
        std::cout << "Sum of minor diagonal elements in B: " << b.sum_diagonal_minor() << std::endl;
        std::cout << std::endl;

        if(size > 2) {
            Matrix cpy = a;
            cpy.swap_rows(1, 2);
            std::cout << "Result of swapping row 2 of Matrix A with row 3" << std::endl;
            cpy.print_matrix();
            std::cout << std::endl;
        }

        if(size > 3) {
            Matrix cpy = b;
            cpy.swap_cols(2,3);
            std::cout << "Result of swapping col 3 of Matrix B with col 4" << std::endl;
            cpy.print_matrix();
            std::cout << std::endl;
        }


    } else {
        std::cerr << "Unable to open file. Make sure it exists and has valid permissions" << std::endl;
        return 1;
    }

    return 0;
}
