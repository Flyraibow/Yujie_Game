//
//  LocalizationHelper.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 5/16/18.
//

#include "LocalizationHelper.hpp"

#include <string>

#include "cocos2d.h"

#include "ByteBuffer.hpp"

USING_NS_CC;

using namespace std;

static LocalizationHelper *s_sharedLocalizationHelper = nullptr;

LocalizationHelper* LocalizationHelper::getInstance()
{
    if (!s_sharedLocalizationHelper)
    {
        s_sharedLocalizationHelper = new (std::nothrow) LocalizationHelper();
        s_sharedLocalizationHelper->load("res/base/translation/chinese.lang");
    }
    
    return s_sharedLocalizationHelper;
    
}

void LocalizationHelper::load(const std::string &filename)
{
    auto data = FileUtils::getInstance()->getDataFromFile(filename);
    
    if (!data.isNull())
    {
        auto bytes = data.getBytes();
        
        auto buffer = make_unique<bb::ByteBuffer>(bytes, data.getSize());
        auto count = buffer->getLong();
        CCLOG("======= count : %llu", count);
        for (int i = 0; i < count; ++i) {
            string localId = buffer->getString();
            string translation = buffer->getString();
            cout << localId << "  " << translation << endl;
            s_map[localId] = translation;
        }
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
