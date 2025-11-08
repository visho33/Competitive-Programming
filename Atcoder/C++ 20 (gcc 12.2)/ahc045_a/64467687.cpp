#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#endif
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
//mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng(33);

long double cpu_time() {
#if defined(_WIN32) || defined(_WIN64)
    FILETIME creation_ft, exit_ft, kernel_ft, user_ft;
    GetProcessTimes(GetCurrentProcess(), &creation_ft, &exit_ft, &kernel_ft, &user_ft);
     
    auto extract_time = [](FILETIME ft) {
        return 1e-7L * (ft.dwLowDateTime | uint64_t(ft.dwHighDateTime) << 32);
    };
     
    return extract_time(user_ft) + extract_time(kernel_ft);
#else
    return (long double) clock() / CLOCKS_PER_SEC;
#endif
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
};

int Q2 = 0;
int N, M, Q, L, W;
vector<int> G;
vector<int> lx, rx, ly, ry, X, Y;
vector<int> subtree;
vector<int> padre;
vector<int> color;
vector<bool> asignado;
vector<int> gruposize;
vector<vector<int> > nodosres;
vector<vector<ii> > aristasres;
vector<vector<int> > newaristas;
vector<ii> aristas;
vector<vector<ll> > distancia;
vector<vector<int> > disbfs;
vector<vector<int> > finalMST;
int tries = 100;

