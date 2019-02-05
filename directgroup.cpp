#include "directgroup.h"

DirectGroup::DirectGroup(const size_t size, const size_t D): wordlist_size(size), depth(D){
    // Set up vectors so that they don't have to resize through program.
    main_listX.resize(wordlist_size);
    //FamilyX.resize(wordlist_size);
}
void DirectGroup::Process(std::vector<std::string> &WordsX){
    // Calculate R for each GroupT then set withn main_listX.
    std::cout<<"PROCESSING..."<<std::endl;
    const size_t size(WordsX.size() - 1);
    const size_t size_k(size + 1); 
    for(size_t n = 0; n < size; ++n){
        for(size_t k = n + 1; (((k - n) < depth) && (k < size_k)); ++k){
            GroupT g(WordsX[n], WordsX[k], (depth - (k-n)), wordlist_size);
            Set(g);
        }
    }
}
void DirectGroup::Set(GroupT &group){
    // Place within main_listX two words with their corresponding relationship value.
    const size_t size(main_listX[group.hash_C].size());
    for(size_t n = 0; n < size; ++n){ // Through conflict pairs.
        if(main_listX[group.hash_C][n] == group){
            main_listX[group.hash_C][n].R += group.R;
            return;
        }
    }
    // If no pair matches at index add to conflict vector at index.
      main_listX[group.hash_C].push_back(group);
      // Add individual words to other array to look up via hash and find all relatives.
     // FamilyX[group.hash_0].push_back(group.hash_C);
     // FamilyX[group.hash_1].push_back(group.hash_C);

}
void DirectGroup::TakeInHTML(const char * url_text){ // Python sends a char * not a string.
    // Gather usable words as are found in HTML text.
    std::vector<std::string> WordsX;
    const std::string s_main(WordUse::ToUpper(url_text)); //Use constructor to create usable string.
    const size_t size(s_main.size());
    bool inTag(false);
    std::string tag, text;
    for(size_t n = 0; n < size; ++n)
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

    // Gather hash index values in FamilyX for particular sArg.
    // Look at each hash index within main_listX through conflict pairs for matching strings.

	/*
    const size_t hash_index(Hash::HashMe(sArg, wordlist_size));
    std::cout<<std::endl<<"HASH INDEX FOR: "<<sArg<<" : " <<hash_index<<std::endl;
    const size_t size_f(FamilyX[hash_index].size());
    std::cout<<std::endl<<"Size of FamilyX at "<<hash_index<<" is "<<size_f<<std::endl<<std::endl;
    for(size_t m = 0; m < size_f; ++m){ // These should be short loops though conflict pairs; most are probably size == 1.
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
	*/
    //n^2 look up function without hash work.
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
}

size_t DirectGroup::OurR(const char * sArg, const char *sArg1){
    std::string w(WordUse::ToUpper(sArg)); 
    std::string w1(WordUse::ToUpper(sArg1)); 
    GroupT group(w, w1, 0, wordlist_size); 
    const size_t size(main_listX[group.hash_C].size());
    for(size_t n = 0; n < size; ++n){ // Through conflict pairs.
        if(main_listX[group.hash_C][n] == group){
		return main_listX[group.hash_C][n].R;
        }
    }
    return 0;
}

void DirectGroup::Forget(){
    // Start reducing R in GroupT each call.
    // If R is already == 1 erase GroupT from main_listX
    // Since main_listX size is constant and conflicts should be rare this is closer to C time than n^2
    // as long as the starting wordlist_size is sufficiently large enough.
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
    // When interfacing with Python its nice to know the destructor got called.
    // Can be removed.
    std::cout<<"DESTROYED"<<std::endl;
}
