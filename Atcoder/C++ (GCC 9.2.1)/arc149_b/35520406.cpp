#include<bits/stdc++.h>
using namespace std;

struct STmax{
	
	int n;
	vector<int> ST;
	
	int query(int node, int l, int r, int i, int j){
	
		if(i <= l && r <= j) return ST[node];

		if(j < l || r < i) return 0;
		
		return max(query(2*node, l, (l+r)/2, i, j), query(2*node+1, (l+r)/2+1, r, i, j));
		
	}
	
	void update(int node, int l, int r, int i, int x){

		if(l == r){
			ST[node] = x;
			return;
		}

		if(i < l || r < i) return;

		update(2*node, l, (l+r)/2, i, x);
		update(2*node+1, (l+r)/2+1, r, i, x);
		
		ST[node] = max(ST[2*node], ST[2*node + 1]);
		
		return;
	
	}
	
public:
	
    STmax(int nx){
        n = nx;
        ST.resize(4*n + 5, 0);
    }
    
    int query(int a, int b){
    	return query(1, 0, n-1, a, b);
	}
	
	void update(int a, int value){
        update(1, 0, n-1, a, value);
    	return;
	}
	
};

int lis(vector<int> A){
	
	int n = A.size();
	STmax st(n + 1);
	int maxi = 0;
	for(int i = 0; i<n; i++){
		int aux = st.query(1, A[i] - 1) + 1;
		maxi = max(maxi, aux);
		//cout<<i<<" "<<aux<<"\n";
		st.update(A[i], aux);
	}
	
	return maxi;
}

int main(){
	
	int n;
	cin>>n;
	
	vector<int> A(n);
	vector<int> B(n);
	vector<int> Ax(n);
	vector<int> Bx(n);
	
	for(int i = 0; i<n; i++){
		cin>>A[i];
	}
	//cout<<lis(A)<<"\n";
	for(int i = 0; i<n; i++){
		cin>>B[i];
	}
	
	for(int i = 0; i<n; i++){
		Ax[A[i] - 1] = B[i];
		Bx[B[i] - 1] = A[i];
	}
	
	int res = max(lis(Ax), lis(Bx));
	cout<<n+res<<"\n";
	
	return 0;
}