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

int N, M, Q, L, W;
vector<int> G;
vector<int> lx, rx, ly, ry;
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

    for(int gx: voy){
        int g = G[gx];
        priority_queue<vector<ll>, vector<vector<ll> >, greater<vector<ll> > > q;
        int inicio = -1;
        for(int i: disponible){
            if(listo[i] == false){
                inicio = i;
                break;
            }
        }
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

    while(cpu_time() < 1.7){
        int i = rng()%M;
        int j = rng()%M;
        if(i == j) continue;
        intentar(i, j);
    }
    //intentar();

    double score = 0;

    cout<<"!"<<endl;

    for(int gx = 0; gx<M; gx++){
        for(auto u: nodos[gx]){
            cout<<u<<" ";
        }
        cout<<endl;
        for(auto u: aristas[gx]){
            score += dis2(u.first, u.second);
            cout<<u.first<<" "<<u.second<<endl; 
        }
    }

    cerr<<score<<endl;

    return 0;
}