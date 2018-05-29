//
//  SHDataManager.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 5/28/18.
//

#include "SHDataManager.hpp"


SHDataManager* SHDataManager::getInstance()
{
    if (!s_dataManager) {
        s_dataManager = new (std::nothrow) SHDataManager;
        CCASSERT(s_dataManager, "FATAL: Not enough memory");
        s_dataManager->init();
    }
    return s_dataManager;
}

bool SHDataManager::init()
{
    return true;
}

//UserDefault::getInstance()->getStringForKey(key, "");
