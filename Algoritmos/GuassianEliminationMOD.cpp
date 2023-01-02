#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

ll modular_inverse(ll a, ll MOD){
	ll x = 1, y = 0;
	ll x1 = 0, y1 = 1, a1 = a, b1 = MOD;
	while(b1){
		ll q = a1/b1;
		tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
	}
	return (x%MOD + MOD)%MOD;
}

int gauss(vector<vector<ll> > a, vector<ll> & ans, ll MOD){
    
	int n = a.size();
    int m = a[0].size() - 1;
    vector<int> where (m, -1);
    
    for(int col = 0, row = 0; col<m && row<n; col++){
        int sel = row;
        for(int i = row; i<n; i++){
        	if(a[i][col] != 0){
        		sel = i;
        		break;
			}
		}
        if(a[sel][col] == 0){
        	continue;
		}
        for(int i = col; i<=m; i++){
        	swap(a[sel][i], a[row][i]);
		}
        where[col] = row;
        for(int i = 0; i<n; i++){
        	if(i != row){
                ll c = (a[i][col]*modular_inverse(a[row][col], MOD))%MOD;
                for(int j = col; j<=m; j++){
                	a[i][j] = ((a[i][j] - a[row][j]*c)%MOD+MOD)%MOD;
				}
            }
        }
        row++;
    }

    ans.assign(m, 0);
    for(int i = 0; i<m; i++){
    	if(where[i] != -1){
    		ans[i] = (a[where[i]][m]*modular_inverse(a[where[i]][i], MOD))%MOD;
		}
	}
	
    for(int i = 0; i<n; i++){
        ll sum = 0;
        for(int j = 0; j<m; j++){
        	sum = (sum + ans[j]*a[i][j])%MOD;
		}
        if(sum != a[i][m]){
        	return 0; //no hay solucion
		}
    }

    for(int i = 0; i<m; i++){
    	if(where[i] == -1){
    		return 2; //infinitas soluciones
		}
	}
	
    return 1; //una solucion
}

int main(){
	
	vector<ll> ans(2);
	vector<vector<ll> > a(2, vector<ll>(3));
	a[0][0] = 1;
	a[0][1] = 3;
	a[0][2] = 2;
	a[1][0] = -2;
	a[1][1] = 4;
	a[1][2] = 0;
	int sol = gauss(a, ans, 1000000007);
	cout<<sol<<"\n";
	for(auto u: ans){
		cout<<u<<" ";
	}
	cout<<"\n";
	
	return 0;
}