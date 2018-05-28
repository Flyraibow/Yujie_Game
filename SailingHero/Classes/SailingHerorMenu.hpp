//
//  SailingHerorMenu.hpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 5/16/18.
//

#ifndef SailingHerorMenu_hpp
#define SailingHerorMenu_hpp

#include "SHScene.hpp"

class SailingHeroMenu : public SHScene
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void buttonClickCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(SailingHeroMenu);
};

#endif /* SailingHerorMenu_hpp */
