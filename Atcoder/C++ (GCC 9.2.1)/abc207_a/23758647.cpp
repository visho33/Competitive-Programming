#include<bits/stdc++.h>
using  namespace std;

int main(){
	
	int a, b, c;
	cin>>a>>b>>c;
	
	if(a <= b && a <=c){
		cout<<b+c<<"\n";
		return 0;
	}
	if(b <= a && b <=c){
		cout<<a+c<<"\n";
		return 0;
	}
	if(c <= a && c <=b){
		cout<<b+a<<"\n";
		return 0;
	}
	
	return 0;
}
