#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <vector>

using namespace std;

typedef vector<vector<double>> Matrix;

void read_matrix_from_file(const char *file_name, Matrix &matrix_1, Matrix &matrix_2) {
    ifstream file(file_name);
    int matrix_size;
    file >> matrix_size;

    matrix_1 = vector<vector<double>>(matrix_size, vector<double>(matrix_size));
    matrix_2 = vector<vector<double>>(matrix_size, vector<double>(matrix_size));

    for (int y = 0; y < matrix_size * 2; y++) {
        for (int x = 0; x < matrix_size; x++) {
            if (y < matrix_size)
                file >> matrix_1[y][x];
            else file >> matrix_2[y - matrix_size][x];
        }
    }
}

void print_matrix(const Matrix &matrix) {
    int m = matrix.size();
    for (int y = 0; y < m; y++) {
        int n = matrix[y].size();
        cout << "| ";
        for (int x = 0; x < n; x++) {
            cout << right << setw(6) << matrix[y][x] << " ";
        }
        cout << "|" << endl;
    }
    cout << endl;
}

void print_matrix(const Matrix &matrix_1, const Matrix &matrix_2) {
    int m1 = matrix_1.size();
    int m2 = matrix_2.size();

    for (int y = 0; y < m1 || y < m2; y++) {
        if (y < m1) {
            int n = matrix_1[y].size();
            cout << "| ";
            for (int x = 0; x < n; x++) {
                cout << right << setw(6) << matrix_1[y][x] << " ";
            }
            cout << "|";
        } else cout << setw(3 + 7 * matrix_1[0].size()) << " ";

        if (y < m2) {
            int n = matrix_2[y].size();
            cout << "  |";
            for (int x = 0; x < n; x++) {
                cout << right << setw(6) << matrix_2[y][x] << " ";
            }
            cout << "|" << endl;
        }
    }
    cout << endl;
}

Matrix operator+(Matrix matrix_1, Matrix matrix_2) {
    int rows = min(matrix_1.size(), matrix_2.size());
    int columns = min(matrix_1[0].size(), matrix_2[0].size());
    Matrix sum = vector<vector<double>>(rows, vector<double>(columns));

    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < columns; x++) {
            sum[y][x] = matrix_1[y][x] + matrix_2[y][x];
        }
    }

    return sum;
}

Matrix operator*(Matrix matrix_1, Matrix matrix_2) {
    if (matrix_1[0].size() != matrix_2.size()) {
        throw runtime_error("tried to multiply matrices of incompatible sizes");
    }
    int shared = matrix_2.size();
    int rows = matrix_1.size();
    int columns = matrix_2[0].size();
    Matrix product = vector<vector<double>>(rows, vector<double>(columns));
    
    for (int y = 0; y < rows; y++) {
        for (int x = 0; x < columns; x++) {
            double sum = 0;
            for (int i = 0; i < shared; i++) {
                sum += matrix_1[y][i] * matrix_2[i][x];
            }
            product[y][x] = sum;
        }
    }

    return product;
}

void get_diagonal_sum(const Matrix &matrix) {
    int rows = matrix.size();
    int xp = 0, xs = matrix[0].size() - 1;
    double primary = 0, secondary = 0;
    for (int y = 0; y < rows && xs >= 0; y++, xp++, xs--) {
        primary += matrix[y][xp];
        secondary += matrix[y][xs];
    }
    cout << "Primary: " << primary << endl;
    cout << "Secondary: " << secondary << endl << endl;
}

void swap_matrix_row(Matrix matrix, int row1, int row2) {
    int rows = matrix.size();
    if (row1 >= rows || row2 >= rows) {
        cout << "cannot swap rows " << row1 << " and " << row2 << ": invalid index" << endl;
        return;
    }

    vector<double> temp = matrix[row1];
    matrix[row1] = matrix[row2];
    matrix[row2] = temp;

    print_matrix(matrix);
}

int main(int argc, char *argv[]) {
    Matrix matrix_1, matrix_2;
    read_matrix_from_file("matrix.txt", matrix_1, matrix_2);
    cout << "print_matrix" << endl;
    print_matrix(matrix_1, matrix_2);

    auto add_matrix = matrix_1 + matrix_2;
    cout << "operator+ overloading" << endl;
    print_matrix(add_matrix);

    auto multiply_matrix = matrix_1 * matrix_2;
    cout << "operator* overloading" << endl;
    print_matrix(multiply_matrix);

    cout << "get matrix diagonal sums of matrix 1" << endl;
    get_diagonal_sum(matrix_1);

    cout << "swap rows of matrix 1" << endl;
    swap_matrix_row(matrix_1, 0, 1);
    swap_matrix_row(matrix_1, 0, 100);
}
