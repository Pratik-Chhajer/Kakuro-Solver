#include "backtrack.h"
#include "helper.h"
#include <iostream>
#include <utility>
using namespace std;

pair<int,int> firstUnAssigned(int rows, int columns,bool **T){
	for(int i=0;i<rows;i++){
		for(int j=0;j<columns;j++){
			if(!T[i][j]){
				return make_pair(i,j);
			}
		}
	}
	return make_pair(-1,-1);
}

bool conflicts_in_row(int **F,int **H,int rows,int columns,int r,int c,int i){
	int start = c;
	while( ((start-1)>=0) && H[r][start-1]==0)
		start--;
	int end = c;
	while( ((end+1) < columns) && H[r][end+1]==0)
		end++;
	for(int j=start;j<=end;j++)
		if(F[r][j]==i)
			return true;
	return false;
}

bool conflicts_in_col(int **F,int **V,int rows,int columns,int r,int c,int i){
	int start = r;
	while( ((start-1)>=0) && V[start-1][c]==0)
		start--;
	int end = r;
	while( ((end+1) < rows) && V[end+1][c]==0)
		end++;
	for(int j=start;j<=end;j++)
		if(F[j][c]==i)
			return true;
	return false;
}

bool h_sum_conflict(int **F,int **H,int columns,int row,int col,int i){
	int start = col;
	while( ((start-1)>=0) && H[row][start-1]==0)
		start--;
	int end = col;
	while( ((end+1) < columns) && H[row][end+1]==0)
		end++;
	int required = H[row][start-1];
	int count_of_zeros = 0;
	bool Found[10];
	for(int j=0;j<=9;j++)
		Found[j] = 0;
	for(int j=start;j<=end;j++){
		Found[F[row][j]] = 1;
		if(!F[row][j])
			count_of_zeros++;
		else
			required -= F[row][j];
	}
	if(count_of_zeros==1)
		return (required!=i);
	else{
		int total = count_of_zeros-1;
		int c = 0;
		int minn = 0;
		for(int j=1;j<=9;j++){
			if(c<total && !Found[j] && i!=j){
				c++;
				minn += j;
			}
		}
		int maxx = 0;
		c = 0;
		for(int j=9;j>=1;j--){
			if(c<total && !Found[j] && i!=j){
				c++;
				maxx += j;
			}
		}
		if( (required - i >= minn) && (required - i<=maxx) )
			return 0;
		return 1;
	}
}

bool v_sum_conflict(int **F,int **V,int rows,int row,int col,int i){
	int start = row;
	while( ((start-1)>=0) && V[start-1][col]==0)
		start--;
	int end = row;
	while( ((end+1) < rows) && V[end+1][col]==0)
		end++;
	int required = V[start-1][col];
	int count_of_zeros = 0;
	bool Found[10];
	for(int j=0;j<=9;j++)
		Found[j] = 0;
	for(int j=start;j<=end;j++){
		Found[F[j][col]] = 1;
		if(!F[j][col])
			count_of_zeros++;
		else
			required -= F[j][col];
	}
	if(count_of_zeros==1)
		return (required!=i);
	else{
		int total = count_of_zeros-1;
		int c = 0;
		int minn = 0;
		for(int j=1;j<=9;j++){
			if(c<total && !Found[j] && i!=j){
				c++;
				minn += j;
			}
		}
		int maxx = 0;
		c = 0;
		for(int j=9;j>=1;j--){
			if(c<total && !Found[j] && i!=j){
				c++;
				maxx += j;
			}
		}
		if( (required - i >= minn) && (required - i<=maxx) )
			return 0;
		return 1;
	}
}

bool backtrack(int **H,int **V,int **F,bool **T,int rows,int columns){
	int r,c;
	pair<int,int> temp = firstUnAssigned(rows,columns,T);
	if(temp.first==-1)
		return true;
	r = temp.first;
	c = temp.second;
	for(int i=1;i<=9;i++){
		bool P = conflicts_in_row(F,H,rows,columns,r,c,i);
		bool Q = conflicts_in_col(F,V,rows,columns,r,c,i);
		bool R = h_sum_conflict(F,H,columns,r,c,i);
		bool S = v_sum_conflict(F,V,rows,r,c,i);
		if(!(P || Q || R || S)){
			F[r][c] = i;
			T[r][c] = 1;
			if(backtrack(H,V,F,T,rows,columns)){
				return true;
			}
			F[r][c] = 0;
			T[r][c] = 0;	
		}
	}
	return false;
}