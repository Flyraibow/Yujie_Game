//
//  LanguageWriter.hpp
//  ResourcePackager
//
//  Created by Yujie Liu on 5/16/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#ifndef LanguageWriter_hpp
#define LanguageWriter_hpp

#include <stdio.h>
#include <string>

#include "LanguageData.hpp"

using namespace std;

class LanguageWriter
{
public:
    void writeLanguageData(const LanguageData &data, const string &path);
};

#endif /* LanguageWriter_hpp */
