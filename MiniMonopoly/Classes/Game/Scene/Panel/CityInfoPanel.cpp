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
#include "TeamData.hpp"
#include "QuickAlert.hpp"
#include "GameScene.hpp"

std::unordered_map<std::string, CityInfoPanel *> CityInfoPanel::s_sharedCityInfoPanel = std::unordered_map<std::string, CityInfoPanel *>();


CityInfoPanel::CityInfoPanel(CityData* cityData)
{
  p_cityData = cityData;
  p_labCreateTeam = nullptr;
  p_createTeamButton = nullptr;
}

Node* CityInfoPanel::generateCityPanel()
{
  auto cityData = p_cityData;
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
  if (cityData->isMyCity()) {
    p_labCreateTeam = Label::createWithSystemFont("创建商队 ($500)" , SYSTEM_FONT, 18);
    p_createTeamButton = MenuItemLabel::create(p_labCreateTeam, CC_CALLBACK_1(CityInfoPanel::clickCreateTeam, this));
    
    auto menu = Menu::createWithItem(p_createTeamButton);
    menu->setPosition(Vec2::ZERO);
    sprite->addChild(menu);
    
    height += p_createTeamButton->getContentSize().height + 5;
  }
  float width = 220;
  auto size = Size(width, height);
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
    labGoodsNumber->setPosition(width - 5, top);
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
      labGuildControls->setPosition(width - 5, top);
      sprite->addChild(labGuildControls);
      
      top -= labGuild->getContentSize().height + 4;
    }
  }
  
  // show create team button
  if (cityData->isMyCity()) {
    p_createTeamButton->setAnchorPoint(Vec2(0.5, 1));
    p_createTeamButton->setPosition(220 / 2, top);
    top -= p_createTeamButton->getContentSize().height + 5;
  }
  
  refresh();
  
  return sprite;
}

void CityInfoPanel::refresh()
{
  if (p_labCreateTeam != nullptr) {
    auto myGuild = p_cityData->getControledByGuild();
    auto price = TeamData::getCreatTeamPrice(myGuild);
    p_labCreateTeam->setString("创建商队 ($" + to_string(price) + ")");
  }
}

void CityInfoPanel::clickCreateTeam(cocos2d::Ref* pSender)
{
  // 创建商队
  auto myGuild = p_cityData->getControledByGuild();
  auto price = TeamData::getCreatTeamPrice(myGuild);
  CCASSERT(myGuild->isPlayer(), "must create team in a city controled by player.");
  if (myGuild->getMoney() < price) {
    QuickAlert::createAlertWithMsg("金钱不足");
  } else {
    auto teamData = TeamData::createTeam(myGuild, p_cityData);
    auto scene = GameScene::getGameScene();
    scene->addTeamOnMap(teamData);
    refresh();
  }
}
