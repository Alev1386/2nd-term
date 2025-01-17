//============================================================================
// Name        : main.cpp
// Author      : Alex
// Version     :
//============================================================================

#include <iostream>
#include <fstream>
using namespace std;
////////////////variables//////////////
//const int MAX_SIZE_A = 7;
//const int MAX_SIZE_B = 9;

const int MAX_SIZE_A = 2;
const int MAX_SIZE_B = 2;


const char* FNAME = "test.txt";

int matrix[MAX_SIZE_A][MAX_SIZE_B];
//////////////////////////////Prototypes//////////////////////////////////////
int multyply_elements_in_row(int a[MAX_SIZE_A][MAX_SIZE_B], int currentr);//multyplying the elements from current row
void print_matrix(int a[MAX_SIZE_A][MAX_SIZE_B]);//printing matrix in console
int read_console(int a[MAX_SIZE_A][MAX_SIZE_B]);//reading data from console
int read_file(int a[MAX_SIZE_A][MAX_SIZE_B], const char* NAME);//reading data from file
int get_option();//asking user which method of entering string he prefers
void tasks(int a[MAX_SIZE_A][MAX_SIZE_B]);//solving tasks

int main() {
	if (get_option() == 1)
	{
		switch(read_file(matrix,FNAME))
		{
		case -1:
			cout << "File " << FNAME << " is not found\n";
			return -1;
		case -2:
			cout << "File " << FNAME << " is empty\n";
			return -1;
		default:
			cout << "Reading ended!" << endl;
			break;
		}
	}
	else {
		switch(read_console(matrix))
				{
				case -1:
					cout << "Only digitst must be entered!\n";
					return -1;
				default:
					cout << "Reading ended!" << endl;
					break;
				}
	}
	//print_matrix(matrix);
	//------------------------------------------------------------------------------------------------------------------------------------------------------//
	//                                             1 and 2:  find multiply of rows with no "0" and max of these multiplies                                  //
	//------------------------------------------------------------------------------------------------------------------------------------------------------//
	tasks(matrix);


	return 0;
}
int multyply_elements_in_row(int a[MAX_SIZE_A][MAX_SIZE_B], int currentr){
	int result = 1;
	for (int i = 0; i < MAX_SIZE_B; i++)
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
void tasks(int a[MAX_SIZE_A][MAX_SIZE_B]){
	int max_mult = 0;
	for (int i = 0; i < MAX_SIZE_A; i++)
	{
		int mult = multyply_elements_in_row(matrix, i);
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
void print_matrix(int a[MAX_SIZE_A][MAX_SIZE_B]) {
	for (int i = 0; i < MAX_SIZE_A; i++)
	{
		for (int j = 0; j < MAX_SIZE_B; j++)
		{
			cout << matrix[i][j] << "\t";
		}
		cout << endl;
	}
}
int read_console(int a[MAX_SIZE_A][MAX_SIZE_B]){
	for (int i = 0; i < MAX_SIZE_A; i++)//getting digits one by one
	{
		for (int j = 0; j < MAX_SIZE_B; j++)
		{
			cin >> matrix[i][j];
			if(cin.fail()){
				return -1;
			}
		}
	}
	return 0;
}
int read_file(int a[MAX_SIZE_A][MAX_SIZE_B],const char* NAME) {
	//////////////////////////FILE///////////////////////////////////////
	ifstream fin(NAME);//open file

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

	/////////////////////////READ/////////////////////////
	for (int i = 0; i < MAX_SIZE_A; i++)//getting digits one by one
	{
		for (int j = 0; j < MAX_SIZE_B; j++)
		{
			fin >> a[i][j];
		}
	}
	fin.close();
	return 0;
}
int get_option() {
	int option;
	cin >> option;
	return option;
}
