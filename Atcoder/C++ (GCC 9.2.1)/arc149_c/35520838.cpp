#include<bits/stdc++.h>
using namespace std;

int main(){
	
	int n;
	cin>>n;
	
	vector<bool> isprime(2*n*n + 1, true);
	for(int i = 2; i<=2*n*n; i++){
		if(isprime[i] == false){
			continue;
		}
		for(int j = 2*i; j<=2*n*n; j = j + i){
			isprime[j] = false;
		}
	}
	
	if(n == 3){
		vector<int> A(9);
		vector<vector<int> > res(3, vector<int>(3));
		for(int i = 0; i<9; i++){
			A[i] = i + 1;
		}
		do{
			for(int i = 0; i<9; i++){
				res[i%3][i/3] = A[i];
			}
			bool nice = true;
			if(isprime[res[0][0] + res[0][1]] == true) nice = false;
			if(isprime[res[0][1] + res[0][2]] == true) nice = false;
			if(isprime[res[1][0] + res[1][1]] == true) nice = false;
			if(isprime[res[1][1] + res[1][2]] == true) nice = false;
			if(isprime[res[2][0] + res[2][1]] == true) nice = false;
			if(isprime[res[2][1] + res[2][2]] == true) nice = false;
			if(isprime[res[0][0] + res[1][0]] == true) nice = false;
			if(isprime[res[1][0] + res[2][0]] == true) nice = false;
			if(isprime[res[0][1] + res[1][1]] == true) nice = false;
			if(isprime[res[1][1] + res[2][1]] == true) nice = false;
			if(isprime[res[0][2] + res[1][2]] == true) nice = false;
			if(isprime[res[1][2] + res[2][2]] == true) nice = false;
			
			if(nice == true){
				break;
			}
			
			
		}while(next_permutation(A.begin(), A.end()));
		for(int i = 0; i<3; i++){
			for(int j = 0; j<3; j++){
				cout<<res[i][j]<<" ";
			}
			cout<<"\n";
		}
		return 0;
	}
	
	vector<vector<int> > res(n, vector<int>(n, 0));
	set<int> bolsa;
	for(int ix = 2; ix<=n*n; ix = ix + 2){
		bolsa.insert(ix);
	}
	
	int k = 1;
	int i = 0;
	int j = 0;
	while(k <= n*n){
		if(j == n){
			j = 0;
			i++;
		}
		res[i][j] = k;
		k = k + 2;
		j++;
	}
	
	while(i < n){
		if(j == n){
			j = 0;
			i++;
		}
		if(i == n){
			break;
		}
		int num = 0;
		for(auto u: bolsa){
			
			bool can = true;
			
			if(i > 0 && isprime[res[i-1][j] + u] == true){
				can = false;
			}
			if(i < n-1 && isprime[res[i+1][j] + u] == true){
				can = false;
			}
			if(j > 0 && isprime[res[i][j-1] + u] == true){
				can = false;
			}
			if(j < n-1 && isprime[res[i][j+1] + u] == true){
				can = false;
			}
			
			if(can == true){
				num = u;
				break;
			}
		}
		bolsa.erase(num);
		res[i][j] = num;
		j++;
	}
	
	for(int i = 0; i<n; i++){
		for(int j = 0; j<n; j++){
			cout<<res[i][j]<<" ";
		}
		cout<<"\n";
	}
	
	return 0;
}