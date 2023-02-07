#include<bits/stdc++.h>
using namespace std;

struct vishoset{
	
	set<int> A;
	
public:
		
	vishoset(){
		A.insert(-1000010000);
		A.insert(1000010000);
	}
	
	void agregar(int a){
		A.insert(a);
	}
	
	void sacar(int a){
		A.erase(a);
	}
	
	int mayor(int a){
		auto it = A.upper_bound(a);
		if(*it == 1000010000){
			return -1000010000;
		}
		else{
			return *it;
		}
	}
	
	int mayorigual(int a){
		auto it = A.lower_bound(a);
		if(*it == 1000010000){
			return -1000010000;
		}
		else{
			return *it;
		}
	}
	
	int menor(int a){
		auto it = A.lower_bound(a);
		it--;
		if(*it == -1000010000){
			return -1000010000;
		}
		else{
			return *it;
		}
	}
	
	int menorigual(int a){
		auto it = A.upper_bound(a);
		it--;
		if(*it == -1000010000){
			return -1000010000;
		}
		else{
			return *it;
		}
	}
	
};

int main(){
	
	vishoset A;
	A.agregar(0);
	A.agregar(1);
	A.agregar(3);
	A.agregar(4);
	
	
	return 0;
}