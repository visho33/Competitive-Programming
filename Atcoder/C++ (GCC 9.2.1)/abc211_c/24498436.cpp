#include<bits/stdc++.h>
using namespace std;
typedef pair<char, int> ci;
typedef long long ll;

int main(){
	
	string s;
	cin>>s;
	
	map<char, int> mapa;
	mapa.insert(ci('c', 1));
	mapa.insert(ci('h', 2));
	mapa.insert(ci('o', 3));
	mapa.insert(ci('k', 4));
	mapa.insert(ci('u', 5));
	mapa.insert(ci('d', 6));
	mapa.insert(ci('a', 7));
	mapa.insert(ci('i', 8));
	
	vector<vector<ll> > ways(s.size(), vector<ll>(9, 0));
	for(int i = 0; i<s.size(); i++){
		ways[i][0] = 1;
	}
	
	if(s[0] == 'c'){
		ways[0][1] = 1;
	}
	
	for(int i = 1; i<s.size(); i++){
		int x = mapa[s[i]];
		if(x != 0){
			ways[i][x] = ways[i-1][x-1];
		}
		for(int j = 1; j<9; j++){
			ways[i][j] = (ways[i][j] + ways[i-1][j])%1000000007;
		}
	}
	
	
	cout<<ways[s.size() - 1][8]<<"\n";
	
	
	return 0;
}