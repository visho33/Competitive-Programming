#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll MOD = 1000000007;
vector<ll> mobius;

ll exp(ll a, ll b){
	
	ll aux = a;
	ll res = 1;
	for(ll i = 0; i<30; i++){
		if((b&(1<<i))!= 0){
			res = (res*aux)%MOD;
		}
		aux = (aux*aux)%MOD;
	}
	
	return res;
}

void compute(){
	ll n = mobius.size();
	vector<bool> isprime(n, true);
	for(ll i = 2; i<n; i++){
		if(isprime[i] == true){
			mobius[i] = -1;
			for(ll j = i*i; j<n; j = j*i){
				for(ll k = j; k<n; k = k + j){
					mobius[k] = 0;
				}
			}
			for(ll j = 2LL*i; j<n; j = j + i){
				mobius[j] = mobius[j]*-1;
				isprime[j] = false;
			}
		}
	}
}

int main(){
	
	ll n, k;
	cin>>n>>k;
	
	ll res = 0;
	
	mobius.resize(k+1, 1);
	compute();
	
	for(ll m = 1; m<=k; m++){
		
		ll multi = 0;
		for(ll d = 1; d <= k/m; d++){
			multi = (multi + mobius[d]*exp(k/(m*d), n))%MOD;
		}
		multi = (m*multi)%MOD;
		res = (res + multi)%MOD;
	}
	
	cout<<res<<"\n";
	
	return 0;
}