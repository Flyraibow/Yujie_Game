//
//  CityInfoPanel.cpp
//  MiniMonopoly
//
//  Created by Yujie Liu on 7/29/19.
//

#include "CityInfoPanel.hpp"
#include "ui/UIScale9Sprite.h"
#include "SceneConstants.h"

Node* generateCityPanel(const CityData* cityData)
{
  ui::Scale9Sprite *sprite = ui::Scale9Sprite::create("res/Graph/Frame/frame.png");
  
  auto labName = Label::createWithSystemFont(cityData->getName(), SYSTEM_FONT, 20);
  labName->setAnchorPoint(Vec2(0.5, 1));
  labName->setNormalizedPosition(Vec2(0.5, 1));
  sprite->addChild(labName);
  auto goodsList = cityData->getGoodsList();
  
  auto sample = Label::createWithSystemFont("1", SYSTEM_FONT, 18);
  float lineHeight = sample->getContentSize().height;
  float height = labName->getContentSize().height + 20 + (lineHeight + 4) * goodsList.size();
  auto size = Size(150, height);
  sprite->setPreferredSize(size);
  
  float top = height - labName->getContentSize().height - 10;
  for (auto goods : goodsList) {
    auto labGoods = Label::createWithSystemFont(goods->getName(), SYSTEM_FONT, 18);
    labGoods->setAnchorPoint(Vec2(0, 1));
    labGoods->setPosition(5, top);
    sprite->addChild(labGoods);
    
    auto labGoodsNumber = Label::createWithSystemFont(to_string(goods->getCurrNum()) + "/" + to_string(goods->getMaxNum()), SYSTEM_FONT, 18);
    labGoodsNumber->setAnchorPoint(Vec2(1, 1));
    labGoodsNumber->setPosition(size.width - 5, top);
    sprite->addChild(labGoodsNumber);
    
    top -= labGoods->getContentSize().height + 4;
  }
  
  return sprite;
}
