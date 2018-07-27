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
#include <unordered_map>
#include "SystemBarFrame.hpp"

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
  SystemBarFrame p_systemBarFrame;
  unordered_map<int, Node*> p_buildingImageMap;
  
  Label* p_labData;
  
  Label* createLabelWithScale(Vec2 position, Vec2 anchor = Vec2(), std::string text = "", int textSize = 8);
public:
  CitySceneFrame();
  void setCityData(CityData *cityData);
  void refresh();
  Sprite* getSprite() const;
  void clickTest2(cocos2d::Ref* pSender);
  void clickTest3(cocos2d::Ref* pSender);
};

#endif /* CitySceneFrame_hpp */
