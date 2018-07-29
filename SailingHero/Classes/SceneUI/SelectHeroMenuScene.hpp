//
//  SelectHeroMenu.hpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 5/16/18.
//

#ifndef SelectHeroMenu_hpp
#define SelectHeroMenu_hpp

#include "SHScene.hpp"

class SelectHeroMenuScene : public SHScene
{
public:
  static cocos2d::Scene* createScene();
  
  virtual bool init();
  
  // implement the "static create()" method manually
  CREATE_FUNC(SelectHeroMenuScene);
};

#endif /* SailingHeroMenu_hpp */

