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
  
  // implement the "static create()" method manually
  CREATE_FUNC(SailingHeroMenu);
};

#endif /* SailingHeroMenu_hpp */

