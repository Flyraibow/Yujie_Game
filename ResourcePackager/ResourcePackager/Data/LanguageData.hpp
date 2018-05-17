//
//  LanguageData.hpp
//  ResourcePackager
//
//  Created by Yujie Liu on 5/16/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#ifndef LanguageData_hpp
#define LanguageData_hpp

#include <stdio.h>
#include <unordered_map>
#include <string>
#include "ReadCSV.hpp"

using namespace std;

class LanguageData
{
private:
    MAP_2D s_dictionary;
public:
    LanguageData(const string &filePath);
    MAP_2D get_dictionary() const;
};

#endif /* LanguageData_hpp */
