//
//  TradePanel.cpp
//  MiniMonopoly
//
//  Created by Yujie Liu on 8/1/19.
//

#include "TradePanel.hpp"
#include "TeamData.hpp"
#include "CityData.hpp"

#include "SceneConstants.h"

TradePanel::TradePanel(TeamData* teamData)
{
  p_teamData = teamData;
  p_cityData = teamData->getCurrCity();
  
  float width = 800;
  float height = 600;
  
  p_panel = ui::Scale9Sprite::create("res/Graph/Frame/frame.png");
  p_panel->setContentSize(Size(width, height));
  auto title = Label::createWithSystemFont("交易所", SYSTEM_FONT, 30);
  title->setAnchorPoint(Vec2(0.5, 1));
  title->setNormalizedPosition(Vec2(0.5, 0.99));
  p_panel->addChild(title);
  
  auto top = height - title->getContentSize().height - 10;
  
  auto cityName = Label::createWithSystemFont(p_cityData->getName(), SYSTEM_FONT, 25);
  cityName->setAnchorPoint(Vec2(0.5, 1));
  cityName->setPosition(Vec2(width * 0.25, top));
  p_panel->addChild(cityName);
  
  auto teamName = Label::createWithSystemFont(p_teamData->getName(), SYSTEM_FONT, 25);
  teamName->setAnchorPoint(Vec2(0.5, 1));
  teamName->setPosition(Vec2(width * 0.75, top));
  p_panel->addChild(teamName);
  
  auto ownNumber = Label::createWithSystemFont("持有数", SYSTEM_FONT, 25);
  ownNumber->setAnchorPoint(Vec2(1, 1));
  ownNumber->setPosition(Vec2(width - 20, top));
  p_panel->addChild(ownNumber);
  
  auto cityNumber = Label::createWithSystemFont("数量", SYSTEM_FONT, 25);
  cityNumber->setAnchorPoint(Vec2(0, 1));
  cityNumber->setPosition(Vec2(20, top));
  p_panel->addChild(cityNumber);
  
  // show goods
  
  auto closeButton = MenuItemLabel::create(Label::createWithSystemFont("关闭", SYSTEM_FONT, 25), CC_CALLBACK_1(TradePanel::clickClose, this));
  closeButton->setAnchorPoint(Vec2(0.5, 0));
  closeButton->setNormalizedPosition(Vec2(0.5, 0.01));
  auto menu = Menu::createWithItem(closeButton);
  menu->setPosition(Vec2::ZERO);
  p_panel->addChild(menu);
}

void TradePanel::clickClose(cocos2d::Ref* pSender)
{
  p_panel->removeFromParent();
}

void TradePanel::createTradePanel(TeamData* teamData)
{
  auto tradePanel = new TradePanel(teamData);
  auto panel = tradePanel->getPanel();
  panel->setNormalizedPosition(Vec2(0.5, 0.5));
  Director::getInstance()->getRunningScene()->addChild(panel);
}
