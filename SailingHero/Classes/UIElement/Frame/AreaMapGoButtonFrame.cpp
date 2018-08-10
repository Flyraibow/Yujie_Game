//
//  AreaMapGoButtonFrame.cpp
//  SailingHero
//
//  Created by Yujie Liu on 8/8/18.
//

#include "AreaMapGoButtonFrame.hpp"

AreaMapGoButtonFrame::AreaMapGoButtonFrame(AreaData* targetArea, AREA_BUTTON_POSITION position)
{
  p_targetArea = targetArea;
  p_position = position;
  p_isVertical = !(position == AREA_BUTTON_POSITION::UP || position == AREA_BUTTON_POSITION::DOWN);
  p_sprite = Sprite::create("res/base/frame/areaButtonFrame.png");
  auto f = Director::getInstance()->getContentScaleFactor();
  p_labAreaTarget = Label::createWithSystemFont(targetArea->getAreaName(), "Helvetica", 13);
  p_labAreaTarget->setScale(1 / f);
  auto size = p_sprite->getContentSize();
  if (p_isVertical) {
    p_labAreaTarget->setContentSize(Size(size.height + 10, size.width + 10));
    p_labAreaTarget->setDimensions(size.height, size.width);
    p_labAreaTarget->setRotation(-90);
    p_sprite->setRotation(90);
  } else {
    p_labAreaTarget->setContentSize(size);
    p_labAreaTarget->setDimensions(size.width, size.height);
  }
  p_labAreaTarget->setAlignment(TextHAlignment::CENTER, TextVAlignment::CENTER);
  p_labAreaTarget->setAnchorPoint(Vec2(0.5, 0.5));
  p_labAreaTarget->setNormalizedPosition(Vec2(0.5, 0.5));
  p_sprite->addChild(p_labAreaTarget);
  
  switch (position)
  {
    case AREA_BUTTON_POSITION::LEFT:
      p_sprite->setAnchorPoint(Vec2(0, 0));
      p_sprite->setNormalizedPosition(Vec2(0, 0.35));
      break;
    case AREA_BUTTON_POSITION::RIGHT_UP:
      p_sprite->setAnchorPoint(Vec2(0, 1));
      p_sprite->setNormalizedPosition(Vec2(1, 0.8645));
      break;
    case AREA_BUTTON_POSITION::RIGHT:
      p_sprite->setAnchorPoint(Vec2(0, 1));
      p_sprite->setNormalizedPosition(Vec2(1, 0.58));
      break;
    case AREA_BUTTON_POSITION::RIGHT_DOWN:
      p_sprite->setAnchorPoint(Vec2(0, 1));
      p_sprite->setNormalizedPosition(Vec2(1, 0.30));
      break;
    case AREA_BUTTON_POSITION::UP:
      p_sprite->setAnchorPoint(Vec2(0.5, 1));
      p_sprite->setNormalizedPosition(Vec2(0.5, 0.9));
      break;
    case AREA_BUTTON_POSITION::DOWN:
      p_sprite->setAnchorPoint(Vec2(0.5, 0));
      p_sprite->setNormalizedPosition(Vec2(0.5, 0));
      break;
  }
}

Node* AreaMapGoButtonFrame::getSprite() const
{
  return p_sprite;
}
