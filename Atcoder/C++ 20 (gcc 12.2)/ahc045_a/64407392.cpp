#include<bits/stdc++.h>
using namespace std;
typedef pair<int, int> ii;
int N, M, Q, L, W;
vector<int> G;
vector<int> lx, rx, ly, ry;

int dis(int i, int j){
    return ((lx[i] + rx[i]) - (lx[j] + rx[j]))*((lx[i] + rx[i]) - (lx[j] + rx[j])) + ((ly[i] + ry[i]) - (ly[j] + ry[j]))*((ly[i] + ry[i]) - (ly[j] + ry[j]));;
}

struct UnionFind{
	
	int n;
	vector<int> padre;
	vector<int> tamano;
	
    UnionFind(int a){
        n = a;
        tamano.resize(n, 1);
        padre.resize(n);
        for(int i = 0; i<n; i++){
        	padre[i] = i;
		}
    }

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

int main(){

    cin>>N>>M>>Q>>L>>W;

    G.resize(M);

    for(int i = 0; i<M; i++){
        cin>>G[i];
    }

    lx.resize(N);
    rx.resize(N);
    ly.resize(N);
    ry.resize(N);

    for(int i = 0; i<N; i++){
        cin>>lx[i]>>rx[i]>>ly[i]>>ry[i];
    }

    vector<bool> listo(N, false);
    UnionFind uf(N);

    vector<vector<int> > nodos(M);
    vector<vector<ii> > aristas(M);

    for(int gx = 0; gx<M; gx++){
        int g = G[gx];
        priority_queue<vector<int>, vector<vector<int> >, greater<vector<int> > > q;
        int inicio = -1;
        for(int i = 0; i<N; i++){
            if(listo[i] == false){
                inicio = i;
                break;
            }
        }
        nodos[gx].push_back(inicio);
        listo[inicio] = true;
        for(int i = 0; i<N; i++){
            if(listo[i] == true) continue;
            q.push({dis(inicio, i), inicio, i});
        }

        while(q.size() > 0 && int(nodos[gx].size()) < g){
            int x = q.top()[1];
            int y = q.top()[2];
            q.pop();
            if(listo[y] == true) continue;
            nodos[gx].push_back(y);
            aristas[gx].push_back({x, y});
            listo[y] = true;
            for(int i = 0; i<N; i++){
                if(listo[i] == true) continue;
                q.push({dis(y, i), y, i});
            }
        }
    }

    /*for(int gx = 0; gx<M; gx++){
        if(G[gx] <= M && G[gx] >= 2){
            aristas[gx].clear();
            cout<<"? ";
            for(auto u: nodos[gx]){
                cout<<u<<" ";
            }
            cout<<endl;
            for(int i = 0; i<G[gx] - 1; i++){
                int x, y;
                cin>>x>>y;
                aristas[gx].push_back({x, y});
            }
        }
    }*/

    cout<<"!"<<endl;

    for(int gx = 0; gx<M; gx++){
        for(auto u: nodos[gx]){
            cout<<u<<" ";
        }
        cout<<endl;
        for(auto u: aristas[gx]){
            cout<<u.first<<" "<<u.second<<endl; 
        }
    }

    return 0;
}