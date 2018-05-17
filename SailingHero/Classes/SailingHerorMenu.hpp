//
//  SailingHerorMenu.hpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 5/16/18.
//

#ifndef SailingHerorMenu_hpp
#define SailingHerorMenu_hpp

#include "cocos2d.h"

class SailingHeroMenu : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(SailingHeroMenu);
};

#endif /* SailingHerorMenu_hpp */
