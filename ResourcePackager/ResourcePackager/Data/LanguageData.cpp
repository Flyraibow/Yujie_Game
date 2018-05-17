//
//  LanguageData.cpp
//  ResourcePackager
//
//  Created by Yujie Liu on 5/16/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#include "LanguageData.hpp"

LanguageData::LanguageData(const string &filePath)
{
    s_dictionary = readCVSByMaping(filePath, false);
}

MAP_2D LanguageData::get_dictionary() const
{
    return s_dictionary;
}
