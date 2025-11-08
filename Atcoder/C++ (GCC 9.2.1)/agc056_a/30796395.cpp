#include<bits/stdc++.h>
using namespace std;

int main(){
	
	int t = 1;
	//cin>>t;
	
	while(t--){
		
		int n;
		cin>>n;
		vector<vector<char> > grilla(n, vector<char>(n, '.'));
		
		int act = 0;
		
		int index1 = -1;
		int index2 = -1;
		
		for(int i = 0; i<n; i++){
			grilla[i][act] = '#';
			grilla[i][(act+1)%n] = '#';
			grilla[i][(act+2)%n] = '#';
			act = (act+3)%n;
			if(act > (act+1)%n || act > (act+2)%n){
				if(index1 != -1){
					index2 = i;
				}
				else{
					index1 = i;
				}
			}
		}
		for(int i = 0; i<n; i++){
			for(int j = 0; j<n; j++){
				if(i == index1){
					cout<<grilla[index2-1][j];
				}
				if(i == index2-1){
					cout<<grilla[index1][j];
				}
				if(i != index1 && i != index2-1){
					cout<<grilla[i][j];
				}
			}
			cout<<"\n";
		}
		
		
	}
	
	return 0;
}