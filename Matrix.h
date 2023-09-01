#pragma once
#define NOMINMAX
#include <iomanip>
#include <iostream>
#include <Windows.h>
#include <string>
#include <cassert>
#include <optional>

using namespace std;

namespace DataContainers {
	template <typename type, typename = enable_if_t<is_arithmetic_v<type>>>
	class Matrix
	{
	private:
		unsigned int rows;
		unsigned int columns;
		type** data;

		static int MaxSize(type** init, int row, int col) {
			int res = 0;

			for (size_t i = 0; i < row; i++) {
				for (size_t j = 0; j < col; j++) {
					if (to_string(init[i][j]).size() > res)
						res = to_string(init[i][j]).size();
				}
			}
			return res;
		}

	public:
		~Matrix() {
			for (size_t i = 0; i < rows; i++) {
				delete[] data[i];
				data[i] = nullptr;
			}
			delete data;
			data = nullptr;
		}

		Matrix(unsigned int row, unsigned int col) {
			data = new type * [row];
			for (size_t i = 0; i < row; i++)
				data[i] = new type[col];

			this->rows = row;
			this->columns = col;
		}

		Matrix(const Matrix<type>& elem) : Matrix(elem.rows, elem.columns) {
			for (size_t i = 0; i < rows; i++) {
				for (size_t j = 0; j < columns; j++)
					data[i][j] = elem.data[i][j];
			}
		}

		static void Initialize(type**& init, int row, int col) {
			init = new type * [row];
			for (size_t i = 0; i < row; i++)
				init[i] = new type[col];
		}

		static void Delete(type**& init, int row) {
			for (size_t i = 0; i < row; i++) {
				delete[] init[i];
				init[i] = nullptr;
			}
			init = nullptr;
		}


		friend ostream& operator<<(ostream& out, Matrix<type> p) {
			int maxSize = MaxSize(p.data, p.rows, p.columns);

			for (size_t i = 0; i < p.rows; i++) {
				for (size_t j = 0; j < p.columns; j++)
					out << setw(maxSize + 2) << p.data[i][j];
				out << endl;
			}
			return out;
		}
		friend istream& operator>>(istream& in, Matrix<type>& p) {
			for (size_t i = 0; i < p.rows; i++) {
				COORD coord;
				coord.Y = i + 1;
				for (size_t j = 0; j < p.columns; j++) {
					if (j == 0)
						coord.X = j + 1;
					bool flag;
					do {
						int tmp;
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

						in >> tmp;
						p.data[i][j] = tmp;

						const int elemSize = to_string(tmp).size();
						if (in.fail()) {
							in.clear();
							in.ignore(32767, '\n');
							SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
							for (size_t i = 0; i < 100; i++) cout << " ";
							flag = true;
						}
						else {
							flag = false;
							coord.X += elemSize + 2;
						}
					} while (flag);
				}
			}
			return in;

		}
		friend Matrix operator+(Matrix<type>& first, Matrix<type>& second) {
			assert(first.columns == second.rows);

			Matrix<type> tmp(first.rows, second.columns);

			for (size_t i = 0; i < tmp.rows; i++) {
				for (size_t j = 0; j < tmp.columns; j++) {
					tmp.data[i][j] = 0;
					for (size_t k = 0; k < first.columns; k++) {

						if (first.data[i][k] != 0 || second.data[k][j] != 0)
							tmp.data[i][j] += (first.data[i][k] + second.data[k][j]);

					}
				}
			}
			return tmp;

		}
		friend Matrix operator-(Matrix<type>& first, Matrix<type>& second) {
			assert((first.columns == second.columns && first.rows == second.rows) && "Matrix sizes do not match");

			Matrix<type> tmp(first.rows, second.columns);

			for (size_t i = 0; i < tmp.rows; i++) {
				for (size_t j = 0; j < tmp.columns; j++) {
					tmp.data[i][j] = 0;
					for (size_t k = 0; k < first.columns; k++) {
						if (first.data[i][k] != 0 || second.data[k][j] != 0) {
							tmp.data[i][j] += (first.data[i][k] - second.data[k][j]);
						}
					}
				}
				return tmp;
			}
		}
		friend Matrix operator*(Matrix<type>&first, Matrix<type>&second) {
			assert((first.columns == second.rows) && "Matrix sizes do not match");

			Matrix<type> tmp(first.rows, second.columns);

			for (size_t i = 0; i < tmp.rows; i++) {
				for (size_t j = 0; j < tmp.columns; j++) {
					tmp.data[i][j] = 0;
					for (size_t k = 0; k < first.columns; k++) {
						if (first.data[i][k] != 0 || second.data[k][j] != 0)
							tmp.data[i][j] += (first.data[i][k] * second.data[k][j]);
					}
				}
			}
			return tmp;

		}
		friend Matrix operator/(Matrix<type>&first, Matrix<type>&second) {
			assert((first.columns == second.rows) && "Matrix sizes do not match");

			Matrix<type> tmp(first.rows, second.columns);

			for (size_t i = 0; i < tmp.rows; i++) {
				for (size_t j = 0; j < tmp.columns; j++) {
					tmp.data[i][j] = 0;
					for (size_t k = 0; k < first.columns; k++) {
						if (first.data[i][k] != 0 || second.data[k][j] != 0)
							tmp.data[i][j] += (first.data[i][k] / second.data[k][j]);
					}
				}
			}
			return tmp;

		}
		Matrix& operator=(Matrix<type> second)
		{
			if (data != nullptr)
				Clear();

			rows = second.rows;
			columns = second.columns;

			data = new type * [rows];
			for (size_t i = 0; i < columns; i++)
				data[i] = new type[columns];

			for (size_t i = 0; i < rows; i++) {
				for (size_t j = 0; j < columns; j++)
					data[i][j] = second.data[i][j];
			}
			return *this;
		}


