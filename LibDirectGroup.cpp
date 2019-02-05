#include "directgroup.h"

//g++ -c -fPIC -std=c++11 directgroup.h staticgroup.h smtptr.h directgroup.cpp staticgroup.cpp LibDirectGroup.cpp
 //g++ -shared -Wl,-soname,libfoo.so -o libfoo.so directgroup.o groupt.o LibDirectGroup.o staticgroup.o

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
	void MyR(DirectGroup * dg, const char * sArg, const char * sArg1){
		std::cout<<sArg<<'\t'<<dg->OurR(sArg, sArg)<<'\t'<<sArg1<<std::endl; 
	}
	void End(DirectGroup * dg){
		delete dg;
	}
	void Forget(DirectGroup * dg){
		dg->Forget();
	}
}

