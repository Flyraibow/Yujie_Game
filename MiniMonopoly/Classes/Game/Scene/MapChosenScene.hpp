//
//  MapChosenScene.hpp
//  MiniMonopoly
//
//  Created by Yujie Liu on 7/20/19.
//

#ifndef MapChosenScene_hpp
#define MapChosenScene_hpp

#include <stdio.h>

class MapChosenScene : public cocos2d::Scene
{
private:
  void _showLevelsMethod1();
  void _clickLevel(cocos2d::Ref* pSender);
  
public:
  static cocos2d::Scene* createScene();
  
  virtual bool init();
  
  
  void popScene(cocos2d::Ref* pSender);
  
  // implement the "static create()" method manually
  CREATE_FUNC(MapChosenScene);
};

#endif /* MapChosenScene_hpp */
