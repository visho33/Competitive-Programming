#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

struct STmin{
	
	int n;
	vector<ll> A;
	vector<ll> ST;
	vector<ll> L;
	
	void build(int node, int l, int r){
		
		if(l==r){
			ST[node] = A[r];
			return;
		}
	
		build(2*node, l, (l+r)/2);
		build(2*node+1, (l+r)/2+1, r);
	
		ST[node] = min(ST[2*node], ST[2*node+1]);
		
		return;
	}
	
	ll query(int node, int l, int r, int i, int j){
	
		if(L[node] != 1e18){
			
			ST[node] = min(ST[node], L[node]);
			
			if(l != r){
				L[2*node] = min(L[2*node], L[node]);
				L[2*node+1] = min(L[2*node+1], L[node]);
			}

			L[node] = 1e18;
		}
		
		if(i <= l && r <= j) return ST[node];

		if(j < l || r < i) return 1000000000000000000;

		return min(query(2*node, l, (l+r)/2, i, j), query(2*node+1, (l+r)/2+1, r, i, j));
	
	}
	
	void fix_update(int node, int l, int r, int i, int j, ll x){
	
		if(L[node] != 1e18){
			ST[node] = min(ST[node], L[node]);
			
			if(l != r){
				L[2*node] = min(L[2*node], L[node]);
				L[2*node+1] = min(L[2*node + 1], L[node]);
			}

			L[node] = 1e18;
		}

		if(i <= l && r <= j){
			
			ST[node] = min(ST[node], x);

			if(l != r){
				L[2*node] = min(L[2*node], x);
				L[2*node+1] = min(L[2*node + 1], x);
			}

			return;
		}

		if(j < l || r < i) return;

		fix_update(2*node, l, (l+r)/2, i, j, x);
		fix_update(2*node+1, (l+r)/2+1, r, i, j, x);

		ST[node] = min(ST[2*node], ST[2*node+1]);
		
		return;
	
	}
	
public:
	
    STmin(vector<ll> v){
        A = v;
        n = v.size();
        ST.resize(4*n + 5);
        L.resize(4*n + 5, 1e18);
	build(1, 0, n-1);
    }

    ll query(int a, int b){
        return query(1, 0, n-1, a, b);
    }

    void fix_update(int a, int b, ll value){
        fix_update(1, 0, n-1, a, b, value);
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
		
	STmin st(A);
	
	while(q--){
		int t;
		cin>>t;
		
		if(t == 1){
			int a, b, c;
			cin>>a>>b>>c;
			st.fix_update(a, b, c);
		}
		else{
			int a, b;
			cin>>a>>b;
			cout<<st.query(a, b)<<"\n";
		}
	}
	
	return 0;
	
}
