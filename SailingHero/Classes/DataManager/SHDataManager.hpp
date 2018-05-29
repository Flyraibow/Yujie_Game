//
//  SHDataManager.hpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 5/28/18.
//

#ifndef SHDataManager_hpp
#define SHDataManager_hpp

#include "cocos2d.h"
#include "base/CCRef.h"

USING_NS_CC;

class SHDataManager : public Ref
{
private:
    static SHDataManager* s_dataManager;
public:
    static SHDataManager* getInstance();
    bool init();
};


#endif /* SHDataManager_hpp */
