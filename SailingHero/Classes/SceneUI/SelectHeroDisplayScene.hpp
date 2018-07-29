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
  Label* p_labHeroName;
  Label* p_labGuildName;
  Label* P_labBirth;
  Label* p_labZodiac;
  Sprite* p_zodiacIcon;
  HeroSelectData* p_selectHeroData;
public:
  static cocos2d::Scene* createScene(HeroSelectData *selectHeroData);
  
  virtual bool init();
  
  void setSelectHeroData(HeroSelectData *selectHeroData);
  void refreshScene();
  void clickChangeHeroName(cocos2d::Ref* pSender);
  void clickChangeGuildName(cocos2d::Ref* pSender);
  void clickChangeHeroBirth(cocos2d::Ref* pSender);
  void clickChangeStartGame(cocos2d::Ref* pSender);
  void selectHero();
  
  // implement the "static create()" method manually
  CREATE_FUNC(SelectHeroDisplayScene);
};


#endif /* SelectHeroDisplayScene_hpp */
