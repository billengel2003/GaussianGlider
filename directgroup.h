#ifndef DIRECTGROUP_H
#define DIRECTGROUP_H
#include "staticgroup.h"
#include <vector>

class DirectGroup
{
private:
    class GroupT{
    private:
    public:
        std::string Ws; // Word0
        std::string Ks; // Word1
        std::string Cs; // Word0 + Word1 concatenation
        size_t R; // Relationship between words
        size_t hash_C; // Concatenation hash with greater first
        size_t hash_0;
        size_t hash_1;
        //
        GroupT(); // In vector's constructor.
        GroupT(std::string &sArg, std::string &sArg1, const size_t rel, const size_t list_size);
        //
        bool operator==(GroupT &g);
    };
    std::vector<std::vector<GroupT>> main_listX; // Holds all data from process.
    std::vector<std::vector<size_t>> FamilyX; // Used to look for individual words
    const size_t wordlist_size;
    const size_t depth;
    //
    DirectGroup(const DirectGroup & right); // Don't allow copies
    void Process(std::vector<std::string> &WordsX);
    void Set(GroupT &group); //Place groupT into main_listX
public:
    explicit DirectGroup(const size_t size, const size_t D);
    void TakeInText(std::string &s_main);
    void TakeInHTML(const char * sArg); // Python sends (char *)
    void MyFamily(const char * sArg, const size_t greater_than); //Python sends (char *) no string
    void Forget();
    ~DirectGroup();
};


#endif // DIRECTGROUP_H
