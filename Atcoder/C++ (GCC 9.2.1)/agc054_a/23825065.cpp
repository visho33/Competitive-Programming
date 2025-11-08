#include<bits/stdc++.h>
using namespace std;

int main(){
	
	int n;
	string s;
	cin>>n;
	cin>>s;
	vector<int> dp(n+1, 100000000);
	vector<int> last(26, 100000000);
	dp[0] = 0;
	
	for(int i = 1; i<=n; i++){
		int c = s[i-1] - 'a';
		int mini = 100000000;
		for(int j = 0; j<26; j++){
			if(j == c) continue;
			mini = min(mini, last[j]);
		}
		dp[i] = min(dp[i], mini + 1);
		last[c] = min(last[c], dp[i-1]);
	}
	
	dp[n] == 100000000 ? cout<<"-1" : cout<<dp[n];
	cout<<"\n";
	
	return 0;
}
