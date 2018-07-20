//
//  SystemBarFrame.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 7/19/18.
//

#include "SystemBarFrame.hpp"

#include "SystemButton.hpp"
#include "SystemButtonData.hpp"

static const int SYSTEM_BAR_BUTTON_NUM = 5;

SystemBarFrame::SystemBarFrame()
{
  p_sprite = Sprite::create("res/base/frame/systemBar.png");
  
  for (int i = 0; i < SYSTEM_BAR_BUTTON_NUM; ++i) {
    auto buttonData = SystemButtonData::getSystemButtonDataById(i);
    auto button = SystemButton::defaultButtonWithText(buttonData->getButtonName(), CC_CALLBACK_1(SystemBarFrame::clickSystemButton, this));
    button->setTag(i);
    button->setAnchorPoint(Vec2(0.5, 0.5));
    button->setNormalizedPosition(Vec2(0.112 + i * 0.1923, 0.4));
    button->setContentSize(Size(48, 15));
    p_buttonList.push_back(button);
    p_sprite->addChild(button);
  }
}

void SystemBarFrame::setTextScale(double f)
{
  for (int i = 0; i < SYSTEM_BAR_BUTTON_NUM; ++i) {
    p_buttonList[i]->setScale(f);
  }
}

void SystemBarFrame::clickSystemButton(cocos2d::Ref* pSender)
{
  Button *button = dynamic_cast<Button *>(pSender);
  CCLOG("click system button %d", button->getTag());
}

Sprite* SystemBarFrame::getSprite() const
{
  return p_sprite;
}
