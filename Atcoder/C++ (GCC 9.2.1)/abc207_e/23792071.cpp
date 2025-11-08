#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll MOD = 1000000007;

int main(){
	
	int n;
	cin>>n;
	
	vector<ll> lista(n+1);
	for(int i = 1; i<=n; i++){
		cin>>lista[i];
	}
	
	vector<vector<ll> > dp(n+1, vector<ll>(n+1, 0));
	
	for(int i = 1; i<=n; i++){
		dp[i][1] = 1;
	}
	
	for(int i = 2; i<=n; i++){
		vector<ll> resto(i, 0);
		ll sum = 0;
		for(int j = 1; j<=n; j++){
			sum = (sum + lista[j])%i;
			dp[j][i] = (dp[j][i] + resto[sum%i])%MOD;
			resto[sum%i] = (resto[sum%i] + dp[j][i-1])%MOD;
		}
	}
	
	ll res = 0;
	for(int i = 1; i<=n; i++){
		res = (res + dp[n][i])%MOD;
	}
	
	cout<<res<<"\n";
	
	return 0;
}
