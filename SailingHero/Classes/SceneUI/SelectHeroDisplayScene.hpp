//
//  SelectHeroDisplayScene.hpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 7/14/18.
//

#ifndef SelectHeroDisplayScene_hpp
#define SelectHeroDisplayScene_hpp

#include "SHScene.hpp"
#include "HeroSelectData.hpp"

USING_NS_CC;

class SelectHeroDisplayScene : public SHScene
{
private:
  Sprite* p_zodiacIcon;
public:
  static cocos2d::Scene* createScene(HeroSelectData *selectHeroData);
  
  virtual bool init();
  
  void refreshScene();
  
  // implement the "static create()" method manually
  CREATE_FUNC(SelectHeroDisplayScene);
};


#endif /* SelectHeroDisplayScene_hpp */
