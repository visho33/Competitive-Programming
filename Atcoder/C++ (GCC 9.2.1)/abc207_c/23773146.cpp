#include<bits/stdc++.h>
using  namespace std;

int main(){
	
	int n;
	cin>>n;
	
	vector<vector<int> > lista(n, vector<int>(2));
	
	for(int i = 0; i<n; i++){
		int t;
		cin>>t>>lista[i][0]>>lista[i][1];
		lista[i][0] = lista[i][0]*2;
		lista[i][1] = lista[i][1]*2;
		if(t == 2){
			lista[i][1]--;
		}
		if(t == 3){
			lista[i][0]++;
		}
		if(t == 4){
			lista[i][0]++;
			lista[i][1]--;
		}
	}
	
	int res = 0;
	
	for(int i = 0; i<n; i++){
		for(int j = i+1; j<n; j++){
			res++;
			if(lista[i][1] < lista[j][0] || lista[i][0] > lista[j][1]){
				res--;
			}
		}
	}
	
	cout<<res<<"\n";
	
	return 0;
}
