#ifndef STATICGROUP_H
#define STATICGROUP_H
#include <iostream>

class Hash
{
public:
    static size_t HashMe(std::string &sArg, const size_t list_size);
};

class WordUse
{
public:
    static std::string ToUpper(std::string &sArg);
    static std::string ToUpper(const char * sArg_c);
    static bool Good(std::string &sArg);
};



#endif // STATICGROUP_H
