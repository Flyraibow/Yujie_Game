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

USING_NS_CC;

class SailMapFrame
{
private:
  Sprite* p_sprite;
  double p_scale;
  AreaData* p_currentArea;
  AreaMapFrame p_areaMap;
  vector<Node*> p_buttonList;
  Label* p_labCurrentArea;
  void updateAreaData(AreaData *areaData);
  void addButton(AreaData *areaData, AREA_BUTTON_POSITION position);
public:
  SailMapFrame();
  Sprite* getSprite() const;
};


#endif /* SailMapFrame_hpp */
