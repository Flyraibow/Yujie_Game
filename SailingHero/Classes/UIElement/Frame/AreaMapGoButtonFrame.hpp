//
//  AreaMapGoButtonFrame.hpp
//  SailingHero
//
//  Created by Yujie Liu on 8/8/18.
//

#ifndef AreaMapGoButtonFrame_hpp
#define AreaMapGoButtonFrame_hpp

#include "cocos2d.h"
#include "AreaData.hpp"

USING_NS_CC;
using namespace std;

enum class AREA_BUTTON_POSITION
{
  LEFT = 0,
  RIGHT_UP = 1,
  RIGHT = 2,
  RIGHT_DOWN = 3,
  UP = 4,
  DOWN = 5,
};

class AreaMapGoButtonFrame
{
private:
  bool p_isVertical;
  Node* p_sprite;
  Label* p_labAreaTarget;
  AreaData* p_targetArea;
  AREA_BUTTON_POSITION p_position;
public:
  AreaMapGoButtonFrame(AreaData* targetArea, AREA_BUTTON_POSITION position);
  Node* getSprite() const;
};

#endif /* AreaMapGoButtonFrame_hpp */
