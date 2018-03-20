#include <iostream>
#include <algorithm>
#include <string>
#include <iterator>
#include "input_functions.h"
#include "helper.h"
#include "list"
using namespace std;

list<list<int> >ANS;

int map_init(int ****P,int **H,int rows,int columns){
	int ***M = new int**[rows];
	for(int i=0;i<rows;i++){
		M[i] = new int*[columns];
		for(int j=0;j<columns;j++)
			M[i][j] = new int[10];
	}
	*P = M;
	int c = 1;
	for(int i=0;i<rows;i++){
		for(int j=0;j<columns;j++){
			if(!H[i][j]){
				for(int k=1;k<=9;k++){
					M[i][j][k] = c++;
				}
			}
			else{
				for(int k=1;k<=9;k++){
					M[i][j][k] = 0;
				}
			}
		}
	}
	return c-1;
}

void at_least_one(int ***M,int rows,int columns){
	for(int i=0;i<rows;i++){
		for(int j=0;j<columns;j++){
			if(M[i][j][1]){
				// for(int k=1;k<=9;k++)
				// 	cout<<M[i][j][k]<<" ";
				// cout<<"\n";
				list<int> L;
				for(int k=1;k<=9;k++)
					L.push_back(M[i][j][k]);
				ANS.push_back(L);
			}
		}
	}
}

void exactly_one(int ***M,int rows,int columns){
	for(int i=0;i<rows;i++){
		for(int j=0;j<columns;j++){
			if(M[i][j][1]){
				for(int k=1;k<=9;k++){
					// for(int l=k+1;l<=9;l++){
					// 	cout<<-M[i][j][k]<<" "<<-M[i][j][l]<<"\n";
					// }
					for(int l=k+1;l<=9;l++){
						list<int> L;
						L.push_back(-M[i][j][k]);
						L.push_back(-M[i][j][l]);
						ANS.push_back(L);
					}
				}
			}
		}
	}
}

// Function copied from: https://stackoverflow.com/questions/127704/algorithm-to-return-all-combinations-of-k-elements-from-n
template <typename Iterator>
bool next_combination(const Iterator first, Iterator k, const Iterator last){
	/* Credits: Mark Nelson http://marknelson.us */
	if((first == last) || (first == k) || (last == k))
		return false;
	Iterator i1 = first;
	Iterator i2 = last;
	++i1;
	if(last == i1)
		return false;
	i1 = last;
	--i1;
	i1 = k;
	--i2;
	while(first != i1){
		if(*--i1 < *i2){
			Iterator j = k;
			while (!(*i1 < *j)) ++j;
			iter_swap(i1,j);
			++i1;
			++j;
			i2 = k;
			rotate(i1,j,last);
			while (last != j){
				++j;
				++i2;
			}
			rotate(k,i2,last);
			return true;
		}
	}
	rotate(first,k,last);
	return false;
}

// void pratik(int n,int k){
// 	string s = "";
// 	for(int i=1;i<=n;i++)
// 		s += (i+'0');
//     size_t comb_size = k;
//     do
//     {
//         cout << string(s.begin(), s.begin() + comb_size) << endl;
//     } while (next_combination(s.begin(), s.begin() + comb_size, s.end()));
// }

void row_sum_helper(int ***M,int ro,int co,int count,int sum){
	
	if(count==1){
		list<int> L;
		L.push_back(M[ro][co][sum]);
		ANS.push_back(L);
	}

	string s = "";
	for(int i=1;i<=9;i++)
		s += (i+'0');
	size_t comb_size = count;
	do{
		string t = "";
		int c = 0;
		for(int i=0;i<comb_size;i++){
			t += s[i];
			c += (s[i]-'0');
		}
		if(c==sum){
			list<list<int> >temp;
			sort(t.begin(),t.end());
			do{
				list<int> l;
				for(int i=0;i<comb_size;i++)
					l.push_back(M[ro][co+i][t[i]-'0']);
				temp.push_back(l);
				// cout << sum<<" "<<t << endl;
			}
			while(next_permutation(t.begin(), t.end()));
			list<list<int> >::iterator itr_i,itr_j; 
			for(itr_i=temp.begin();itr_i!=temp.end();itr_i++){
				list<list<int> >::iterator itrN = itr_i;
				itrN++;
				for(itr_j=itrN;itr_j!=temp.end();itr_j++){
					// cout<<"here"<<endl;
					list<int>::iterator itr = (*itr_i).begin();
					list<int> P;
					while(itr!=(*itr_i).end()){
						P.push_back(-(*itr));
						// cout<<*itr<<" ";
						itr++;
					}
					itr = (*itr_j).begin();
					while(itr!=(*itr_j).end()){
						P.push_back(-(*itr));
						// cout<<*itr<<" ";
						itr++;
					}
					// cout<<endl;
					ANS.push_back(P);
				}
			}
		}
	}while(next_combination(s.begin(), s.begin() + comb_size, s.end()));
}

