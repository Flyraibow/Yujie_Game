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

void SailMapFrame::updateAreaData(AreaData *areaData)
{
  p_currentArea = areaData;
  p_areaMap.setAreaData(p_currentArea);
  for (auto areaButton : p_buttonList) {
    areaButton->removeFromParent();
    delete areaButton;
  }
  p_buttonList.clear();
  p_labCurrentArea->setString(areaData->getAreaName());
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
    AreaMapGoButtonFrame *button = new AreaMapGoButtonFrame();
    button->setTargetArea(areaData, position);
    button->addToParent(p_sprite);
    button->addClickEvent([areaData, this](Touch* touch, Event* event){
      this->updateAreaData(areaData);
    });
    p_buttonList.push_back(button);
  }
}

void SailMapFrame::citySelectCallback(CityData* cityData)
{
  if (p_tradeInfoFrame == nullptr) {
    p_tradeInfoFrame = new TradeInfoFrame();
    p_tradeInfoFrame->addToParent(p_sprite, 2, true);
  } else {
    p_tradeInfoFrame->setVisible(true);
  }
  p_tradeInfoFrame->updateGoodsCategory();
  p_tradeInfoFrame->setCityData(cityData);
  
//    if (p_cityInfoFrame == nullptr) {
//      p_cityInfoFrame = new CityDataFrame();
//      auto sprite = p_cityInfoFrame->getSprite();
//      p_sprite->addChild(sprite, 2);
//    }
//    p_cityInfoFrame->setCityData(cityData);
}

Node* SailMapFrame::genSprite(double scale)
{
  p_sprite = Sprite::create("res/base/frame/sailSceneFrame.png");
  
  Vec2 origin = Director::getInstance()->getVisibleOrigin();
  auto visibleSize = Director::getInstance()->getVisibleSize();
  p_scale = visibleSize.height / p_sprite->getContentSize().height;
  auto f = Director::getInstance()->getContentScaleFactor();
  p_sprite->setScale(p_scale);
  p_sprite->setAnchorPoint(Vec2(0, 0));
  p_sprite->setNormalizedPosition(Vec2(0, 0));
  
  p_areaMap.setCityDataSelectCallback(CC_CALLBACK_1(SailMapFrame::citySelectCallback, this));
  p_areaMap.addToParent(p_sprite);
  
  DateFrame dateFrame;
  dateFrame.addToParent(p_sprite, 1);
  dateFrame.getSprite()->setAnchorPoint(Vec2());
  dateFrame.getSprite()->setNormalizedPosition(Vec2(0.01, 0.005));
  
  p_labCurrentArea = Label::createWithSystemFont("", "Helvetica", 16);
  p_labCurrentArea->setNormalizedPosition(Vec2(0.136, 0.885));
  p_labCurrentArea->setScale(1.0 / f);
  p_sprite->addChild(p_labCurrentArea);
  
  p_tradeInfoFrame = nullptr;
  updateAreaData(GameData::getSharedInstance()->getCityData()->getAreaData());
  return p_sprite;
}
