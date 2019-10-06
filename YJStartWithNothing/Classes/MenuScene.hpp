//
//  MenuScene.hpp
//  YJStartWithNothing
//
//  Created by Yujie Liu on 10/4/19.
//

#ifndef MenuScene_hpp
#define MenuScene_hpp

#include "cocos2d.h"
#include "FrontContainer.hpp"
#include "BackgroundContainer.hpp"

USING_NS_CC;

class MenuScene : public cocos2d::Scene
{
private:
  BackgroundContainer* p_background;
  FrontContainer* p_front;
  
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
  
  void restart();
    
    CREATE_FUNC(MenuScene);
};


#endif /* MenuScene_hpp */

