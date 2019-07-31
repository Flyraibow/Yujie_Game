//
//  CityIcon.hpp
//  MiniMonopoly
//
//  Created by Yujie Liu on 7/30/19.
//

#ifndef CityIcon_hpp
#define CityIcon_hpp

#include "cocos2d.h"
#include "CityData.hpp"

USING_NS_CC;

class CityInfoPanel;

class CityIcon
{
private:
  // Data
  CityData* p_cityData;
  CityInfoPanel* p_cityInfoData;
  
  // Sprite
  Node* p_parent;
  MenuItemImage* p_cityIconButton;
  Node* p_cityInfoPanel;
  
  void clickCity(cocos2d::Ref* pSender);
public:
  CityIcon(CityData* cityData);
  ~CityIcon();
  void addCityToMap(Node* parent);
  void setCityInfoPanelVisible(bool visible);
  bool getCityInfoPanelVisible() const;
  static CityIcon* createCityIconWithCityData(CityData* cityData);
};

#endif /* CityIcon_hpp */
