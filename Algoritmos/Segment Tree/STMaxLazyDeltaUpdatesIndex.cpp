#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, int> li;

struct STmax{
	
	int n;
	vector<ll> A;
	vector<li> ST;
	vector<ll> L;
	li MIN = make_pair(-1000000000000000000, -1);
	
	void build(int node, int l, int r){
		
		if(l==r){
			ST[node].first = A[r];
			ST[node].second = r;
			return;
		}
	
		build(2*node, l, (l+r)/2);
		build(2*node+1, (l+r)/2+1, r);
		
		if(ST[2*node].first >= ST[2*node+1].first){
			ST[node] = ST[2*node];
		}
		else{
			ST[node] = ST[2*node + 1];
		}
		
		return;
	}
	
	li query(int node, int l, int r, int i, int j){
	
		if(L[node] != 0) {
			
			ST[node].first += L[node];
			
			if(l != r){
				L[2*node] += L[node];
				L[2*node+1] += L[node];
			}

			L[node] = 0;
		}
	
		if(i <= l && r <= j) return ST[node];

		if(j < l || r < i) return MIN;
		
		li query1 = query(2*node, l, (l+r)/2, i, j);
		li query2 = query(2*node+1, (l+r)/2+1, r, i, j);
		
		if(query1.first >= query2.first){
			return query1;
		}
		else{
			return query2;
		}
	}
	
	void update(int node, int l, int r, int i, int j, ll x){
	
		if(L[node] != 0) {
			ST[node].first += L[node];
			
			if(l != r){
				L[2*node] += L[node];
				L[2*node+1] += L[node];
			}

			L[node] = 0;
		}

		if(i <= l && r <= j){
			ST[node].first += x;

			if(l != r){
				L[2*node] += x;
				L[2*node+1] += x;
			}

			return;
		}

		if(j < l || r < i) return;

		update(2*node, l, (l+r)/2, i, j, x);
		update(2*node+1, (l+r)/2+1, r, i, j, x);
		
		if(ST[2*node].first >= ST[2*node + 1].first ){
			ST[node] = ST[2*node];
		}
		else{
			ST[node] = ST[2*node+1];
		}
		
		return;
	
	}
	
public:
	
    STmax(vector<ll> v){
        A = v;
        n = v.size();
        ST.resize(4*n + 5);
        L.resize(4*n + 5, 0);
	build(1, 0, n-1);
    }

    li query(int a, int b){
        return query(1, 0, n-1, a, b);
    }

    void update(int a, int b, ll value){
        update(1, 0, n-1, a, b, value);
    	return;
	}
	
};

int main(){
	
	int n, q;
	cin>>n>>q;
	
	vector<ll> A(n);
	for(int i = 0; i<n; i++){
		cin>>A[i];
	}
		
	STmax st(A);
	
	while(q--){
		int t;
		cin>>t;
		
		if(t == 1){
			int a, b, c;
			cin>>a>>b>>c;
			st.update(a, b, c);
		}
		else{
			int a, b;
			cin>>a>>b;
			li res = st.query(a, b);
			cout<<res.first<<" "<<res.second<<"\n";
		}
	}
	
	return 0;
}
