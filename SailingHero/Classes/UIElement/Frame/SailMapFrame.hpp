//
//  SailMapFrame.hpp
//  SailingHero
//
//  Created by Yujie Liu on 8/8/18.
//

#ifndef SailMapFrame_hpp
#define SailMapFrame_hpp

#include "cocos2d.h"
#include "AreaData.hpp"
#include "AreaMapFrame.hpp"
#include "AreaMapGoButtonFrame.hpp"
#include "TradeInfoFrame.hpp"
#include "CityDataFrame.hpp"

USING_NS_CC;

class CityData;

class SailMapFrame
{
private:
  Sprite* p_sprite;
  double p_scale;
  AreaData* p_currentArea;
  AreaMapFrame p_areaMap;
  vector<Node*> p_buttonList;
  Label* p_labCurrentArea;
  TradeInfoFrame* p_tradeInfoFrame;
  CityDataFrame* p_cityInfoFrame;
  void updateAreaData(AreaData *areaData);
  void addButton(AreaData *areaData, AREA_BUTTON_POSITION position);
  void citySelectCallback(CityData* cityData);
public:
  SailMapFrame();
  Sprite* getSprite() const;
};


#endif /* SailMapFrame_hpp */
