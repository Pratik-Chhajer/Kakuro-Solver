#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "input_functions.h"
using namespace std;

void read_original_input(char FileName[],bool P[]){
	int rows, columns;
	int **H, **V, **F;
	bool **T;
	input(FileName,rows,columns,&H,&V,&F,&T);
	int c = 1;
	for(int i=0;i<rows;i++){
		for(int j=0;j<columns;j++){
			if(H[i][j])
				cout<<H[i][j]<<" ";
			else{
				for(int k=1;k<=9;k++){
					if(V[c+k]){
						cout<<k<<" ";
						break;
					}
				}
				c += 9;
			}
		}
		cout<<"\n";
	}
}

void read_output(char FileName[],bool **P){
	list<int> Temp;
	ifstream infile;
	infile.open(FileName);
	if(!infile.good()){
		cout<<FileName<<" named file doesn't exists\n";
		return;
	}
	string line;
	getline(infile,line);
	int x;
	while(1){
		infile >> x;
		cout<<x<<" ";
		Temp.push_back(x);
		if(!x)
			break;
	}
	infile.close();
	bool *V = new bool[Temp.size()+1];
	list<int>::iterator itr = Temp.begin();
	while(itr!=Temp.end()){
		if(*itr>0)
			V[*itr] = 1;
		else
			V[-(*itr)] = 0;
	}
	*P = V;
}

int main(){
	char A[] = "miniOutput.txt";
	char B[] = "input.txt";
	bool *P;
	read_output(A,&P);
	read_original_input(B,P);
	return 0;
}