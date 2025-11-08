#include<bits/stdc++.h>
using namespace std;

int main(){
	
	vector<string> s(4);
	cin>>s[0];
	cin>>s[1];
	cin>>s[2];
	cin>>s[3];
	
	int yes = 0;
	
		
	for(int i = 0; i<4; i++){
		if(s[i] == "H"){
			yes++;
			//cout<<"1";
			break;
		}
	}
	
	for(int i = 0; i<4; i++){
		if(s[i] == "2B"){
			yes++;
			//cout<<"2";
			break;
		}
	}
	for(int i = 0; i<4; i++){
		if(s[i] == "3B"){
			yes++;
			//cout<<"3";
			break;
		}
	}
	
	for(int i = 0; i<4; i++){
		if(s[i] == "HR"){
			yes++;
			break;
		}
	}
	
	//cout<<yes<<"\n";
	
	if(yes == 4){
		cout<<"Yes\n";
	}
	else{
		cout<<"No\n";
	}
	
	return 0;
}