//
//  CityInfoPanel.cpp
//  MiniMonopoly
//
//  Created by Yujie Liu on 7/29/19.
//

#include "CityInfoPanel.hpp"
#include "ui/UIScale9Sprite.h"
#include "SceneConstants.h"
#include "GuildData.hpp"


Node* generateCityPanel(const CityData* cityData)
{
  ui::Scale9Sprite *sprite = ui::Scale9Sprite::create("res/Graph/Frame/frame.png");
  
  auto labName = Label::createWithSystemFont(cityData->getName(), SYSTEM_FONT, 20);
  labName->setAnchorPoint(Vec2(0.5, 1));
  labName->setNormalizedPosition(Vec2(0.5, 1));
  sprite->addChild(labName);
  auto goodsList = cityData->getGoodsList();
  auto guildControls = cityData->getGuildControls();
  
  auto sample = Label::createWithSystemFont("1", SYSTEM_FONT, 18);
  float lineHeight = sample->getContentSize().height;
  float height = labName->getContentSize().height + 25 + (lineHeight + 4) * goodsList.size() + (lineHeight + 4) * guildControls.size();
  auto size = Size(220, height);
  sprite->setPreferredSize(size);

  // show the goods and numbers
  float top = height - labName->getContentSize().height - 10;
  for (auto goods : goodsList) {
    auto goodsAndLvStr = goods->getName() + "[Lv" + to_string(goods->getLevel()) + "]";
    auto labGoods = Label::createWithSystemFont(goodsAndLvStr, SYSTEM_FONT, 18);
    labGoods->setAnchorPoint(Vec2(0, 1));
    labGoods->setPosition(5, top);
    sprite->addChild(labGoods);
    
    auto labGoodsNumber = Label::createWithSystemFont(to_string(goods->getCurrNum()) + "/" + to_string(goods->getMaxNum()), SYSTEM_FONT, 18);
    labGoodsNumber->setAnchorPoint(Vec2(1, 1));
    labGoodsNumber->setPosition(size.width - 5, top);
    sprite->addChild(labGoodsNumber);
    
    top -= labGoods->getContentSize().height + 4;
  }
  
  top -= 5;
  // show the guild and controls
  auto masterGuild = cityData->getControledByGuild();
  for (auto guildControlPair : guildControls) {
    if (guildControlPair.second > 0) {
      auto guildName = masterGuild == guildControlPair.first ? guildControlPair.first->getName() + "(owner)" : guildControlPair.first->getName();
      auto labGuild = Label::createWithSystemFont(guildName, SYSTEM_FONT, 18);
      labGuild->setAnchorPoint(Vec2(0, 1));
      labGuild->setPosition(5, top);
      sprite->addChild(labGuild);
      
      auto labGuildControls = Label::createWithSystemFont(to_string(guildControlPair.second) + "%", SYSTEM_FONT, 18);
      labGuildControls->setAnchorPoint(Vec2(1, 1));
      labGuildControls->setPosition(size.width - 5, top);
      sprite->addChild(labGuildControls);
      
      top -= labGuild->getContentSize().height + 4;
    }
  }
  
  
  return sprite;
}

std::unordered_map<std::string, CityInfoPanel *> CityInfoPanel::s_sharedCityInfoPanel = std::unordered_map<std::string, CityInfoPanel *>();


Node* CityInfoPanel::generateCityPanel(const CityData* cityData)
{
  return generateCityPanel(cityData);
}