// void row_sum_helper(int ***M,int ro,int co,int count,int sum){
// 	string s = "";
// 	for(int i=1;i<=9;i++)
// 		s += (i+'0');
// 	size_t comb_size = count;
// 	do{
// 		string t = "";
// 		int c = 0;
// 		for(int i=0;i<comb_size;i++){
// 			t += s[i];
// 			c += (s[i]-'0');
// 		}
// 		if(c==sum){
// 			sort(t.begin(),t.end());
// 			while (next_permutation(t.begin(), t.end())){
// 				list<int> l;
// 				for(int i=0;i<comb_size;i++){
// 					l.push_back(M[ro][co+i][t[i]-'0']);
// 				}
// 				ANS.push_back(l);
// 				// cout << sum<<" "<<t << endl;
// 			}
// 		}
// 	}while(next_combination(s.begin(), s.begin() + comb_size, s.end()));
// }

void col_sum_helper(int ***M,int ro,int co,int count,int sum){
	
	if(count==1){
		list<int> L;
		L.push_back(M[ro][co][sum]);
		ANS.push_back(L);
	}

	string s = "";
	for(int i=1;i<=9;i++)
		s += (i+'0');
	size_t comb_size = count;
	do{
		string t = "";
		int c = 0;
		for(int i=0;i<comb_size;i++){
			t += s[i];
			c += (s[i]-'0');
		}
		if(c==sum){
			list<list<int> >temp;
			sort(t.begin(),t.end());
			do{
				list<int> l;
				for(int i=0;i<comb_size;i++)
					l.push_back(M[ro+i][co][t[i]-'0']);
				temp.push_back(l);
				// cout << sum<<" "<<t << endl;
			}
			while (next_permutation(t.begin(), t.end()));
			list<list<int> >::iterator itr_i,itr_j; 
			for(itr_i=temp.begin();itr_i!=temp.end();itr_i++){
				list<list<int> >::iterator itrN = itr_i;
				itrN++;
				for(itr_j=itrN;itr_j!=temp.end();itr_j++){
					list<int>::iterator itr = (*itr_i).begin();
					list<int> P;
					while(itr!=(*itr_i).end()){
						P.push_back(-(*itr));
						itr++;
					}
					itr = (*itr_j).begin();
					while(itr!=(*itr_j).end()){
						P.push_back(-(*itr));
						itr++;
					}
					ANS.push_back(P);
				}
			}
		}
	}while(next_combination(s.begin(), s.begin() + comb_size, s.end()));
} 

void row_sum_constraints(int ***M,int **H,int rows,int columns){
	int i,j,k,c,s;
	i = j = 0;
	while(i<rows){
		while(j<columns){
			if(H[i][j]){
				j++;
			}
			else{
				//cout<<i<<" "<<j<<endl;
				k = j;
				while(k+1<columns && !H[i][k+1]){
					k++;
				}
				row_sum_helper(M,i,j,k-j+1,H[i][j-1]);
				j = k+1;
			}
		}
		i++;
		j = 0;
	}
}

void col_sum_constraints(int ***M,int **V,int rows,int columns){
	int i,j,k,c,s;
	i = j = 0;
	while(j<columns){
		while(i<rows){
			if(V[i][j]){
				i++;
			}
			else{
				k = i;
				while(k+1<rows && !V[k+1][j]){
					k++;
				}
				col_sum_helper(M,i,j,k-i+1,V[i-1][j]);
				i = k+1;
			}
		}
		j++;
		i = 0;
	}
}

void writeList(int total_variables){
	list<list<int> >:: iterator i;
	list<int>:: iterator itr;
	int total = ANS.size();
	cout<<"p cnf "<<total_variables<<" "<<total<<endl;
	for(i=ANS.begin();i!=ANS.end();i++){
		itr = ((*i).begin());
		while(itr!=((*i).end())){
			cout<<*itr<<" ";
			itr++;
		}
		cout<<0<<"\n";
	}
}

int main(int argc,char **argv){
	int rows, columns;
	int **H, **V, **F;
	bool **T;
	input(argv[1],rows,columns,&H,&V,&F,&T);
	int ***M;
	int total_variables = map_init(&M,H,rows,columns);
	at_least_one(M,rows,columns);
	exactly_one(M,rows,columns);
	row_sum_constraints(M,H,rows,columns);
	col_sum_constraints(M,V,rows,columns);
	writeList(total_variables);
	return 0;
}