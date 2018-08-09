//
//  SailMapFrame.cpp
//  SailingHero
//
//  Created by Yujie Liu on 8/8/18.
//

#include "SailMapFrame.hpp"
#include "DateFrame.hpp"
#include "GameData.hpp"
#include "SHSpriteListener.hpp"

SailMapFrame::SailMapFrame()
{
  p_sprite = Sprite::create("res/base/frame/sailSceneFrame.png");
  
  Vec2 origin = Director::getInstance()->getVisibleOrigin();
  auto visibleSize = Director::getInstance()->getVisibleSize();
  p_scale = visibleSize.height / p_sprite->getContentSize().height;
  p_sprite->setScale(p_scale);
  p_sprite->setAnchorPoint(Vec2(0, 0));
  p_sprite->setNormalizedPosition(Vec2(0, 0));
  
  auto areaMapSprite = p_areaMap.getSprite();
  areaMapSprite->setPosition(Vec2(14, 13));
  p_sprite->addChild(areaMapSprite);
  
  DateFrame dateFrame;
  auto dateFrameSprite = dateFrame.getSprite();
  dateFrameSprite->setAnchorPoint(Vec2());
  dateFrameSprite->setNormalizedPosition(Vec2(0.01, 0.005));
  p_sprite->addChild(dateFrameSprite, 1);

  updateAreaData(GameData::getSharedInstance()->getCityData()->getAreaData());
}

void SailMapFrame::updateAreaData(AreaData *areaData)
{
  p_currentArea = areaData;
  p_areaMap.setAreaData(p_currentArea);
  for (auto areaButton : p_buttonList) {
    areaButton->removeFromParent();
  }
  p_buttonList.clear();
  
  addButton(p_currentArea->getLeftData(), AREA_BUTTON_POSITION::LEFT);
  addButton(p_currentArea->getRightUpData(), AREA_BUTTON_POSITION::RIGHT_UP);
  addButton(p_currentArea->getRightData(), AREA_BUTTON_POSITION::RIGHT);
  addButton(p_currentArea->getRightDownData(), AREA_BUTTON_POSITION::RIGHT_DOWN);
  addButton(p_currentArea->getUpData(), AREA_BUTTON_POSITION::UP);
  addButton(p_currentArea->getDownData(), AREA_BUTTON_POSITION::DOWN);
}

void SailMapFrame::addButton(AreaData *areaData, AREA_BUTTON_POSITION position)
{
  if (areaData != nullptr) {
    AreaMapGoButtonFrame button(areaData, position);
    auto listener = SHSpriteListener::createWithNode(button.getSprite());
    listener->setTouchEnd([areaData, this](Touch* touch, Event* event){
      CCLOG("select area 0: %s", areaData->getAreaName().c_str());
      this->updateAreaData(areaData);
    }, nullptr);
    
    p_buttonList.push_back(button.getSprite());
    p_sprite->addChild(button.getSprite());
  }
}


Sprite* SailMapFrame::getSprite() const
{
  return p_sprite;
}
