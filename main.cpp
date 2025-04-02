#include "matrix.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

int main(int argc, char *argv[]) {
    // Prompt the user for an input file
    std::cout << "Enter name of file to process: ";
    // Create a string to store the filename
    std::string filename;
    // Take user input and store in filename
    std::cin >> filename;

    // Create an input file stream with the input file name
    std::ifstream inputFile(filename);

    // Create new matrices a and b with dimension 0
    Matrix a(0);
    Matrix b(0);

    // Make sure that the file exists
    if(inputFile.is_open()) {
        // Create a string to store each line
        std::string line;
        // Initialize the size of the matrices to zero
        int size = 0;

        try {
            // Take the first line of the file as the size of the matrices
            std::string sizeString;
            std::getline(inputFile, sizeString);

            // Cast the size string to an integer
            size = stoi(sizeString);
            // Reconstruct matrices to be proper size
            a = Matrix(size);
            b = Matrix(size);
        } catch(...) { // If the first line cannot be cast to an int
            // Print an error to the user and return
            std::cerr << "Input file in invalid format." << std::endl;
            return 1;
        }
        // Get next line after size
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
            // Convert the line to a stringstream to easily cast to int
            std::stringstream ss(line);
            // Store each number in 'number'
            int number;
            // Column number 'n'
            int n = 0;
            while(ss >> number) { // While there are numbers to read in a row
                // Set the value at row i and col n to number
                a.set_value(i, n, number);
                // Increment the column
                n++;
            }
            // Get the next line
            std::getline(inputFile, line);
        }

        // Build second matrix
        Matrix b(size);
        for(int i = 0; i < size; i++) {
            // Add line data to Matrix
            std::vector<int> data(size);
            // Convert the line to a stringstream to easily cast to int
            std::stringstream ss(line);
            // Store each number in 'number'
            int number;
            // Column number 'n'
            int n = 0;
            while(ss >> number) { // While there are numbers to read in a row
                // Set the value at row i and col n to number
                b.set_value(i, n, number);
                // Increment the column
                n++;
            }
            // Get next line
            std::getline(inputFile, line);
        }

        // Print Matrix A to user
        std::cout << "Matrix A:" << std::endl;
        a.print_matrix();
        std::cout << std::endl;

        // Print Matrix B to user
        std::cout << "Matrix B:" << std::endl;
        b.print_matrix();
        std::cout << std::endl;

        // Demo matrix addition
        std::cout << "Result of A + B: " << std::endl;
        (a+b).print_matrix();
        std::cout << std::endl;

        // Demo matrix multiplication
        std::cout << "Result of A * B: " << std::endl;
        (a*b).print_matrix();
        std::cout << std::endl;

        // Demo the major diagonal sums
        std::cout << "Sum of major diagonal elements in A: " << a.sum_diagonal_major() << std::endl;
        std::cout << "Sum of major diagonal elements in B: " << b.sum_diagonal_major() << std::endl;
        std::cout << std::endl;

        // Demo the minor diagonal sums
        std::cout << "Sum of minor diagonal elements in A: " << a.sum_diagonal_minor() << std::endl;
        std::cout << "Sum of minor diagonal elements in B: " << b.sum_diagonal_minor() << std::endl;
        std::cout << std::endl;

        if(size > 2) { // If the size of the matrices is more than 2
            // Demo the row swapping function by swapping row 2 and 3 of matrix A
            Matrix cpy = a;
            cpy.swap_rows(1, 2);
            std::cout << "Result of swapping row 2 of Matrix A with row 3" << std::endl;
            cpy.print_matrix();
            std::cout << std::endl;
        }

        if(size > 3) { // If the size is more than 3
            // Demo the column swapping function by swapping column 3 and 4 of matrix B
            Matrix cpy = b;
            cpy.swap_cols(2,3);
            std::cout << "Result of swapping col 3 of Matrix B with col 4" << std::endl;
            cpy.print_matrix();
            std::cout << std::endl;
        }


    } else { // If the file is unable to be opened
        // Print an error to the user and return
        std::cerr << "Unable to open file. Make sure it exists and has valid permissions" << std::endl;
        return 1;
    }

    return 0;
}
