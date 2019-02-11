//
//  MenuScene.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/10/19.
//

#ifndef MenuScene_hpp
#define MenuScene_hpp

#include "cocos2d.h"

class MenuScene : public cocos2d::Scene
{
public:
  static cocos2d::Scene* createScene();
  
  virtual bool init();
  
  // a selector callback
  void menuCloseCallback(cocos2d::Ref* pSender);
  
  // implement the "static create()" method manually
  CREATE_FUNC(MenuScene);
};

#endif /* MenuScene_hpp */
