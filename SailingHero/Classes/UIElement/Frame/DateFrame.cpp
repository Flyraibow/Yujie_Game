//
//  DateFrame.cpp
//  SailingHero
//
//  Created by Yujie Liu on 8/8/18.
//

#include "DateFrame.hpp"
#include "SHGameDataHelper.hpp"

DateFrame::DateFrame()
{
  auto f = Director::getInstance()->getContentScaleFactor();
  p_sprite = Sprite::create("res/base/frame/areaButtonFrame.png");
  p_labDate = Label::createWithSystemFont(getGameDate(), "Helvetica", 13);
  p_labDate->setAnchorPoint(Vec2(1, 0.5));
  p_labDate->setNormalizedPosition(Vec2(0.95, 0.5));
  auto size = p_sprite->getContentSize();
  p_labDate->setContentSize(size);
  p_labDate->setDimensions(size.width, size.height);
  p_labDate->setAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
  p_labDate->setScale(1 / f);
  p_sprite->addChild(p_labDate);
}

void DateFrame::refresh()
{
  p_labDate->setString(getGameDate());
}

Node* DateFrame::getSprite() const
{
  return p_sprite;
}
