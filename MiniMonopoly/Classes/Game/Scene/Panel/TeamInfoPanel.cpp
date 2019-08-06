//
//  TeamInfoPanel.cpp
//  MiniMonopoly
//
//  Created by Yujie Liu on 8/1/19.
//

#include "TeamInfoPanel.hpp"
#include "SceneConstants.h"
#include "GuildData.hpp"

TeamInfoPanel::TeamInfoPanel(TeamData* teamData)
{
  p_teamData = teamData;
  generateTeamPanel();
  refresh();
}
void TeamInfoPanel::generateTeamPanel()
{
  p_panel = ui::Scale9Sprite::create("res/Graph/Frame/frame.png");
  p_labelName = Label::createWithSystemFont(p_teamData->getName(), SYSTEM_FONT, 20);
  p_labelName->setAnchorPoint(Vec2(0.5, 0));
  p_panel->addChild(p_labelName);
  p_labelGuild = Label::createWithSystemFont(p_teamData->getGuild()->getName(), SYSTEM_FONT, 20);
  p_labelGuild->setAnchorPoint(Vec2(1, 0));
  p_panel->addChild(p_labelGuild);
  p_tradeBtn = MenuItemLabel::create(Label::createWithSystemFont("交易", SYSTEM_FONT, 20), CC_CALLBACK_1(TeamInfoPanel::clickTrade, this));
  p_tradeBtn->setAnchorPoint(Vec2(0.5, 0));
  
  
  auto menu = Menu::createWithItem(p_tradeBtn);
  menu->setPosition(Vec2::ZERO);
  p_panel->addChild(menu);
}

void TeamInfoPanel::refresh()
{
  float width = 220;
  float center = 220 / 2;
  float bottom = 5;
  if (p_teamData->getCurrCity() != nullptr) {
    p_tradeBtn->setVisible(true);
    p_tradeBtn->setPosition(center, bottom);
    bottom += p_tradeBtn->getContentSize().height + 5;
  } else {
    p_tradeBtn->setVisible(false);
  }
  bottom += 5;
  p_labelGuild->setPosition(width - 5, bottom);
  bottom += p_labelGuild->getContentSize().height + 5;
  p_labelName->setPosition(center, bottom);
  bottom += p_labelName->getContentSize().height + 5;

  p_panel->setContentSize(Size(width, bottom));
}

#include "TradePanel.hpp"

void TeamInfoPanel::clickTrade(cocos2d::Ref* pSender)
{
  TradePanel::createTradePanel(p_teamData);
}
