//
//  LocalizationHelper.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 5/16/18.
//

#include "LocalizationHelper.hpp"

#include "cocos2d.h"

#include "base/ccUTF8.h"

USING_NS_CC;

using namespace std;

static LocalizationHelper *s_sharedLocalizationHelper = nullptr;

LocalizationHelper* LocalizationHelper::getInstance()
{
    if (!s_sharedLocalizationHelper)
    {
        s_sharedLocalizationHelper = new (std::nothrow) LocalizationHelper();
        s_sharedLocalizationHelper->load("File.txt");
    }
    
    return s_sharedLocalizationHelper;
    
}

void LocalizationHelper::load(const std::string &filename)
{
    auto data = FileUtils::getInstance()->getDataFromFile(filename);
    
    if (!data.isNull())
    {
        auto bytes = data.getBytes();
        
        auto str = StringUtils::toString(bytes);
        
        CCLOG("bypte: %s, length: %ld", str.c_str(), data.getSize());
    }
    else CCLOG("FILE not found");
    
    
}

string LocalizationHelper::getLocalization(const string &localId)
{
    if (LocalizationHelper::getInstance()->s_map.count(localId)) {
        return LocalizationHelper::getInstance()->s_map.at(localId);
    }
    CCLOG("Local id doesn't have translation: %s", localId.c_str());
    return localId;
}
