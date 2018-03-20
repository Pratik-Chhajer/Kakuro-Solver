#include "helper.h"
#include <iostream>
using namespace std;

void printBoard(int **A,int n,int m){
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++)
			cout<<A[i][j]<<" ";
		cout<<endl;
	}
}