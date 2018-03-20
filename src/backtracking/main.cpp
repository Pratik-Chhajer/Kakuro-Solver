#include "input_functions.h"
#include "backtrack.h"
#include "helper.h"
#include <iostream>
using namespace std;

int main(int argc,char **argv){
	int rows, columns;
	int **H, **V, **F;
	bool **T;
	input(argv[1],rows,columns,&H,&V,&F,&T);
	backtrack(H,V,F,T,rows,columns);
	printBoard(F,rows,columns);
	return 0;
}