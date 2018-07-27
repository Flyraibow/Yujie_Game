//
//  CityBuildingFrame.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 7/26/18.
//

#include "CityBuildingFrame.hpp"
#include "ui/UIButton.h"

CityBuildingFrame::CityBuildingFrame(int cityBuildingDataId) : CityBuildingFrame(CityBuildingData::getCityBuildingDataById(cityBuildingDataId)) {}

CityBuildingFrame::CityBuildingFrame(CityBuildingData* cityBuildingData)
{
  CCASSERT(cityBuildingData, "City building data cannot be nil");
  p_cityBuildingData = cityBuildingData;
  
  auto button = ui::Button::create(cityBuildingData->getBuildingImagePath());
  button->setAnchorPoint(Vec2(cityBuildingData->getAnchorX(), cityBuildingData->getAnchorY()));
  button->setNormalizedPosition(Vec2(cityBuildingData->getPosX(), cityBuildingData->getPosY()));
  button->addClickEventListener(
                                [cityBuildingData](cocos2d::Ref* pSender){
                                  CCLOG("click %s", cityBuildingData->getBuildingName().c_str());
                                }
                                );
  p_sprite = button;
}

Node* CityBuildingFrame::getSprite() const
{
  return p_sprite;
}
