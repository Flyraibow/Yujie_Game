//
//  SystemScene.hpp
//  MiniMonopoly
//
//  Created by Yujie Liu on 7/28/19.
//

#ifndef SystemScene_hpp
#define SystemScene_hpp

#include "cocos2d.h"

class GameManager;

class SystemScene : public cocos2d::Scene
{
private:
  void quitLevel(cocos2d::Ref* pSender);
  void resume(cocos2d::Ref* pSender);
  void restartLevel(cocos2d::Ref* pSender);
  
public:
  static cocos2d::Scene* createScene();
  
  virtual bool init();
  
  // implement the "static create()" method manually
  CREATE_FUNC(SystemScene);
};


#endif /* SystemScene_hpp */
