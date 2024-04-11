//============================================================================
// Name        : main.cpp
// Author      : Alex
// Version     :
//============================================================================
#include <iostream>
#include <fstream>
using namespace std;

/////////////////////////////////define/////////////////////////
#define SPACE 32//defining space number
#define ENDL 10//defining end of line number

const char* FNAME = "matrix.txt";
/////////////////prototypes///////////////////////////////
int** create_matrix(int *params);//creating matrix
int get_matrix_from_console(int *&param, int **matrix);//getting matrix from console
int get_params(int *&params);//gettting parametrs of the matrix from console
int get_matrix_from_file(const char* NAME, int *params, int** arr);//reading matrix from file
int check_params(const char* NAME, int *&params);//Checking the size of matrix in file
int multyply_elements_in_row(int** matrix, int* params,int currentr);//multyplying the elements from current row
void print_matrix(int** matrix, int* params);//print the matrix
int get_option();//asking user which method of entering string he prefers
void tasks(int* params, int **matrix);//solving tasks

int main() {
	int* params1 = new int[2];//size of matrix
	int** matrix;
	if (get_option() != 1)
	{
		cout << "Entering data from console" << endl;
		switch(get_params(params1)){//Asking the user to enter the size of matrix
		case -1:
			cout << "The number of rows must be a natural number!" << endl;
			return -1;
		default:
			break;
		}
		matrix = create_matrix(params1);//creating empty matrix with given size
		switch(get_matrix_from_console(params1,matrix)){
		case -1:
			cout << "Only digits must be entered!" << endl;
			return -1;
		default:
			break;
		}
	}
	else
	{
		cout << "Entering data from file" << endl;
		switch(check_params(FNAME,params1)){
		case -1:
			cout << "File " << FNAME << " is not found\n";
			return -1;
		case -2:
			cout << "File " << FNAME << " is empty\n";
			return -1;
		default:
			break;
		}
		matrix = create_matrix(params1);//creating empty matrix with given size
		switch(get_matrix_from_file(FNAME, params1,matrix)){
		case -1:
			cout << "Error! Only digits must be entered!" << endl;
			return -1;
		default:
			cout << "Reading ended!" << endl;
			break;
		}

	}
	print_matrix(matrix, params1);
	//------------------------------------------------------------------------------------------------------------------------------------------------------//
	//                                             1 and 2:  find multiply of rows with no "0" and max of these multiplies                                  //
	//------------------------------------------------------------------------------------------------------------------------------------------------------//
	tasks(params1,matrix);

	delete[] matrix;
}

///////////////////realization of functions///////////////////////////////////
void tasks(int* params, int **matrix){
	int max_mult = 0;
		for (int i = 0; i < params[0]; i++)
		{
			int mult = multyply_elements_in_row(matrix, params, i);
			if (mult)
			{
				cout << "Multiplying of elements in <" << i+1 << "> string equals <" << mult<<"> \n";
				if (mult > max_mult) {
					max_mult = mult;
				}
			}
		}
		cout << "Max multipluing is = " << max_mult << endl;
}
int** create_matrix(int *params) {//function gets the size of matrix
	int** result = new int* [params[0]];//making rows
	for (int i = 0; i < params[0]; i++) {//making columns
		result[i] = new int[params[1]];
	}
	return result;
}
int get_matrix_from_console(int *&param, int **matrix) {
	for (int i = 0; i < param[0]; ++i)//getting the matrix from console
	{
		for (int j = 0; j < param[1]; ++j) {
			cout << "Enter the element with index :(" << i+1 << "," << j+1 << ") :";
			cin >> matrix[i][j];
			if (cin.fail()) {
				return -1;
			}
		}
	}
	return 0;
}
int get_params(int *&params) {
	cout << "Enter amount of rows" << endl;
	cin >> params[0];
	cout << int(params[0]) << endl;
	if (params[0] <= 0 )
	{
		return -1;
	}
	cout << "Enter amount of columns" << endl;
	cin >> params[1];
	cout << params[1] << endl;
	if (params[1] <= 0)
	{
		return -1;
	}
	return 0;
}
int get_matrix_from_file(const char* NAME, int *params, int** matrix) {
	ifstream fin(NAME); //открываем файл
	for (int i = 0; i < params[0]; i++) //массива
	{
		for (int j = 0; j < params[1]; j++){ //чтение элементов
			fin >> matrix[i][j];
			if (fin.fail())
			{
				fin.close();
				return -1;
			}
		}
	}
	fin.close(); //закрываем файл
	return 0;
}
int check_params(const char* NAME, int *&params) {
	ifstream fin(NAME);//Определяем файл
	params[0] = 0;
	params[1] = 0;
	/////////EXISTANCE////////////////////////////////////////
	if (!fin)
	{
		fin.close();
		return -1;
	} // end if
	///////////NOT EMPTY//////////////////////////////////
	if (fin.eof()) 	//empty
	{
		fin.close();
		return -2;
	} // end if
	int countr = 0;
	int countc = 0;
	while (!fin.eof())
	{
		char buf = fin.get();
		if (int(buf) == SPACE) {
			countc++;
		}
		if (int(buf) == ENDL)
		{
			countr++;
			if (countc >= params[1])
			{
				params[1] = countc;
			}
			countc = 0;
		}
	}
	params[0] = countr + 1;
	params[1]++;
	fin.close();
	return 0;
}
int multyply_elements_in_row(int** matrix, int* params, int currentr) {
	int result = 1;
	for (int i = 0; i < params[1]; i++)
	{
		if (matrix[currentr][i] != 0) {
			result *= matrix[currentr][i];
		}
		else
		{
			return 0;
		}
	}
	return result;
}
void print_matrix(int** matrix, int* params) {
	cout << "\nGiven matrix is: \n";
	for (int i = 0; i < params[0]; i++)
	{
		for (int j = 0; j < params[1]; j++)
		{
			cout << matrix[i][j] << "\t";
		}
		cout << endl;
	}
}
int get_option() {
	int option;
	cin >> option;
	return option;
}
