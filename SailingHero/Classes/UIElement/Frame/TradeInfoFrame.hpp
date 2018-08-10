//
//  TradeInfoFrame.hpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 8/9/18.
//

#ifndef TradeInfoFrame_hpp
#define TradeInfoFrame_hpp

#include "cocos2d.h"
#include "CityData.hpp"

USING_NS_CC;

class TradeInfoFrame
{
private:
  Sprite* p_sprite;
  CityData* p_cityData;
public:
  TradeInfoFrame();
  void setCityData(CityData *cityData);
  Sprite* getSprite() const;
};


#endif /* TradeInfoFrame_hpp */
