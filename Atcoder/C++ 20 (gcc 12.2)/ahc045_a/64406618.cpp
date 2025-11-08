#include<bits/stdc++.h>
using namespace std;
int N, M, Q, L, W;
vector<int> G;
vector<int> lx, rx, ly, ry;

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

    cout<<"!"<<endl;

    int j = 0;

    for(int i = 0; i<M; i++){
        for(int r = 0; r<G[i]; r++){
            cout<<j + r<<" ";
        }
        cout<<endl;
        for(int r = 0; r<G[i]-1; r++){
            cout<<j + r<<" "<<j+r+1<<endl;
        }
        j = j + G[i];
    }


    return 0;
}