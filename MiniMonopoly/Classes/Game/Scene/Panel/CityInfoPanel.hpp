//
//  CityInfoPanel.hpp
//  MiniMonopoly
//
//  Created by Yujie Liu on 7/29/19.
//

#ifndef CityInfoPanel_hpp
#define CityInfoPanel_hpp

#include "cocos2d.h"
#include "CityData.hpp"

USING_NS_CC;

class CityInfoPanel
{
private:
  static std::unordered_map<std::string, CityInfoPanel *> s_sharedCityInfoPanel;
  CityData* p_cityData;
  Node* p_node;
  
  void clickCreateTeam(cocos2d::Ref* pSender);
public:
  CityInfoPanel(CityData* cityData);
  Node* generateCityPanel();
};

#endif /* CityInfoPanel_hpp */
