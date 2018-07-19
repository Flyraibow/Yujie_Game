//
//  CitySceneFrame.hpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 7/18/18.
//

#ifndef CitySceneFrame_hpp
#define CitySceneFrame_hpp


#include "cocos2d.h"
#include "CityData.hpp"
#include <vector>

USING_NS_CC;
using namespace std;

class CitySceneFrame
{
private:
  Sprite* p_sprite;
  CityData* p_cityData;
  double p_scale;
  Label* p_labCityName;
  Label* p_labCityType;
  Label* p_labCulture;
  Label* p_labMilitary;
  Label* p_labCommerce;
  Label* p_labMilitaryValue;
  Label* p_labCommerceValue;
  Label* p_labCityStatus;
  Label* p_labGoodsTag;
  vector<Label *> p_labGoodsList;
  vector<Label *> p_labGuildList;
  vector<Label *> p_labGuildShareList;
  
  Label* createLabelWithScale(Vec2 position, Vec2 anchor = Vec2(), std::string text = "");
public:
  CitySceneFrame();
  void setCityData(CityData *cityData);
  void refresh();
  Sprite* getSprite() const;
};

#endif /* CitySceneFrame_hpp */
