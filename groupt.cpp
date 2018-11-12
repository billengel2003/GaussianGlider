#include "directgroup.h"

DirectGroup::GroupT::GroupT(){}
DirectGroup::GroupT::GroupT(std::string &sArg, std::string &sArg1,
                            const size_t rel, const size_t list_size):
    Ws(sArg), Ks(sArg1), R(rel){
    hash_0 = Hash::HashMe(sArg, list_size);
    hash_1 = Hash::HashMe(sArg1, list_size);
    if(sArg > sArg1){
        Cs = sArg + sArg1;
        hash_C = Hash::HashMe(Cs, list_size);
    } else if(sArg <= sArg1){
        Cs = sArg1 + sArg;
        hash_C = Hash::HashMe(Cs, list_size);
    }
}
//
bool DirectGroup::GroupT::operator==(GroupT &g){
    if(this->Ws == g.Ws && this->Ks == g.Ks){
        return true;
    } else if(this->Ws == g.Ks && this->Ks == g.Ws){
        return true;
    } else {
        return false;
    }
}
