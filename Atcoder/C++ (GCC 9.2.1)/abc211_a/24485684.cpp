#include<bits/stdc++.h>
using namespace std;

int main(){
	
	int a, b, c;
	cin>>a>>b;
	
	c = (a-b)/3 + b;
	
	cout<<c;
	
	if((a-b)%3 == 1){
		cout<<".333333333\n";
	}
	if((a-b)%3 == 2){
		cout<<".6666666666\n";
	}
	if((a-b)%3 == 0){
		cout<<"\n";
	}
	
	return 0;
}