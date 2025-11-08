#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
	
	ll n, m;
	cin>>n>>m;
	
	vector<vector<ll> > dp(n+1, vector<ll>(10, 0));
	for(ll i = 1; i<=n; i++){
		for(ll j = 1; j<=9; j++){
			dp[i][j] = (10LL*dp[i-1][j] + j)%m;
		}
	}
	
	int nx = -1;
	int dx = -1;
	
	for(int i = n; i>0; i--){
		for(int j = 9; j>=1; j--){
			if(dp[i][j] == 0){
				nx = i;
				dx = j;
				i = -1;
				j = -1;
				break;
			}
		}
	}
	
	if(nx == -1){
		cout<<"-1\n";
		return 0;
	}
	
	string s = "";
	for(int i = 0; i<nx; i++){
		s.push_back('0' + dx);
	}
	
	cout<<s<<"\n";
	
	return 0;
}