#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> combSets;
    return floatComb(in, floating, combSets, dict);


}

std::set<std::string> floatComb(
    const std::string& in,
    const std::string& floating,
    std::set<std::string>& combSets, const std::set<std::string>& dict){

    //if nothing to float return 
    //if not, for the size of the floating pass first letter to in
    //and then remove the first letter in floating and recurse
    if(floating.size() == 0){
        allComb(in, combSets, 0, dict);
    }
    else{
        for(unsigned int i = 0; i < in.size(); i++){
            if(in[i] == '-'){
                string s = in;
                s[i] = floating[0];
                floatComb(s, floating.substr(1), combSets, dict);
            }
        }
    }
    return combSets;
}

void allComb(std::string in, std::set<std::string>& combSets, int len, const std::set<std::string>& dict)
{
    if(len == int(in.size())){
        if(dict.find(in) != dict.end()){
            combSets.insert(in);
        }
    
    }
    else{
        if(in[len] == '-'){
            for(int num = 97; num <= 122; num++){
                char c = static_cast<char>(num);
                in[len] = c;
                allComb(in, combSets, len+1, dict);
            }
        }
        else{
            allComb(in,combSets, len+1, dict);
        }
    }
    
}


// Define any helper functions here
