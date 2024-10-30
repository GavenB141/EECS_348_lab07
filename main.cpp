#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void read_matrix_from_file(
    const char *file_name,
    vector<vector<double>> &matrix_1,
    vector<vector<double>> &matrix_2) {
    ifstream file(file_name);
    int matrix_size;
    file >> matrix_size;

    matrix_1 = vector<vector<double>>(matrix_size, vector<double>(matrix_size));
    matrix_2 = vector<vector<double>>(matrix_size, vector<double>(matrix_size));

    // TODO
}

void print_matrix(const vector<vector<double>> &matrix) {
    // TODO
}

void print_matrix(const vector<vector<double>> &matrix_1, const vector<vector<double>> &matrix_2) {
    // TODO
}

vector<vector<double>> operator+(vector<vector<double>> matrix_1, vector<vector<double>> matrix_2) {
    // TODO
}

vector<vector<double>> operator*(vector<vector<double>> matrix_1, vector<vector<double>> matrix_2) {
    // TODO
}

void get_diagonal_sum(const vector<vector<double>> &matrix) {
    // TODO
}

void swap_matrix_row(vector<vector<double>> matrix, int row1, int row2) {
    // TODO
}

int main(int argc, char *argv[]) {
    vector<vector<double>> matrix_1, matrix_2;
    read_matrix_from_file("matrix.txt", matrix_1, matrix_2);
    cout << "print_matrix" << endl;
    print_matrix(matrix_1, matrix_2);

    auto add_matrix = matrix_1 + matrix_2;
    cout << "operator+ overloading" << endl;
    print_matrix(add_matrix);

    auto multiply_matrix = matrix_1 * matrix_2;
    cout << "operator* overloading" << endl;
    print_matrix(multiply_matrix);

    cout << "get matrix diagonal sum" << endl;
    get_diagonal_sum(matrix_1);

    cout << "swap matrix rows" << endl;
    swap_matrix_row(matrix_1, 0, 1);
    swap_matrix_row(matrix_1, 0, 100);
}