//
//  SailingHeroPackager.cpp
//  ResourcePackager
//
//  Created by Yujie Liu on 5/16/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#include <iostream>
#include "SailingHeroPackager.hpp"
#include "LanguageData.hpp"
#include "LanguageWriter.hpp"

void SailingHeroPackager::startPackage()
{
    readBaseFiles();
}

void SailingHeroPackager::readBaseFiles()
{
    string baseLanguagePath = get_dataSourcePath() + "/Base/translation.csv";
    string baseLanguageOutput = get_outputResourcePath() + "/Base/translation/";
    
    cout << "read base language: " << baseLanguagePath << endl;
    auto baseLanguage = LanguageData(baseLanguagePath);
    LanguageWriter langWriter;
    langWriter.writeLanguageData(baseLanguage, baseLanguageOutput);
}
