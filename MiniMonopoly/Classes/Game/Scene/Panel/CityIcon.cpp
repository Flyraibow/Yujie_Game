//
//  CityIcon.cpp
//  MiniMonopoly
//
//  Created by Yujie Liu on 7/30/19.
//

#include "CityIcon.hpp"
#include "CityInfoPanel.hpp"

CityIcon::CityIcon(CityData* cityData)
{
  p_cityData = cityData;
  p_cityInfoData = new CityInfoPanel(cityData);
  p_parent = nullptr;
  p_cityIconButton = nullptr;
  p_cityInfoPanel = nullptr;
}

CityIcon::~CityIcon()
{
  delete p_cityInfoData;
  p_cityInfoData = nullptr;
}

void CityIcon::addCityToMap(Node* parent)
{
  if (p_cityIconButton == nullptr) {
    float cityWidth = 0.03 * Director::getInstance()->getVisibleSize().width;
    auto icon = p_cityData->getIcon();
    p_cityIconButton = MenuItemImage::create(icon, icon, CC_CALLBACK_1(CityIcon::clickCity, this));
    p_cityIconButton->setName(p_cityData->getId());
    auto scale = cityWidth / p_cityIconButton->getContentSize().width;
    p_cityIconButton->setScale(scale);
    
    auto mapMenu = Menu::create();
    mapMenu->setPosition(Vec2::ZERO);
    mapMenu->setContentSize(parent->getContentSize());
    parent->addChild(mapMenu);
    mapMenu->addChild(p_cityIconButton);
  }
  
  p_parent = parent;
  
  auto pos = p_cityData->getPosition();
  auto parentSize = p_parent->getContentSize();
  p_cityIconButton->setNormalizedPosition(Vec2(pos.first, pos.second));//(parentSize.width * pos.first, parentSize.height * pos.second);
  p_cityIconButton->setColor(p_cityData->getControledCollor());
}

void CityIcon::clickCity(cocos2d::Ref* pSender)
{
  CCLOG("click city : %s", p_cityData->getName().c_str());
  if (getCityInfoPanelVisible()) {
    setCityInfoPanelVisible(false);
    return;
  }
  if (p_cityInfoPanel == nullptr) {
    auto cityPanel = p_cityInfoData->generateCityPanel();
    auto position = p_cityIconButton->getPosition();
    auto size = p_cityIconButton->getContentSize();
    auto scale = p_cityIconButton->getScale();
    cityPanel->setScale(1.0 / p_parent->getScale());
    
    auto cityNormalizedPosition = p_cityIconButton->getNormalizedPosition();
    float x, y;
    float anchorX, anchorY;
    if (cityNormalizedPosition.x <= 0.5) {
      // show in right side
      x = position.x + size.width / 2 * scale;
      anchorX = 0;
    } else {
      // show in left side
      x = position.x - size.width / 2 * scale;
      anchorX = 1;
    }
    if (cityNormalizedPosition.y <= 0.5) {
      // show in up side
      y = position.y + size.height / 2 * scale;
      anchorY = 0;
    } else {
      // show in left side
      y = position.y - size.height / 2 * scale;
      anchorY = 1;
    }
    cityPanel->setAnchorPoint(Vec2(anchorX, anchorY));
    cityPanel->setPosition(Vec2(x, y));
    p_parent->addChild(cityPanel);
    p_cityInfoPanel = cityPanel;
  } else {
    setCityInfoPanelVisible(true);
  }
}

bool CityIcon::getCityInfoPanelVisible() const
{
  if (p_cityInfoPanel == nullptr) {
    return false;
  }
  return p_cityInfoPanel->isVisible();
}

void CityIcon::setCityInfoPanelVisible(bool visible)
{
  if (p_cityInfoPanel != nullptr) {
    p_cityInfoPanel->setVisible(visible);
  }
}

CityIcon* CityIcon::createCityIconWithCityData(CityData* cityData)
{
  auto cityIcon = new CityIcon(cityData);
  return cityIcon;
}
