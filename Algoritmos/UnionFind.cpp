#include<bits/stdc++.h>
using namespace std;

struct UnionFind{
	
	int n;
	vector<int> padre;
	vector<int> tamano;
	
	int findset(int u){
		if(u == padre[u]) return u;
		padre[u] = findset(padre[u]);
		return padre[u];
	}
	
	void joinsets(int u, int v){
		
		u = findset(u);
		v = findset(v);
		
		if(u == v) return;
		
		if(tamano[u]>=tamano[v]){
			padre[v] = u;
			tamano[u] += tamano[v];
		}
		else{
			padre[u] = v;
			tamano[v] += tamano[u];
		}
	
	return;
		
		return;
	}
	
public:
	
    UnionFind(int a){
        n = a;
        tamano.resize(n, 1);
        padre.resize(n);
        for(int i = 0; i<n; i++){
        	padre[i] = i;
		}
    }
	
	bool issameset(int a, int b){
		if(findset(a) == findset(b)){
			return true;
		}
		else{
			return false;
		}
	}
	
	int setsize(int a){
		return tamano[findset(a)];
	}
};
