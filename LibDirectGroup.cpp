#include "directgroup.h"

//g++ -c -fPIC -std=c++11 main.cpp top.h overgroup.cpp smtptr.h undergroup.cpp ExternC.cpp
// g++ -shared -Wl,-soname,libfoo.so -o libfoo.so overgroup.o undergroup.o ExternC.o

extern "C"{
	DirectGroup * DirectGroup_New(const size_t size, const size_t D){		
		DirectGroup * DG = new DirectGroup(size, D); 
		return DG;
	}
	void TakeIn(DirectGroup * dg, const char * url_text){
		dg->TakeInHTML(url_text); 
	}
	void MyFamily(DirectGroup * dg, const char * child, const int greater_than){
		dg->MyFamily(child, greater_than); 
	}
	void End(DirectGroup * dg){
		delete dg;
	}
	void Forget(DirectGroup * dg){
		dg->Forget(); 	
	}
}

