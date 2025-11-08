#include<bits/stdc++.h>
using namespace std;

int main(){
	
	int n, l;
	cin>>n>>l;
	
	vector<int> A(n);
	for(int i = 0; i<n; i++){
		cin>>A[i];
	}
	
	int i = 0;
	int pos = 1;
	while(pos < l){
		pos = pos + A[i] + 1;
		i++;
	}
	
	while(i < n){
		if(A[i] == 2){
			cout<<"No\n";
			return 0;
		}
		i++;
	}
	
	cout<<"Yes\n";
	
	return 0;
}