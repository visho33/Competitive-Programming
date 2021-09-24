#include<bits/stdc++.h>
using namespace std;

int main(){
	
	int v, e;
	int inicio, fin;
	cin>>v>>e;
	cin>>inicio>>fin;
	vector<vector<int> > edges(v+1, vector<int>(0));
	vector<int> peso (v+1, -1);
	for(int i = 0; i<e; i++){
		int a, b;
		cin>>a>>b;
		edges[a].push_back(b);
		edges[b].push_back(a);
	}
	
	queue<int> q;
	peso[inicio] = 0;
	q.push(inicio);
	
	while(q.size()!=0){
		int nodo = q.front();
		q.pop();
		
		for(int i = 0; i<edges[nodo].size();i++){
			
			if(peso[edges[nodo][i]]==-1){
				peso[edges[nodo][i]] = peso[nodo] + 1;
				q.push(edges[nodo][i]);
			}
			
		}
		
	}
	
	cout<<peso[fin];
	
	return 0;
}
