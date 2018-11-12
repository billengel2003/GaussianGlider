#include "directgroup.h"

DirectGroup::DirectGroup(const size_t size, const size_t D): wordlist_size(size), depth(D){
    // Set up vectors so that they don't have to resize through program.
    main_listX.resize(wordlist_size);
    FamilyX.resize(wordlist_size);
}
void DirectGroup::Process(std::vector<std::string> &WordsX){
    // Calculate R for each GroupT then set withn main_listX.
    std::cout<<"PROCESSING..."<<std::endl;
    const size_t size(WordsX.size());
    for(size_t n = 0; n < size - 2; ++n){
        for(size_t k = n + 1; ((k - n) < depth && k < size); ++k){
            GroupT g(WordsX[n], WordsX[k], (depth - (k-n)), wordlist_size);
            Set(g);
        }
    }
}
void DirectGroup::Set(GroupT &group){
    // Place within main_listX two words with their corresponding relationship value.
    const size_t size(main_listX[group.hash_C].size());
    for(size_t n = 0; n < size; ++n){
        if(main_listX[group.hash_C][n] == group){
            main_listX[group.hash_C][n].R += group.R;
            return;
        }
    }
    main_listX[group.hash_C].push_back(group);
    FamilyX[group.hash_0].push_back(group.hash_C);
    FamilyX[group.hash_1].push_back(group.hash_C);
}
void DirectGroup::TakeInHTML(const char * url_text){
    // Gather usable words as are found in HTML text.
    std::vector<std::string> WordsX;
    std::string s_main(WordUse::ToUpper(url_text)); //Use constructor to create usable string.
    bool inTag(false);
    std::string tag, text;
    for(size_t n = 0; n < s_main.size(); ++n)
    {
        if(s_main[n] == '<'){
            if(text.size() > 2){
                if(WordUse::Good(text)){
                    WordsX.push_back(text);
                }
            }
            text.clear();
            tag.clear();
            text += ' ';
            inTag = true;
        }
        else if(inTag && s_main[n] != '>'){
            tag += s_main[n];
        }
        if(s_main[n] == '>'){
            inTag = false;
        }
        if(!inTag){
            if(s_main[n] > 64 && s_main[n] < 91){
                text += s_main[n];
            }
            else if(s_main[n] > 96 && s_main[n] < 123){
                text += (s_main[n] - 32);
            }
            else if(text.size() > 1){
                if(WordUse::Good(text)){
                    WordsX.push_back(text);
                }
                text.clear();
            }
            else{
                text.clear();
            }
        }
    }
    Process(WordsX);
    Forget();
}
void DirectGroup::TakeInText(std::string &s_main){
    const size_t size(s_main.size());
    WordUse::ToUpper(s_main);
    std::string word;
    std::vector<std::string> WordsX;
    for(size_t n = 0; n < size; ++n){
        if(s_main[n] > 64 && s_main[n] < 91){
            // If ascii values within capital letters keep for word
            word += s_main[n];
            if(n == size - 1){
                if(WordUse::Good(word)){
                    WordsX.push_back(word);
                }
                word.clear();
            }
        }
        else if(word.size() > 1){
            // Only take words with multiple letters and which are not too common
            if(WordUse::Good(word)){
                WordsX.push_back(word);
            }
            word.clear();
        }
        else{
            word.clear();
        }
        // Don't clear here; needs to propogate.
    }
    Process(WordsX);
    Forget();
}
void DirectGroup::MyFamily(const char * c_sArg, const size_t greater_than){
    std::string sArg(WordUse::ToUpper(c_sArg));

    // Gather hash index values in FamilyX.
    // Look at each hash index within main_listX through conflict pairs for matching strings.
    const size_t hash_index(Hash::HashMe(sArg, wordlist_size));
    const size_t size_f(FamilyX[hash_index].size());
    for(size_t m = 0; m < size_f; ++m){
        for(size_t k = 0; k < main_listX[FamilyX[hash_index][m]].size(); ++k){
            if(main_listX[FamilyX[hash_index][m]][k].Ks == sArg &&
                    main_listX[FamilyX[hash_index][m]][k].R > greater_than){

                std::cout<<main_listX[FamilyX[hash_index][m]][k].Ws<<'\t'<<main_listX[FamilyX[hash_index][m]][k].R<<'\t'<<std::endl;

            } else if(main_listX[FamilyX[hash_index][m]][k].Ws == sArg &&
                      main_listX[FamilyX[hash_index][m]][k].R > greater_than) {

                std::cout<<main_listX[FamilyX[hash_index][m]][k].Ks<<'\t'<<main_listX[FamilyX[hash_index][m]][k].R<<'\t'<<std::endl;
            }
        }
    }
    /*
    const size_t size(main_listX.size());
    for(size_t n = 0; n < size; ++n){
        for(size_t m = 0; m < main_listX[n].size(); ++m){
            if(main_listX[n][m].Ks == sArg && main_listX[n][m].R > greater_than){
                std::cout<<main_listX[n][m].Ws<<'\t'<<main_listX[n][m].R<<std::endl;
            } else if(main_listX[n][m].Ws == sArg && main_listX[n][m].R > greater_than){
                std::cout<<main_listX[n][m].Ks<<'\t'<<main_listX[n][m].R<<std::endl;
            }
        }
    }
    */
}

void DirectGroup::Forget(){
    // Start reducing R in GroupT each call.
    // If R is already == 1 erase GroupT from main_listX
    std::cout<<"FORGETTING..."<<std::endl;
    const size_t size(main_listX.size());
    for(size_t n = 0; n < size; ++n){
        for(size_t m = 0; m < main_listX[n].size(); ++m){
            if(main_listX[n][m].R > 1){
                main_listX[n][m].R -= 1;
            } else if(main_listX[n][m].R == 1){
                main_listX[n].erase(main_listX[n].begin()+m);
            }
        }
    }
}

DirectGroup::~DirectGroup(){
    std::cout<<"DESTROYED"<<std::endl;
}
