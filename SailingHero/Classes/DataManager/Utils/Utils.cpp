//
//  Utils.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 6/1/18.
//

#include "Utils.hpp"
#include <string.h>

using namespace std;

namespace std {
    string to_string(const string &str) {
        return str;
    }
    template<typename T>
    string to_string(const unordered_set<T> &pSet) {
        string st = "{ ";
        for (auto str : pSet) {
            st += to_string(str) + ", ";
        }
        st += "}";
        return st;
    }
    
    template<typename T>
    string to_string(const vector<T> &pSet) {
        string st = "{ ";
        for (auto str : pSet) {
            st += to_string(str) + ", ";
        }
        st += "}";
        return st;
    }
    
    string to_string(const unordered_set<string> &pSet) {
        return to_string<string>(pSet);
    }
    
    string to_string(const unordered_set<int> &pSet) {
        return to_string<int>(pSet);
    }
    
    string to_string(const unordered_set<bool> &pSet) {
        return to_string<bool>(pSet);
    }
    string to_string(const unordered_set<double> &pSet){
        return to_string<double>(pSet);
    }
    
    string to_string(const unordered_set<float> &pSet) {
        return to_string<float>(pSet);
    }
    
    string to_string(const unordered_set<long long> &pSet) {
        return to_string<long long>(pSet);
    }
    
    string to_string(const vector<int> &pSet) {
        return to_string<int>(pSet);
    }

    string to_string(const vector<bool> &pSet) {
        return to_string<bool>(pSet);
    }
    
    string to_string(const vector<double> &pSet) {
        return to_string<double>(pSet);
    }
    
    string to_string(const vector<float> &pSet) {
        return to_string<float>(pSet);
    }
    
    string to_string(const vector<string> &pSet) {
        return to_string<string>(pSet);
    }
    
    string to_string(const vector<long long> &pSet) {
        return to_string<long long>(pSet);
    }
}
