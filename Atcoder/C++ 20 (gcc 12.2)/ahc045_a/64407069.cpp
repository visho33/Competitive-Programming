#include<bits/stdc++.h>
using namespace std;
typedef pair<int, int> ii;
int N, M, Q, L, W;
vector<int> G;
vector<int> lx, rx, ly, ry;

int dis(int i, int j){
    return ((lx[i] + rx[i]) - (lx[j] + rx[j]))*((lx[i] + rx[i]) - (lx[j] + rx[j])) + ((ly[i] + ry[i]) - (ly[j] + ry[j]))*((ly[i] + ry[i]) - (ly[j] + ry[j]));;
}

double dis2(int i, int j){
    double x1 = (double(lx[i]) + double(rx[i]))/double(2);
    double y1 = (double(ly[i]) + double(ry[i]))/double(2);
    double x2 = (double(lx[j]) + double(rx[j]))/double(2);
    double y2 = (double(lx[j]) + double(rx[j]))/double(2);
    return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
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

    //vector<vector<int> > edges;
    vector<bool> listo(N, false);

    //for(int i = 0; i<N; i++){
    //    for(int j = i+1; j<N; j++){
    //        edges.push_back({dis(i, j), i, j});
    //    }
    //}

    //sort(edges.begin(), edges.end());
    UnionFind uf(N);

    cout<<"!"<<endl;

    double score = 0;

    for(auto g: G){

        vector<int> nodos;
        vector<ii> aristas;
        priority_queue<vector<int>, vector<vector<int> >, greater<vector<int> > > q;
        int inicio = -1;
        for(int i = 0; i<N; i++){
            if(listo[i] == false){
                inicio = i;
                break;
            }
        }
        nodos.push_back(inicio);
        listo[inicio] = true;
        for(int i = 0; i<N; i++){
            if(listo[i] == true) continue;
            q.push({dis(inicio, i), inicio, i});
        }

        while(q.size() > 0 && int(nodos.size()) < g){
            int x = q.top()[1];
            int y = q.top()[2];
            q.pop();
            if(listo[y] == true) continue;
            nodos.push_back(y);
            aristas.push_back({x, y});
            listo[y] = true;
            for(int i = 0; i<N; i++){
                if(listo[i] == true) continue;
                q.push({dis(inicio, i), inicio, i});
            }
        }

        for(auto u: nodos){
            cout<<u<<" ";
        }
        cout<<endl;
        for(auto u: aristas){
            score = score + dis2(u.first, u.second);
            cout<<u.first<<" "<<u.second<<endl;
        }
    }

    //cerr<<fixed<<score<<endl;


    return 0;
}