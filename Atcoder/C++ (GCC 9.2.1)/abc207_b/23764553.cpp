#include<bits/stdc++.h>
using  namespace std;

int main(){
	
	int a, b, c, d;
	cin>>a>>b>>c>>d;
	
	if(c*d <= b){
		cout<<"-1\n";
		return 0;
	}
	
	int p = a;
	int q = d*c-b;
	
	int k = p/q;
	if(p%q != 0){
		k++;
	}
	
	cout<<k<<"\n";
	
	return 0;
}
