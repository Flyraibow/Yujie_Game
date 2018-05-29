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


void LanguageData::addTranslation(const string& language, const string &localId, const string &translation)
{
    assert(s_dictionary.at(language).count(localId) == 0);
    s_dictionary[language][localId] = translation;
}
