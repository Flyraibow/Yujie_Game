//
//  SailingHeroMenu.hpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 5/16/18.
//

#ifndef SailingHeroMenu_hpp
#define SailingHeroMenu_hpp

#include "SHScene.hpp"

class SailingHeroMenu : public SHScene
{
public:
  static cocos2d::Scene* createScene();
  SailingHeroMenu();
  
  virtual bool init();
  
  void clickStartGame(cocos2d::Ref* pSender);
  void clickLoadGame(cocos2d::Ref* pSender);
  void clickGameSetting(cocos2d::Ref* pSender);
  void clickTest1(cocos2d::Ref* pSender);
  void clickTest2(cocos2d::Ref* pSender);
  void clickTest3(cocos2d::Ref* pSender);
  void clickTest4(cocos2d::Ref* pSender);
  
  // implement the "static create()" method manually
  CREATE_FUNC(SailingHeroMenu);
};

#endif /* SailingHeroMenu_hpp */

