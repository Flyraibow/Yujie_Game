//
//  ReadCSV.hpp
//  ResourcePackager
//
//  Created by Yujie Liu on 5/16/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#ifndef ReadCSV_hpp
#define ReadCSV_hpp

#include <stdio.h>

#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

typedef unordered_map<string, unordered_map<string, string>> MAP_2D;

vector<vector<string>> readCVSBylines(const string &path);

/*
 Will take the first row and col as the key
 i.e.   map[row_key][col_key] = value (row first)
        map[col_key][row_key] = value (row first)
 */
MAP_2D readCVSByMaping(const string &path, bool rowfirst = true);


#endif /* ReadCSV_hpp */
