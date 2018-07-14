//
//  SelectHeroMenu.hpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 5/16/18.
//

#ifndef SelectHeroMenu_hpp
#define SelectHeroMenu_hpp

#include "SHScene.hpp"

class SelectHeroMenu : public SHScene
{
public:
  static cocos2d::Scene* createScene();
  
  virtual bool init();
  
  void clickCancelButton(cocos2d::Ref* pSender);
  // implement the "static create()" method manually
  CREATE_FUNC(SelectHeroMenu);
};

#endif /* SailingHerorMenu_hpp */