		friend bool operator==(Matrix<type>&first, Matrix<type>&second)	{
			if (first.rows != second.rows || first.columns != second.columns) return false;

			for (size_t i = 0; i < first.rows; i++) {
				for (size_t j = 0; j < first.columns; j++)
					if (first.data[i][j] != second.data[i][j])
						return false;
				
			}
			return true;
		}
		friend bool operator!=(Matrix<type>&first, Matrix<type>&second)	{
			if (first.rows != second.rows || first.columns != second.columns)
				return true;

			for (size_t i = 0; i < first.rows; i++) {
				for (size_t j = 0; j < first.columns; j++)
					if (first.data[i][j] != second.data[i][j])
						return true;
			}
			return false;
		}

		void Clear()
		{
			for (size_t i = 0; i < rows; i++) {
				delete[] data[i];
				data[i] = nullptr;
			}
			delete data;
			data = nullptr;
			rows = 0;
			columns = 0;
		}

		void RandomFill(type min = 0, type max = 10) {
			for (size_t i = 0; i < rows; i++) {
				for (size_t j = 0; j < columns; j++) {
					if constexpr (is_integral_v<type>) data[i][j] = rand() % (max - min + 1) + min;
					else data[i][j] = (max - min) * rand() / RAND_MAX + min;
				}
			}
		}

		void Print() {
			for (size_t i = 0; i < rows; i++) {
				for (size_t j = 0; j < columns; j++)
					cout << setw(3) << data[i][j];
				cout << endl;
			}
		}

		void Transposition() {
			type** newData;
			Initialize(newData, columns, rows);

			for (size_t i = 0; i < rows; i++) {
				for (size_t j = 0; j < columns; j++)
					newData[j][i] = data[i][j];
			}


			for (size_t i = 0; i < rows; i++) {
				delete[] data[i];
				data[i] = nullptr;
			}
			delete data;
			data = nullptr;
			data = newData;
			swap(rows, columns);
		}

		// Request user input in console
		void KbInput(int posX = 0, int posY = 0) {
			for (size_t i = 0; i < rows; i++) {
				COORD coord;
				coord.Y = i + 1 + posY;
				for (size_t j = 0; j < columns; j++) {
					if (j == 0) coord.X = j + 1 + posX;
					bool flag;
					do {
						int tmp;
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

						cin >> tmp;
						data[i][j] = tmp;

						int size_tmpElem = to_string(tmp).size();
						if (cin.fail())	{
							cin.clear();
							cin.ignore(32767, '\n');
							SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
							for (size_t i = 0; i < 100; i++) cout << " ";
							flag = true;
						}
						else {
							flag = false;
							coord.X += size_tmpElem + 2;
						}
					} while (flag);
				}
			}
		}

		unsigned int Height() const { return rows; }

		unsigned int Width() const { return columns; }

