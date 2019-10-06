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
  p_panel = nullptr;
  p_teamData = teamData;
  generateTeamPanel();
  refresh();
}
void TeamInfoPanel::generateTeamPanel()
{
  p_panel = ui::Scale9Sprite::create("res/Graph/Frame/frame.png");
  p_labelName = Label::createWithSystemFont(p_teamData->getName(), SYSTEM_FONT, 25);
  p_labelName->setAnchorPoint(Vec2(0.5, 0));
  p_panel->addChild(p_labelName);
  p_tradeBtn = MenuItemLabel::create(Label::createWithSystemFont("交易", SYSTEM_FONT, 20), CC_CALLBACK_1(TeamInfoPanel::clickTrade, this));
  p_tradeBtn->setAnchorPoint(Vec2(0.5, 0));
  
  p_moveBtn = MenuItemLabel::create(Label::createWithSystemFont("移动", SYSTEM_FONT, 20), CC_CALLBACK_1(TeamInfoPanel::clickTrade, this));
  p_moveBtn->setAnchorPoint(Vec2(.5, 0));
  
  auto menu = Menu::create(p_tradeBtn, p_moveBtn, NULL);
  menu->setPosition(Vec2::ZERO);
  p_panel->addChild(menu);
}

void TeamInfoPanel::refresh()
{
  float width = 220;
  float center = 220 / 2;
  float left = 220 / 3;
  float right = 220 / 3 * 2;
  float bottom = 5;
  p_labelName->setString(p_teamData->getName() + "(" + p_teamData->getGuild()->getName() + ")");
  
  p_moveBtn->setPosition(right, bottom);
  bottom += p_moveBtn->getContentSize().height + 5;
  
  if (p_teamData->getCurrCity() != nullptr) {
    p_tradeBtn->setVisible(true);
    p_tradeBtn->setPosition(left, bottom);
    bottom += p_tradeBtn->getContentSize().height + 5;
  } else {
    p_tradeBtn->setVisible(false);
  }
  bottom += 5;
  
  for (auto node : p_goodsNode) {
    node->removeFromParent();
  }
  p_goodsNode.clear();
  
  for (auto teamGoods : p_teamData->getGoodsList()) {
    auto goodsDes = teamGoods->getName() + "(" + to_string(teamGoods->getLevel()) + ") × " + to_string(teamGoods->getNum());
    auto goodsLabel = Label::createWithSystemFont(goodsDes, SYSTEM_FONT, 20);
    goodsLabel->setAnchorPoint(Vec2());
    goodsLabel->setPosition(5, bottom);
    p_panel->addChild(goodsLabel);
    p_goodsNode.push_back(goodsLabel);
    bottom += goodsLabel->getContentSize().height + 5;
  }
  
  p_labelName->setPosition(center, bottom);
  bottom += p_labelName->getContentSize().height + 5;

  p_panel->setContentSize(Size(width, bottom));
}

#include "TradePanel.hpp"

void TeamInfoPanel::clickTrade(cocos2d::Ref* pSender)
{
  TradePanel::createTradePanel(p_teamData);
}
