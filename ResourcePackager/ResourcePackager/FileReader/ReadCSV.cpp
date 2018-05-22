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
#include <unordered_set>

using namespace std;

vector<string>* readCSVOneLine(ifstream &indata)
{
    string cell;
    if (getline(indata , cell, '\r')) {
        vector<string>* vec = new vector<string>();
        cell.erase(std::remove(cell.begin(), cell.end(), '\n'), cell.end());
        
        while (cell.length() > 0) {
            // get the first word.
            bool is_special = cell.at(0) == '"';
            unordered_set<char> end_chars = is_special ? unordered_set<char>({'"'}) : unordered_set<char>({',','\t'});
            for (int i = is_special ? 1 : 0; i < cell.length(); ++i) {
                char c = cell.at(i);
                if (end_chars.count(c) > 0 ||  i + 1 == cell.length()) {
                    if (is_special) {
                        if (i + 1 < cell.length() && cell.at(i + 1) == '"') {
                            ++i;
                        } else {
                            // find the word
                            string word = cell.substr(1,i-1);
                            word = regex_replace(word, regex("\"\""), "\"");
                            vec->push_back(word);
                            cell = cell.substr(i+1);
                            cout << word << endl;
                            break;
                        }
                    } else {
                        // find the word.
                        string word = ( i + 1 == cell.length())? cell.substr(0,i+1) : cell.substr(0,i);
                        vec->push_back(word);
                        cell = cell.substr(i+1);
                        break;
                    }
                }
            }
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
    }
    
    return dictionary;
}
