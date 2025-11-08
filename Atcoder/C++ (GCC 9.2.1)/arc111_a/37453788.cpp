#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
	
	ll n, m;
	cin>>n>>m;
	
	vector<ll> pot(64, 1);
	pot[0] = 10;
	for(int i = 1; i<64; i++){
		pot[i] = (pot[i-1]*pot[i-1])%(m*m);
	}
	ll multi = 1;
	for(ll i = 0; i<64; i++){
		if((n&(1LL<<i)) != 0){
			multi = (multi*pot[i])%(m*m);
		}
	}

	cout<<(multi/m)%m<<"\n";
	
	return 0;
}