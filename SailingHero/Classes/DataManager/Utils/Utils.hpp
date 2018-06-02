//
//  Utils.hpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 6/1/18.
//

#ifndef Utils_hpp
#define Utils_hpp

#include <stdio.h>
#include <unordered_set>
#include <vector>


namespace std {
    string to_string(const string &pSet);
    string to_string(const unordered_set<int> &pSet);
    string to_string(const unordered_set<bool> &pSet);
    string to_string(const unordered_set<double> &pSet);
    string to_string(const unordered_set<float> &pSet);
    string to_string(const unordered_set<string> &pSet);
    string to_string(const unordered_set<long long> &pSet);
    
    string to_string(const vector<int> &pSet);
    string to_string(const vector<bool> &pSet);
    string to_string(const vector<double> &pSet);
    string to_string(const vector<float> &pSet);
    string to_string(const vector<string> &pSet);
    string to_string(const vector<long long> &pSet);
}

#endif /* Utils_hpp */
