#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int main(){
	
	int n, m;
	cin>>n>>m;
	
	vector<vector<int> > edges(n);
	vector<int> d(n, -1);
	for(int i = 0; i<m; i++){
		int a, b;
		cin>>a>>b;
		a--; b--;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	
	queue<int> q;
	queue<int> q2;
	d[0] = 0;
	q.push(0);
	q2.push(0);
	
	while(q.size()!=0){
		
		int nodo = q.front();
		q.pop();
		
		for(int i = 0; i<edges[nodo].size(); i++){
			if(d[edges[nodo][i]]==-1){
				d[edges[nodo][i]] = d[nodo] + 1;
				q.push(edges[nodo][i]);
				q2.push(edges[nodo][i]);
			}
		}
		
	}
	
	vector<ll> ways(n, 0);
	ways[0] = 1;
	
	
	while(q2.size() != 0){
		int nodo = q2.front();
		q2.pop();
		
		for(int i = 0; i<edges[nodo].size(); i++){
			if(d[edges[nodo][i]] == d[nodo] + 1){
				ways[edges[nodo][i]] = (ways[edges[nodo][i]] + ways[nodo])%1000000007;
			}
		}
		
	}
	
	cout<<ways[n-1]<<"\n";
	
	return 0;
}