//
//  ReadCSV.cpp
//  ResourcePackager
//
//  Created by Yujie Liu on 5/16/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#include "ReadCSV.hpp"

#include <sstream>
#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

vector<string>* readCSVOneLine(ifstream &indata)
{
    string cell;
    if (getline(indata , cell, '\r')) {
        vector<string>* vec = new vector<string>();
        cell.erase(std::remove(cell.begin(), cell.end(), '\n'), cell.end());
        regex e("[\t,]");
        sregex_token_iterator iter(cell.begin(),
                                   cell.end(),
                                   e,
                                   -1);
        
        for ( ; iter != sregex_token_iterator(); ++iter) {
            string token = *iter;
            cout << token << endl;
            vec->push_back(token);
        }
        return vec;
    }
    return nullptr;
}

MAP_2D readCVSByMaping(const string &path, bool rowfirst)
{
    MAP_2D dictionary;
    ifstream indata;
    indata.open(path);
    int row = 0;
    vector<string> col_keys;
    while(auto vec = readCSVOneLine(indata)) {
        if (vec->size() == 0) {
            continue;
        }
        string row_key = vec->at(0);
        for (int i = 1; i < vec->size(); ++i) {
            string str = vec->at(i);
            if (row == 0) {
                col_keys.push_back(str);
            } else {
                string col_key = col_keys.at(i - 1);
                // There shouldn't be any duplicates
                if (rowfirst) {
                    assert(dictionary.count(row_key) == 0 || dictionary[row_key].count(col_key) == 0);
                    dictionary[row_key][col_key] = str;
                } else {
                    assert(dictionary.count(col_key) == 0 || dictionary[col_key].count(row_key) == 0);
                    dictionary[col_key][row_key] = str;
                }
            }
        }
        row++;
        cout << row << endl;
//        delete [] vec;
    }
    
    return dictionary;
}
