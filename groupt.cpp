#include "directgroup.h"

DirectGroup::GroupT::GroupT(){}
DirectGroup::GroupT::GroupT(std::string &sArg, std::string &sArg1,
                            const size_t rel, const size_t list_size):
    Ws(sArg), Ks(sArg1), R(rel), Cs(sArg + sArg1),
    hash_0(Hash::HashMe(sArg, list_size)),
    hash_1(Hash::HashMe(sArg1, list_size)),
    hash_C(Hash::Con_HashMe(sArg, sArg1, list_size)) {}

//

bool DirectGroup::GroupT::operator==(GroupT &g){
    // Since a pair of strings can be represented uniquely with one value in constructor.
    if(g.hash_C == this->hash_C){
        if((this->Ws == g.Ws && this->Ks == g.Ks) ||
           (this->Ws == g.Ks && this->Ks == g.Ws) ){
            return true;
        }
    }
    return false;
}

void DirectGroup::GroupT::Print(std::ostream &out){
    if(Ws != "" && Ks != "" && R > 1){
        out<<hash_C;
        out<<'\t';
        out<<Ws;
        out<<'\t';
        out<<R;
        out<<'\t';
        out<<Ks;
        out<<std::endl;
    }
}

