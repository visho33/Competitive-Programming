#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#if defined(_WIN32) || defined(_WIN64)
#include <Windows.h>
#endif
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

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

int N, M, Q, L, W;
vector<int> G;
vector<int> lx, rx, ly, ry, X, Y;
vector<bool> listo;
vector<vector<int> > nodos;
vector<vector<ii> > aristas;

ll dis(int i, int j){
    return ((lx[i] + rx[i]) - (lx[j] + rx[j]))*((lx[i] + rx[i]) - (lx[j] + rx[j])) + ((ly[i] + ry[i]) - (ly[j] + ry[j]))*((ly[i] + ry[i]) - (ly[j] + ry[j]));;
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

void intentar(int i, int j){

    vector<int> disponible;

    for(auto u: nodos[i]){
        disponible.push_back(u);
        listo[u] = false;
    }

    for(auto u: nodos[j]){
        disponible.push_back(u);
        listo[u] = false;
    }

    random_shuffle(disponible.begin(), disponible.end());

    vector<int> bnodosi = nodos[i];
    vector<int> bnodosj = nodos[j];
    vector<ii> baristasi = aristas[i];
    vector<ii> baristasj = aristas[j];
    
    ll sumantes = 0;
    for(auto u: aristas[i]){
        sumantes += dis(u.first, u.second);
    }
    for(auto u: aristas[j]){
        sumantes += dis(u.first, u.second);
    }

    nodos[i].clear();
    nodos[j].clear();
    aristas[i].clear();
    aristas[j].clear();

    vector<int> voy = {i, j};
    vector<int> iniciox = {-1, -1};

    int maxi = -1;

    for(auto u: disponible){
        for(auto v: disponible){
            if(dis(u, v) > maxi){
                maxi = dis(u, v);
                iniciox[0] = u;
                iniciox[1] = v;
            }
        }
    }

    listo[iniciox[0]] = true;
    listo[iniciox[1]] = true;

    for(int r = 0; r<2; r++){
        int gx = voy[r];
        int g = G[gx];
        priority_queue<vector<ll>, vector<vector<ll> >, greater<vector<ll> > > q;
        int inicio = iniciox[r];
        nodos[gx].push_back(inicio);
        listo[inicio] = true;
        for(int i: disponible){
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
            for(int i: disponible){
                if(listo[i] == true) continue;
                q.push({dis(y, i), y, i});
            }
        }
    }

    ll sum = 0;
    for(auto u: aristas[i]){
        sum += dis(u.first, u.second);
    }
    for(auto u: aristas[j]){
        sum += dis(u.first, u.second);
    }

    if(sumantes < sum){
        nodos[i] = bnodosi;
        nodos[j] = bnodosj;
        aristas[i] = baristasi;
        aristas[j] = baristasj;
    }

    return;
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
    X.resize(N);
    Y.resize(N);

    for(int i = 0; i<N; i++){
        cin>>lx[i]>>rx[i]>>ly[i]>>ry[i];
    }

    for(int i = 0; i<N; i++){
        //cin>>X[i]>>Y[i];
    }

    listo.resize(N, false);
    nodos.resize(M);
    aristas.resize(M);

    for(int gx = 0; gx<M; gx++){
        int g = G[gx];
        priority_queue<vector<ll>, vector<vector<ll> >, greater<vector<ll> > > q;
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

    int intentos = 0;

    while(cpu_time() < 1.5){
        int i = rng()%M;
        int j = rng()%M;
        if(i == j) continue;
        intentar(i, j);
        intentos++;
    }

    cerr<<intentos<<endl;
    
    vector<int> cual(N);
    vector<set<ii> > graph(N);

    for(int i = 0; i<M; i++){
        for(auto u: nodos[i]){
            cual[u] = i;
        }
    }

    //agarrar una componente conexa que sea dijkstra vecinos con mas incertidumbre
    //while(Q > 0 && cpu_time() < 1.9){

    //Q = 100000;
    while(Q > 0){
        int i = rng()%N;
        int grupo = cual[i];

        vector<int> qnodos = {i};
        queue<int> q;
        q.push(i);
        vector<int> qaristas;
        set<int> visitados;
        visitados.insert(i);

        while(int(q.size()) > 0 && int(qnodos.size()) < L){
            int x = q.front();
            q.pop();
            for(int j = 0; j<int(aristas[grupo].size()); j++){
                if(int(qnodos.size()) == L) break;
                ii u = aristas[grupo][j];
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

        if(int(qnodos.size()) <= 2) continue;

        cout<<"? "<<qnodos.size()<<" ";
        for(auto u: qnodos){
            cout<<u<<" ";
        }
        cout<<endl;
        
        //vector<ii> res = query(qnodos);

        for(int j = 0; j < int(qaristas.size()); j++){
            cin>>aristas[grupo][qaristas[j]].first>>aristas[grupo][qaristas[j]].second;
            //aristas[grupo][qaristas[j]] = res[j];
        }
        Q--;
    }

    for(int i = 0; i<M; i++){
        //aristas[i] = query(nodos[i]);
    }

    double score = 0;
    double score2 = 0;

    cout<<"!"<<endl;

    for(int gx = 0; gx<M; gx++){
        for(auto u: nodos[gx]){
            cout<<u<<" ";
        }
        cout<<endl;
        for(auto u: aristas[gx]){
            cout<<u.first<<" "<<u.second<<endl; 
            score += dis2(u.first, u.second);
            score2 += dis3(u.first, u.second);
        }
    }

    cerr<<fixed<<setprecision(0)<<score<<" "<<score2<<endl;

    return 0;
}