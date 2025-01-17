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

const char* FNAME = "Test1.txt";//defining text file name


//////////////////////////////Prototypes//////////////////////////////////////
void task1(char *&file,int &sze, int *&nl);//solving of the 1st task
void task2(char *&file,int &sze, int *&nl);//solving of the 2nd task
void resize_arr(char *&file, int &sz);//increasing array size by one
int get_option();//asking user which method of entering string he prefers
int read_file(const char* NAME, char *&file,int &sze, int *&nl);//reading data from file
int read_console(char *&file,int &sze, int *&nl);//getting data from console





//////////////////////////////MAIN/////////////////////////////////////////////
int main() {
	int sizem = 0;//current size of array that keeps the data
	char* arr = new char[sizem];//array that keeps the data
	int* newline = new int[2];//massive with indexes of ENDL symbols
	newline[0] = 0;
	newline[1] = 0;
	if (get_option() == 1)
	{
		switch (read_file(FNAME, arr,sizem,newline))//looking for fails in file
		{
		case -1:
			cout << "File " << FNAME << " is not found\n";
			return -1;
		case -2:
			cout << "File " << FNAME << " is empty\n";
			return -1;
		case -3:
			cout << "Too many strings! Only 3 must be included!" << endl;
			return -1;
		case -4:
			cout << "Only 1 word must be included in 1st string!" << endl;
			return -1;
		default:
			cout << "Reading ended!" << endl;
			break;
		}
	}
	else {
		switch(read_console(arr,sizem,newline)){//looking for fails in console data
		case -1:
			cout << "Only 1 word must be included in 1st string!" << endl;
			return -1;
		default:
			break;
		}
	}
	//------------------------------------------------------------------------------------------------------------------------------------------------------//
	//                                                  1 printing the information about same symbols in strings                                            //
	//------------------------------------------------------------------------------------------------------------------------------------------------------//
	task1(arr,sizem,newline);
	//------------------------------------------------------------------------------------------------------------------------------------------------------//
	//                                                  2 finding the string where the word meets more frequent                                             //
	//------------------------------------------------------------------------------------------------------------------------------------------------------//
	task2(arr,sizem,newline);

}//main


////////////////////////////////////////////realization of functions////////////////////////////
void task1(char *&file,int &sze, int *&nl){
	int st1[255];//index of each element equals the number of symbol from ASCII
	int st2[255];//index of each element equals the number of symbol from ASCII
	for(int i = 0; i < 255;i++){
		st1[i] = 0;
		st2[i] = 0;
	}
	for (int i = nl[0] + 1; i < nl[1]; i++)//counting symbols at first string
	{
		st1[int(file[i])]++;
	}
	for (int i = nl[1] + 1; i < sze; i++)//counting symbols at second string
	{
		st2[int(file[i])]++;
	}
	cout << endl << endl << "The answer for the first issue:" << endl;
	for (int i = 0; i < 255; i++)//printing the information about same symbols
	{
		if (st1[i] != 0 and st2[i] != 0) {
			int k;
			if (st1[i] < st2[i]) {
				k = st1[i];
			}
			else {
				k = st2[i];
			}
			cout << "Symbol <" << char(i) << "> repeats " << k << " times." << endl;
		}
	}
}
void task2(char *&file,int &sze, int *&nl){
	int wordInFirstStr = 0;//variable that counts how many times the word meets at 1st string
	int wordInSecondStr = 0;//variable that counts how many times the word meets at 2nd string
	int lenCounter = 0;//this variable counts how many symbols from first string program checked
	int wordlen = nl[0];//length of the word
	char* word = new char[wordlen];//the word itself
	if (wordlen == 0)//check whether no word is entered
	{
		cout << endl << "No word entered in first string" << endl;
		return;
	}
	for (int i = 0; i < wordlen; i++)//reading the word into special variable
	{
		word[i] = file[i];
	}

	for (int i = nl[0] + 1; i < nl[1]; i++)//finding the word at first string
	{
		if (file[i] == word[lenCounter]) {//one letter is found. Let's check next
			lenCounter++;
		}
		else//the letter is wrong, let's search the word again
		{
			lenCounter = 0;
		}
		if (lenCounter == wordlen) {//the whole word is found, keep searching
			wordInFirstStr++;
			lenCounter = 0;
		}
	}
	for (int i = nl[1] + 1; i < sze; i++)//finding the word at second string
	{
		if (file[i] == word[lenCounter]) {//one letter is found. Let's check next
			lenCounter++;
		}
		else//the letter is wrong, let's search the word again
		{
			lenCounter = 0;
		}
		if (lenCounter == wordlen) {//the whole word is found, keep searching
			wordInSecondStr++;
			lenCounter = 0;
		}
	}
	cout << endl << endl << "The answer for the second issue:" << endl;
	cout << "The word is: ";
	for (int i = 0; i < wordlen; i++)
	{
		cout << word[i];
	}
	cout << endl << "It meets " << wordInFirstStr << " times at first string!" << endl;
	cout << "It meets " << wordInSecondStr << " times at second string!" << endl;

	if (wordInFirstStr>wordInSecondStr)
	{
		cout << "Word meets more frequent at first string!" << endl;
	}else if (wordInSecondStr > wordInFirstStr)
	{
		cout << "Word meets more frequent at second string!" << endl;
	}
	else
	{
		cout << "Word meets more same times at both strings!" << endl;
	}
}
void resize_arr(char *&file, int &sz) {
	int newSize = sz + 1;
	char* newArr = new char[newSize];
	for(int i = 0; i < sz;++i){//rewriting data from old array to new
		newArr[i] = file[i];
	}
	sz = newSize;
	delete[] file;//175 - 176: changing old pointer to new data
	file = newArr;
}
int get_option() {
	int option;
	cin >> option;
	return option;
}
int read_file(const char* NAME, char *&file,int &sze, int *&nl) {
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
	if (fin.good())
	{
		while (!fin.eof()) {
			resize_arr(file,sze);
			file[sze - 1] = fin.get();//reading one symbol from .txt and entering it into array
			if (int(file[sze - 1]) == ENDL)
			{
				if (nl[0] == 0) {//end of line is found
					nl[0] = sze - 1;
				}
				else if (nl[1] == 0)//one more end of line is found
				{
					nl[1] = sze - 1;
				}
				else {//too many end of lines are found
					return -3;
				}
			}
			if (int(file[sze - 1]) == SPACE and nl[0] == 0) {//checking whether only one word is entered in first string
				return -4;
			}
		}
		fin.close();
	}
	return 0;
}
int read_console(char *&file,int &sze, int *&nl) {
	cin.sync();//cleaning the stream
	for (int i = 0; i < 3; i++)
	{
		int flag = 0;
		cout << "Enter " << i + 1 << " string." << endl;
		while (file[sze - 1] != '\n' or flag == 0) {
			flag = 1;
			resize_arr(file,sze);
			file[sze - 1] = cin.get();//reading one symbol from console and entering it into array

			if (int(file[sze - 1]) == SPACE and nl[0] == 0) {//checking whether only one word is entered in first string
				return -1;
			}
		}
		if (i == 0) {//end of line is found
			nl[0] = sze - 1;
		}
		else if (i == 1)//one more end of line is found
		{
			nl[1] = sze - 1;
		}
	}
	return 0;
}
