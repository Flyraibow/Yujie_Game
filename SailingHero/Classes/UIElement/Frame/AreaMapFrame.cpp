//
//  AreaMapFrame.cpp
//  SailingHero
//
//  Created by Yujie Liu on 8/8/18.
//

#include "AreaMapFrame.hpp"
#include "CityData.hpp"
#include "ui/UIButton.h"

AreaMapFrame::AreaMapFrame()
{
  p_background = Node::create();
  p_areaData = nullptr;
}

void AreaMapFrame::setAreaData(AreaData* areaData)
{
  p_areaData = areaData;
  refresh();
}

void AreaMapFrame::refresh()
{
  if (p_areaSprite != nullptr) {
    p_areaSprite->removeFromParent();
    p_cityList.clear();
  }
  p_areaSprite = p_areaData->getIcon();
  p_areaSprite->setAnchorPoint(Vec2());
  p_background->addChild(p_areaSprite);
  auto dict = CityData::getSharedDictionary();
  auto rect = Rect(p_areaData->getX1(), p_areaData->getY1(), p_areaData->getX2() - p_areaData->getX1(), p_areaData->getY2() - p_areaData->getY1());
  for (auto iter = dict->begin(); iter != dict->end(); ++iter) {
    auto city = iter->second;
    auto cityPoint = Vec2(city->getLongitude(), city->getLatitude());
    if (rect.containsPoint(cityPoint)) {
      auto cityDataSelectCallback = p_cityDataSelectCallback;
      auto cityIcon = MenuItemImage::create(
                                            city->getCityTypeData()->getCityUpIconPath(),
                                            city->getCityTypeData()->getCityDownIconPath(),
                                            [cityDataSelectCallback](cocos2d::Ref* pSender) {
                                              auto menuItem = dynamic_cast<MenuItemImage *>(pSender);
                                              int cityId = menuItem->getTag();
                                              auto cityData = CityData::getCityDataById(cityId);
                                              cityDataSelectCallback(cityData);
                                            });
      cityIcon->setTag(city->getCityId());
      cityIcon->setPosition(Vec2((cityPoint.x - rect.origin.x) / rect.size.width * p_areaSprite->getContentSize().width,
                                           (cityPoint.y - rect.origin.y) / rect.size.height * p_areaSprite->getContentSize().height));
      p_cityList.pushBack(cityIcon);
    }
  }
  auto menu = Menu::createWithArray(p_cityList);
  menu->setPosition(Vec2());
  p_areaSprite->addChild(menu);
}

void AreaMapFrame::setCityDataSelectCallback(ccCityDataSelectCallback cityDataSelectCallback)
{
  p_cityDataSelectCallback = cityDataSelectCallback;
}

Node* AreaMapFrame::getSprite() const
{
  return p_background;
}
