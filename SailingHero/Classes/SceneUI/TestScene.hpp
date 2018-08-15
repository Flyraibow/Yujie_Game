//
//  TestScene.hpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 8/14/18.
//

#ifndef TestScene_hpp
#define TestScene_hpp

#include "SHScene.hpp"

class TestScene : public SHScene
{
private:
  void testSailMap(cocos2d::Ref* pSender);
  void clickBack(cocos2d::Ref* pSender);
public:
  static TestScene* createScene();
  
  virtual bool init();
  
  // implement the "static create()" method manually
  CREATE_FUNC(TestScene);
};

#endif /* TestScene_hpp */
