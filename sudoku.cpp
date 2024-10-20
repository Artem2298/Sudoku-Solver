#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <sstream>

using namespace std;

#define N 9

class Matrix {
private:
	int matrix[N][N];
public:

	Matrix() {}
	bool loadData(string fileName);
	bool сhekСondition(int row, int col, int number);
	bool sudokuSolution(int row, int col);
	void print();
};

bool Matrix::loadData(string fileName) {
	ifstream file(fileName);
	if (!file.is_open()) {
		cout << "file is not found :( ";
		return false;
	}
	string line;
	int r = 0;
	while (getline(file, line)) {
		istringstream tokenStream(line);
		string token;
		getline(tokenStream, token, '\n');
		for (int j = 0; j < N; j++) {
			matrix[r][j] = (int)token[j] - 48;
		}
		r++;
	}
	return true;
}

bool Matrix::сhekСondition(int row, int col, int number) {
	// in row
	for (int x = 0; x <= 8; x++) {
		if (matrix[row][x] == number) {
			return false;
		}
	}
	// in col
	for (int x = 0; x <= 8; x++) {
		if (matrix[x][col] == number) {
			return false;
		}
	}
	// in square
	int startRow = row - row % 3;
	int	startCol = col - col % 3;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (matrix[i + startRow][j + startCol] == number) {
				return false;
			}
		}

	}
	return true;
}

bool Matrix::sudokuSolution(int row, int col) {
	if (row == N - 1 && col == N) {
		return true;
	}

	if (col == N) {
		row++;
		col = 0;
	}

	if (matrix[row][col] > 0) {
		return sudokuSolution(row, col + 1);
	}

	for (int i = 1; i <= N; i++) {
		if (сhekСondition(row, col, i)) {
			matrix[row][col] = i;
			if (sudokuSolution(row, col + 1))
				return true;
		}

		matrix[row][col] = 0;
	}
	return false;
}

void Matrix::print() {
	if (sudokuSolution(0, 0)) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cout << matrix[i][j] << " ";
			}
			cout << endl;
		}
	}
	else {
		cout << "no solution exists :( " << endl;
	}
}

int main() {

	cout << "Enter the name of the file with the .txt ending " << endl;
	string fileName;
	cin >> fileName;

	Matrix* matrix = new Matrix();

	if (matrix->loadData(fileName)) {
		matrix->print();
	}


	return 0;
}
