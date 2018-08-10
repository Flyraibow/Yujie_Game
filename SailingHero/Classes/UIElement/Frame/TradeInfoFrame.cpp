//
//  TradeInfoFrame.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 8/9/18.
//

#include "TradeInfoFrame.hpp"

TradeInfoFrame::TradeInfoFrame()
{
  p_sprite = Sprite::create("res/base/frame/tradeInfoFrame.png");
}

void TradeInfoFrame::setCityData(CityData *cityData)
{
  p_cityData = cityData;
}

Sprite* TradeInfoFrame::getSprite() const
{
  return p_sprite;
}
