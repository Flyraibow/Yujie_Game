//
//  FrontContainer.cpp
//  YJStartWithNothing
//
//  Created by Yujie Liu on 10/4/19.
//

#include "FrontContainer.hpp"
#include "BaseSpriteListener.hpp"
#include "GameManager.hpp"

bool FrontContainer::init()
{
  // 1. super init first
  if ( !Sprite::init() )
  {
      return false;
  }
  auto listener = BaseSpriteListener::createWithNode(this, false);
  listener->setTouchBegin(CC_CALLBACK_2(FrontContainer::touchBegin, this));
  auto cancelTouch = CC_CALLBACK_2(FrontContainer::touchEnd, this);
  listener->setTouchEnd(cancelTouch, cancelTouch);
  
  return true;
}

bool FrontContainer::touchBegin(Touch* touch, Event* event)
{
  // start making progress
  return true;
}

void FrontContainer::touchEnd(Touch* touch, Event* event)
{
  if (!GameManager::getInstance()->getStarted()) {
    GameManager::getInstance()->setStarted(true);
    initRole();
  } else if (!GameManager::getInstance()->getMoving()) {
    GameManager::getInstance()->setMoving(true);
  }
}

void FrontContainer::initMoney()
{
  
}

void FrontContainer::initRole()
{
  p_role = MyRole::create();
  p_role->setAnchorPoint(Vec2(0.5, 0));
  p_role->setNormalizedPosition(Vec2(0.5, 0.2));
  this->addChild(p_role, 1);
}

void FrontContainer::initAge()
{
  p_labAge = Label::createWithTTF("Age: 1 years", "fonts/Marker Felt.ttf", 24);
  p_labAge->setTextColor(Color4B::BLACK);
  p_labAge->setAnchorPoint(Vec2(0, 1));
  p_labAge->setNormalizedPosition(Vec2(0.05, 0.95));
  this->addChild(p_labAge, 10);
}

void FrontContainer::updateAge()
{
  auto val = to_string_with_precision<double>(GameManager::getInstance()->getAge(), 1);
  auto age = "Age: " + val + " years";
  p_labAge->setString(age);
}

void FrontContainer::setValue(string type, double value)
{
  auto val = to_string_with_precision<double>(value, 1);
  auto vStr = type + ": " + val;
  if (p_attriLabs.count(type)) {
    auto lab = p_attriLabs.at(type);
    lab->setString(vStr);
    if (value == 0) {
      lab->setTextColor(Color4B::GRAY);
    } else {
      lab->setTextColor(Color4B::BLACK);
    }
  } else {
    auto lab = Label::createWithTTF(vStr, "fonts/Marker Felt.ttf", 20);
    lab->setTextColor(Color4B::BLACK);
    lab->setAnchorPoint(Vec2(0, 1));
    lab->setNormalizedPosition(Vec2(0.05, 0.88 - p_attriLabs.size() * 0.05));
    this->addChild(lab, 10);
    p_attriLabs[type] = lab;
  }
}
