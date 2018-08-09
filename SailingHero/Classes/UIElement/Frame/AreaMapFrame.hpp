//
//  AreaMapFrame.hpp
//  SailingHero
//
//  Created by Yujie Liu on 8/8/18.
//

#ifndef AreaMapFrame_hpp
#define AreaMapFrame_hpp

#include "cocos2d.h"
#include "AreaData.hpp"

USING_NS_CC;
using namespace std;

class AreaMapFrame
{
private:
  Node* p_background;
  Node* p_areaSprite;
  void refresh();
  AreaData* p_areaData;
  Vector<MenuItem*> p_cityList;
  void cityClickCallback(cocos2d::Ref* pSender);
public:
  AreaMapFrame();
  void setAreaData(AreaData* areaData);
  Node* getSprite() const;
};


#endif /* AreaMapFrame_hpp */
