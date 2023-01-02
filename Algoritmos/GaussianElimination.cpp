#include<bits/stdc++.h>
using namespace std;
const double EPS = 1e-9;

int gauss(vector<vector<double> > a, vector<double> & ans){
    
	int n = a.size();
    int m = a[0].size() - 1;
    vector<int> where (m, -1);
    
    for(int col = 0, row = 0; col<m && row<n; col++){
        int sel = row;
        for(int i = row; i<n; i++){
        	if(abs (a[i][col]) > abs (a[sel][col])){
        		sel = i;
			}
		}
        if(abs(a[sel][col]) < EPS){
        	continue;
		}
        for(int i = col; i<=m; i++){
        	swap(a[sel][i], a[row][i]);
		}
        where[col] = row;
        for(int i = 0; i<n; i++){
        	if(i != row){
                double c = a[i][col]/a[row][col];
                for(int j = col; j<=m; j++){
                	a[i][j] = a[i][j] - a[row][j]*c;
				}
            }
        }
        row++;
    }

    ans.assign(m, 0);
    for(int i = 0; i<m; i++){
    	if(where[i] != -1){
    		ans[i] = a[where[i]][m]/a[where[i]][i];
		}
	}
	
    for(int i = 0; i<n; i++){
        double sum = 0;
        for(int j = 0; j<m; j++){
        	sum = sum + ans[j]*a[i][j];
		}
        if(abs(sum - a[i][m]) > EPS){
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
	
	vector<double> ans(2);
	vector<vector<double> > a(2, vector<double>(3));
	a[0][0] = 1;
	a[0][1] = 3;
	a[0][2] = 2;
	a[1][0] = -2;
	a[1][1] = 4;
	a[1][2] = 0;
	int sol = gauss(a, ans);
	cout<<sol<<"\n";
	for(auto u: ans){
		cout<<u<<" ";
	}
	cout<<"\n";
	
	return 0;
}