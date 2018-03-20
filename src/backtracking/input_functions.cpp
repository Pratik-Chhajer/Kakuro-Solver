#include "input_functions.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

ifstream infile;

void input_rows_columns(int& rows, int& columns){
	int name_count = 0;
	int ans = 0;
	char c = 'p';
	while(c!='\n'){
		infile.get(c);
		if(c-'0'>=0 && c-'9'<=0)
			ans = ans*10 + c-'0';
		else if(c=='r')
			name_count = 1;
	}

	// 7 because r,o,w,s,=,\n
	if(name_count)
		rows = ans;
	else
		columns = ans;

	ans = 0;
	c = 'p';
	while(c!='\n'){
		infile.get(c);
		if(c-'0'>=0 && c-'9'<=0)
			ans = ans*10 + c-'0';
	}

	// 7 because r,o,w,s,=,\n
	if(!name_count)
		rows = ans;
	else
		columns = ans;
}

int read_number(){
	char c;
	infile.get(c);
	if(c=='#'){
		if(infile.good())
			infile.get(c);
		return -1;
	}
	int number = 0;
	while(c!=',' && c!='\n'){
		number = number*10 + c-'0';
		if(infile.good())
			infile.get(c);
		else
			break;
	}
	return number;
}

void input_horizontal_vertical(int rows,int columns,int ***P, int ***Q,int ***R, bool ***S){
	// Allocate space from heap
	// Dynamic memory allocation
	int **H;
	int **V;
	int **F;
	bool **T;
	H = new int*[rows];
	V = new int*[rows];
	F = new int*[rows];
	T = new bool*[rows];
	for(int i = 0;i < rows;++i){
		H[i] = new int[columns];
		V[i] = new int[columns];
		F[i] = new int[columns];
		T[i] = new bool[columns];
	}

	bool h = 0;

	char c;
	infile.get(c);
	if(c=='H')
		h = 1;
	while(c!='\n')
		infile.get(c);
	
	for(int i=0;i<rows;i++)
		for(int j=0;j<columns;j++)
			H[i][j] = read_number();

	c = 'p';
	while(c!='\n')
		infile.get(c);

	for(int i=0;i<rows;++i)
		for(int j=0;j<columns;j++)
			V[i][j] = read_number();

	for(int i=0;i<rows;i++){
		for(int j=0;j<columns;j++){
			F[i][j] = 0;
			if(H[i][j])
				T[i][j] = 1;
			else
				T[i][j] = 0;
		}
	}

	if(h){
		*P = H;
		*Q = V;
	}
	else{
		*P = V;
		*Q = H;
	}
	*R = F;
	*S = T;
}

void input(char FileName[],int& rows, int& columns,int ***H,int ***V,int ***F,bool ***T){
	// reading sample text file
	infile.open(FileName);

	if(!infile.good()){
		cout<<FileName<<" named file doesn't exists\n";
		return;
	}
	
	// number of rows and columns in Kakuro board
	input_rows_columns(rows,columns);

	// Horizontal and Vertical view of board
	input_horizontal_vertical(rows,columns,H,V,F,T);

}