		void DeleteRow(int pos = -1) {
			assert(pos >= -1 && pos <= rows - 1);
			if (pos == -1) pos = rows - 1;

			type** NewData = new type * [rows - 1];

			Initialize(NewData, rows - 1, columns);

			if (pos != 0) {
				for (size_t i = 0; i < pos; i++) {
					for (size_t j = 0; j < columns; j++)
						NewData[i][j] = data[i][j];
				}
			}

			for (size_t i = pos + 1, i_posNew = pos; i < rows; i++, i_posNew++) {
				for (size_t j = 0, j_posNew = 0; j < columns; j++, j_posNew++)
					NewData[i_posNew][j_posNew] = data[i][j];
			}

			Delete(data, rows);
			data = NewData;
			rows--;
		}

		void DeleteColumn(int pos =-1) {
			if (pos == -1) pos = columns - 1;
			assert(pos >= 0 && pos <= columns - 1);

			type** NewData;
			Initialize(NewData, rows, columns - 1);

			if (pos != 0) {
				for (size_t i = 0; i < rows; i++) {
					for (size_t j = 0; j < pos; j++)
						NewData[i][j] = data[i][j];
				}
			}

			for (size_t i = 0; i < rows; i++) {
				for (size_t j = pos + 1, j_NewData = pos; j < columns; j++, j_NewData++)
					NewData[i][j_NewData] = data[i][j];
			}

			Delete(data, rows);
			data = NewData;
			columns--;
	
		}

		void AddRow(type* elem, int pos = -1) {
			assert(pos >= -1 || pos < rows);
			if (pos == -1) pos = rows;

			type** NewData;
			Initialize(NewData, rows + 1, columns);


			for (size_t i = 0; i < pos; i++)
				for (size_t j = 0; j < columns; j++)
					NewData[i][j] = data[i][j];

			for (size_t i = 0; i < columns; i++)
				NewData[pos][i] = elem[i];

			for (size_t i = pos; i < rows; i++)
				for (size_t j = 0; j < columns; j++)
					NewData[i + 1][j] = data[i][j];


			Delete(data, rows);
			data = NewData;
			rows++;
		}

		void AddCol(type*& elem, int pos = -1) {
			assert(pos > 0 || pos < columns);

			if (pos != -1)
				pos = columns;

			type** NewData;
			Initialize(NewData, rows, columns + 1);

			for (size_t i = 0; i < rows; i++)
				for (size_t j = 0; j < pos; j++)
					NewData[i][j] = data[i][j];

			for (size_t i = 0; i < rows; i++)
				NewData[i][pos] = elem[i];


			for (size_t i = 0; i < rows; i++)
				for (size_t j_new = pos + 1, j_old = pos; j_old < columns; j_new++, j_old++)
					NewData[i][j_new] = data[i][j_old];


			Delete(data, rows);
			data = NewData;
			columns++;
			return true;
		}

		type MaxElem() {
			type res = data[0][0];
			for (size_t i = 0; i < rows; i++) {
				for (size_t j = 0; j < columns; j++) {
					if (data[i][j] > res)
						res = data[i][j];
				}
			}
			return res;
		}

		type MinElem() {
			type res = data[0][0];
			for (size_t i = 0; i < rows; i++) {
				for (size_t j = 0; j < columns; j++) {
					if (data[i][j] < res)
						res = data[i][j];
				}
			}
			return res;
		}

		void SortLineByLine() {
			for (size_t i = 0; i < rows; i++) {
				for (size_t j = 0; j < columns - 1; j++) {
					int min = j;
					for (size_t b = j + 1; b < columns; b++) {
						if (data[i][b] < data[i][min])
							min = b;
					}
					swap(data[i][j], data[i][min]);
				}
			}
		}

		void Sort() {
			for (size_t i_swap = 0; i_swap < rows; i_swap++) {
				for (size_t j_swap = 0; j_swap < columns; j_swap++) {
					int row_min = i_swap;
					int col_min = j_swap;
					for (size_t i = row_min; i < rows; i++) {
						if (i == row_min) {
							for (size_t j = col_min + 1; j < columns; j++) {
								if (data[i][j] < data[row_min][col_min]) {
									row_min = i;
									col_min = j;
								}
							}
						}
						else {
							for (size_t j = 0; j < columns; j++) {
								if (data[i][j] < data[row_min][col_min]) {
									row_min = i;
									col_min = j;
								}
							}
						}
					}
					swap(data[i_swap][j_swap], data[row_min][col_min]);
				}

			}
		}
	};
};