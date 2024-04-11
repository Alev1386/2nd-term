//============================================================================
// Name        : main.cpp
// Author      : Alex
// Version     :
//============================================================================
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

/////////////////////////////////define/////////////////////////
#define SPACE 32//defining space number
#define ENDL 10//defining end of line number
#define TAB 11//defining tabulation

const char* FNAME = "test.txt";

typedef struct {
    char mod[11];
    char num[6];
    int pas;
    double wg;
} plane;


int check_file(const char* NAME , int &nl);//reading data from file
void indexSort(plane arr[], int n, int *in);
void read_file(const char* NAME, int nl, plane arr[]);

int main(){
	setlocale(LC_ALL,"ru");
	int n = 0;
	switch(check_file(FNAME,n)){
	case -1:
		cout << "File " << FNAME << " is not found\n";
		return -1;
	case -2:
		cout << "File " << FNAME << " is empty\n";
		return -1;
	case -3:
		cout << "data is incorrect!" << endl;
		return -1;
	default:
		break;
	}
	plane* arr = new plane[n];
	int* B = new int[n];

	read_file(FNAME, n, arr);

	indexSort(arr,n, B);
	for(int i = n-1;i>=0;i--){
		cout<< arr[B[i]].mod;
		cout<<" ";
		cout<< arr[B[i]].num;
		cout<<" ";
		cout<< arr[B[i]].pas;
		cout<<" ";
		cout<< arr[B[i]].wg;
		cout<<endl;
	}




	return 0;
}
void read_file(const char* NAME, int nl, plane arr[]){
	ifstream fin(NAME);//open file
	for(int i = 0;i<nl;i++){
		fin >> arr[i].mod;
		fin >> arr[i].num;
		fin >> arr[i].pas;
		fin >> arr[i].wg;

	}
	fin.close();
}
int check_file(const char* NAME , int &nl) {
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
		int ctr = 0;
		char buf;
		while (!fin.eof()) {
			buf = fin.get();
			if(int(buf) == SPACE){
				ctr++;
			}
			if(int(buf) == ENDL and ctr == 3){
				nl++;
				ctr = 0;
			}
			else if(int(buf) == ENDL){
				fin.close();
				return -3;//data is incorrect
			}
		}

	}
	nl++;
	fin.close();
	return 0;
}


void indexSort(plane arr[], int n, int *in){
	int t = 0;
	for(int i = 0; i<n;i++){
		in[i] = i;
	}
	int a;
	int b;
	for (int i = 0; i < n - 1; i++) {
	        for (int j = i + 1; j < n; ++j) {
	        	a = 0;
	        	b = 0;
	        	for(int k = 2;k<6;k++){
	        		a += (int(arr[in[i]].num[k])-48) * pow(10,6-k);
	        		b += (int(arr[in[j]].num[k])-48) * pow(10,6-k);
	        	}
	            if (a < b) {
	                t = in[i];
	                in[i] = in[j];
	                in[j] = t;
	            }
	        }
	    }
}