ll dis2(ll x1, ll y1, ll x2, ll y2){
    return (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
}

ll dis(int i, int j){
    return distancia[i][j];
}

double dis2(int i, int j){
    double x1 = (double(lx[i]) + double(rx[i]))/double(2);
    double x2 = (double(lx[j]) + double(rx[j]))/double(2);
    double y1 = (double(ly[i]) + double(ry[i]))/double(2);
    double y2 = (double(ly[j]) + double(ry[j]))/double(2);
    return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}

int dis3(int i, int j){
    return floor(sqrt((X[i] - X[j])*(X[i] - X[j]) + (Y[i] - Y[j])*(Y[i] - Y[j])));
}

vector<ii> query(vector<int> qnodos){

    int n = qnodos.size();

    vector<vector<int> > edges;

    for(int i = 0; i<n; i++){
        for(int j = i+1; j<n; j++){
            edges.push_back({dis3(qnodos[i], qnodos[j]), i, j});
        }
    }

    sort(edges.begin(), edges.end());

    vector<ii> res;

    UnionFind uf(n);

    for(auto u: edges){
        if(uf.issameset(u[1], u[2]) == false){
            res.push_back({qnodos[u[1]], qnodos[u[2]]});
            uf.joinsets(u[1], u[2]);
        }
    }

    return res;
}

int best(){

    vector<vector<int> > edges;

    for(int i = 0; i<N; i++){
        for(int j = i+1; j<N; j++){
            edges.push_back({dis3(i, j), i, j});
        }
    }

    sort(edges.begin(), edges.end());

    int res = 0;
    int puestos = 0;

    UnionFind uf(N);

    for(auto u: edges){
        if(uf.issameset(u[1], u[2]) == false){
            uf.joinsets(u[1], u[2]);
            res += u[0];
            puestos++;
        }
        if(puestos == N-M) break;
    }
    
    return res;
}

void mejorar(int i){
    
    vector<int> qnodos = {i};
    queue<int> q;
    q.push(i);
    vector<int> qaristas;
    set<int> visitados;
    visitados.insert(i);

    while(int(q.size()) > 0 && int(qnodos.size()) < L){
        int x = q.front();
        q.pop();
        for(int j = 0; j<int(aristas.size()); j++){
            if(int(qnodos.size()) == L) break;
            ii u = aristas[j];
            if(u.first == x && visitados.count(u.second) == 0){
                qnodos.push_back(u.second);
                qaristas.push_back(j);
                q.push(u.second);
                visitados.insert(u.second);
            }
            if(u.second == x && visitados.count(u.first) == 0){
                qnodos.push_back(u.first);
                qaristas.push_back(j);
                q.push(u.first);
                visitados.insert(u.first);
            }
        }
    }

    if(int(qnodos.size()) <= 2) return;

    cout<<"? "<<qnodos.size()<<" ";
    for(auto u: qnodos){
        cout<<u<<" ";
    }
    cout<<endl;
    

    //vector<ii> res = query(qnodos);

    for(int j = 0; j < int(qaristas.size()); j++){
        cin>>aristas[qaristas[j]].first>>aristas[qaristas[j]].second;
        //aristas[qaristas[j]] = res[j];
    }
}

void dfs(int v, int p){
    subtree[v] = 1;
    padre[v] = p;
    for(auto u: newaristas[v]){
        if(u == p || asignado[u] == true) continue;
        dfs(u, v);
        subtree[v] += subtree[u];
    }
}

void colorear(int v, int p, int c){
    color[v] = c;
    asignado[v] = true;
    for(auto u: newaristas[v]){
        if(u == p || asignado[u] == true) continue;
        colorear(u, v, c);
    }
}

int puntaje = 0;

void mejorarMST(){
    int i = rng()%N;
    int j = rng()%N;

    int nuevopuntaje = 0;
    swap(color[i], color[j]);

    UnionFind uf(N);

    for(auto u: finalMST){
        if(color[u[1]] == color[u[2]] && uf.issameset(u[1], u[2]) == false){
            aristasres[color[u[1]]].push_back({u[1], u[2]});
            uf.joinsets(u[1], u[2]);
            nuevopuntaje += u[0];
        }
    }

    if(nuevopuntaje > puntaje){
        swap(color[i], color[j]);
    }
    else{
        puntaje = nuevopuntaje;
    }

}

void computeres(){

    nodosres.clear();
    aristasres.clear();
    nodosres.resize(M);
    aristasres.resize(M);

    for(int i = 0; i<N; i++){
        nodosres[color[i]].push_back(i);
    }

    UnionFind uf(N);

    for(auto u: finalMST){
        if(color[u[1]] == color[u[2]] && uf.issameset(u[1], u[2]) == false){
            aristasres[color[u[1]]].push_back({u[1], u[2]});
            uf.joinsets(u[1], u[2]);
            puntaje += u[0];
        }
    }
}

void mejorargrupo(int i){
    
    int grupo = color[i];
    vector<int> qnodos = {i};
    queue<int> q;
    q.push(i);
    vector<int> qaristas;
    set<int> visitados;
    visitados.insert(i);

    while(int(q.size()) > 0 && int(qnodos.size()) < L){
        int x = q.front();
        q.pop();
        for(int j = 0; j<int(aristasres[grupo].size()); j++){
            if(int(qnodos.size()) == L) break;
            ii u = aristasres[grupo][j];
            if(u.first == x && visitados.count(u.second) == 0){
                qnodos.push_back(u.second);
                qaristas.push_back(j);
                q.push(u.second);
                visitados.insert(u.second);
            }
            if(u.second == x && visitados.count(u.first) == 0){
                qnodos.push_back(u.first);
                qaristas.push_back(j);
                q.push(u.first);
                visitados.insert(u.first);
            }
        }
    }

    if(int(qnodos.size()) <= 2) return;

    cout<<"? "<<qnodos.size()<<" ";
    for(auto u: qnodos){
        cout<<u<<" ";
    }
    cout<<endl;
    
    //vector<ii> res = query(qnodos);

    for(int j = 0; j < int(qaristas.size()); j++){
        cin>>aristasres[grupo][qaristas[j]].first>>aristasres[grupo][qaristas[j]].second;
        //aristasres[grupo][qaristas[j]] = res[j];
    }
}

int main(){

    cin>>N>>M>>Q>>L>>W;

    Q2 = Q - M;

    G.resize(M);

    for(int i = 0; i<M; i++){
        cin>>G[i];
    }

    lx.resize(N);
    rx.resize(N);
    ly.resize(N);
    ry.resize(N);
    X.resize(N);
    Y.resize(N);
    distancia.resize(N, vector<ll>(N, 0));

    ll totincert = 0;

    for(int i = 0; i<N; i++){
        cin>>lx[i]>>rx[i]>>ly[i]>>ry[i];
        totincert += ll(rx[i] - lx[i])*ll(ry[i] - ly[i]);
    }

    for(int i = 0; i<N; i++){
        //cin>>X[i]>>Y[i];
    }

    for(int i = 0; i<N; i++){
        for(int j = i+1; j<N; j++){
            ll xi = (rx[i] + lx[i]);
            ll yi = (ry[i] + ly[i]);
            ll xj = (rx[j] + lx[j]);
            ll yj = (ry[j] + ly[j]);
            distancia[i][j] += ll(floor(sqrt((xi - xj)*(xi - xj) + (yi - yj)*(yi - yj))));
            distancia[j][i] = distancia[i][j];
        }
    }

    vector<vector<ll> > aristasMST;

    for(int i = 0; i<N; i++){
        for(int j = i+1; j<N; j++){
            aristasMST.push_back({distancia[i][j], i, j});
        }
    }

    sort(aristasMST.begin(), aristasMST.end());

    UnionFind ufMST(N);

    for(auto u: aristasMST){
        if(ufMST.issameset(u[1], u[2]) == false){
            ufMST.joinsets(u[1], u[2]);
            aristas.push_back({u[1], u[2]});
        }
    }
    
    int score0 = 0;
    int score1 = 0;
    int score2 = 0;

    for(auto u: aristas){
        score0 += dis3(u.first, u.second);
    }

    for(int qx = 0; qx<Q - Q2; qx++){
        ll x = rng()%totincert + 1LL;
        ll sumincert = 0;
        for(int i = 0; i<N; i++){
            sumincert += ll(rx[i] - lx[i])*ll(ry[i] - ly[i]);
            if(x <= sumincert){
                mejorar(i);
                break;
            }
        }
    }

    for(auto u: aristas){
        score1 += dis3(u.first, u.second);
    }

    newaristas.resize(N);

    for(auto u: aristas){
        newaristas[u.first].push_back(u.second);
        newaristas[u.second].push_back(u.first);
    }

    asignado.resize(N, false);
    nodosres.resize(M);
    aristasres.resize(M);
    color.resize(N);
    gruposize.resize(M, 0);

    while(true){
        padre.clear();
        subtree.clear();
        padre.resize(N, -1);
        subtree.resize(N, -1);
        int inicio = -1;
        for(int i = 0; i<N; i++){
            if(asignado[i] == false){
                inicio = i;
                break;
            }
        }
        if(inicio == -1) break;
        dfs(inicio, -1);
        map<int, int> mapa;
        for(int i = 0; i<N; i++){
            if(subtree[i] == -1) continue;
            mapa[subtree[i]] = i;
        }
        int maxi = -1;
        int where = -1;
        for(int j = 0; j<M; j++){
            if(gruposize[j] != 0) continue;
            if(mapa.count(G[j]) != 0 && G[j] > maxi){
                maxi = G[j];
                where = j;
            }
        }
        if(maxi == -1) break;
        gruposize[where] = G[where];
        colorear(mapa[G[where]], padre[mapa[G[where]]], where);
    }

    for(int gx = 0; gx<M; gx++){
        if(gruposize[gx] != 0) continue;
        int inicio = -1;
        for(int i = 0; i<N; i++){
            if(asignado[i] == false){
                inicio = i;
                break;
            }
        }
        gruposize[gx] = 1;
        color[inicio] = gx;
        queue<int> q;
        vector<int> bfs(N, -1);
        q.push(inicio);
        asignado[inicio] = true;
        bfs[inicio] = 0;

        while(q.size() > 0){
            int nodo = q.front();
            q.pop();
            //cerr<<gx<<" "<<gruposize[gx]<<endl;
            for(auto u: newaristas[nodo]){
                if(gruposize[gx] == G[gx]) break;
                if(bfs[u] == -1){
                    q.push(u);
                    bfs[u] = bfs[nodo];
                    if(asignado[u] == false){
                        color[u] = gx;
                        gruposize[gx]++;
                        asignado[u] = true; 
                    }
                }
            }
            if(gruposize[gx] == G[gx]) break;
        }
        //cerr<<inicio<<" "<<G[gx]<<" "<<gruposize[gx]<<endl;
    }

    //cerr<<"hola"<<endl;

    for(int i = 0; i<N; i++){
        queue<int> q;
        vector<int> d(N, -1);
        d[i] = 0;
        q.push(i);
        while(q.size() > 0){
            int nodo = q.front();
            q.pop();
            for(auto u: newaristas[nodo]){
                if(d[u] == -1){
                    d[u] = d[nodo] + 1;
                    q.push(u);
                    if(i < u){
                        finalMST.push_back({d[u], i, u});
                    }
                }
            }
        }
    }
    
    sort(finalMST.begin(), finalMST.end());

    computeres();

    while(cpu_time() < 1.7){
        mejorarMST();
    }

    computeres();

    for(int xx = 0; xx<Q2; xx++){
        int i = rng()%N;
        mejorargrupo(i);
    }

    cout<<"!"<<endl;

    for(int gx = 0; gx<M; gx++){
        for(auto u: nodosres[gx]){
            cout<<u<<" ";
        }
        cout<<endl;
        for(auto u: aristasres[gx]){
            cout<<u.first<<" "<<u.second<<endl;
            score2 += dis3(u.first, u.second);
        }
    }

    cerr<<fixed<<setprecision(0)<<score2<<endl;
    //err<<fixed<<setprecision(3)<<cpu_time()<<endl;

    return 0;
}