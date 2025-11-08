#include<bits/stdc++.h>
using namespace std;

int main(){
	
	int n;
	cin>>n;
	
	vector<int> A(2*n);
	for(int i = 0; i<2*n; i++){
		cin>>A[i];
	}
	
	vector<int> res;
	
	for(int i = 1; i<2*n - 1; i = i + 2){
		if(A[i-1] > A[i] && A[i-1] > A[i+1]){
			res.push_back(i);
			swap(A[i-1], A[i]);
		}
		if(A[i] > A[i-1] && A[i] > A[i+1]){
			continue;
		}
		if(A[i+1] > A[i] && A[i+1] > A[i-1]){
			res.push_back(i+1);
			swap(A[i+1], A[i]);
		}
	}
	
	if(A[2*n - 2] > A[2*n - 1]){
		res.push_back(2*n - 1);
	}
	
	cout<<res.size()<<"\n";
	for(auto u: res){
		cout<<u<<" ";
	}
	cout<<"\n";
	
	
	return 0;
}