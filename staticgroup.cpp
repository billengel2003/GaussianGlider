#include "staticgroup.h"

size_t Hash::HashMe(std::string &sArg, const size_t list_size){
    return (std::hash<std::string>{}(sArg)) % list_size; // C++11
}
std::string WordUse::ToUpper(std::string &sArg){
        const size_t size(sArg.size());
        for(size_t n = 0; n < size; ++n){
            if(sArg[n] < 123 && sArg[n] > 96){
                sArg[n] = sArg[n] - 32;
            }
        }
        return sArg;
    }
std::string WordUse::ToUpper(const char * sArg_c){
    std::string sArg(sArg_c);
    const size_t size(sArg.size());
    for(size_t n = 0; n < size; ++n){
        if(sArg[n] < 123 && sArg[n] > 96){
            sArg[n] = sArg[n] - 32;
        }
    }
    return sArg;
}
bool WordUse::Good(std::string &sArg){
    std::string arry[50];
    arry[0] = "WHO";
    arry[1] = "THE";
    arry[2] = "IT";
    arry[3] = "OR";
    arry[4] = "OF";
    arry[5] = "FOR";
    arry[6] = "IS";
    arry[7] = "AND";
    arry[8] = "IF";
    arry[9] = "BUT";
    arry[10] = "ITS";
    arry[11] = "THAN";
    arry[12] = "THEN";
    arry[13] = "BY";
    arry[14] = "TO";
    arry[15] = "IN";
    arry[16] = "DO";
    arry[17] = "HAS";
    arry[18] = "AN";
    arry[19] = "WITH";
    arry[20] = "THIS";
    arry[21] = "GOT";
    arry[22] = "AS";
    arry[23] = "THERE";
    arry[24] = "AT";
    arry[25] = "WHICH";
    arry[26] = "FROM";
    arry[27] = "ON";
    arry[28] = "ARE";
    arry[29] = "THAT";
    arry[30] = "ELSE";
    arry[31] = "";
    arry[32] = "WHAT";
    arry[33] = "SO";
    arry[34] = "BE";
    arry[35] = "WAS";
    arry[36] = "UNTO";
    arry[37] = "THEY";
    arry[38] = "THEIR";
    arry[39] = "THEM";
    arry[40] = "WHERE";
    arry[41] = "WHEN";
    arry[42] = "THY";
    arry[43] = "HAVE";
    arry[44] = "WERE";
    arry[45] = "ALSO";
    arry[46] = "WHILE";
    arry[47] = "BEEN";
    arry[48] = "WHEREFORE";
    arry[49] = "SHALL";


    for(size_t n = 0; n < 50; ++n){
        if(arry[n] == sArg){
            return false;
        }
    }
    return true;
}
