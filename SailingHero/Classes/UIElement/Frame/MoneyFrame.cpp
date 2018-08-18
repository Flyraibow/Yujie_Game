//
//  MoneyFrame.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 7/28/18.
//

#include "MoneyFrame.hpp"
#include "LocalizationHelper.hpp"

MoneyFrame::MoneyFrame()
{
  p_guildData = nullptr;
}

void MoneyFrame::setGuildDataId(int guildId)
{
  setGuildData(GuildData::getGuildDataById(guildId));
}

void MoneyFrame::setGuildData(GuildData *guildData)
{
  p_guildData = guildData;
  refresh();
}

void MoneyFrame::refresh()
{
  p_labMoney->setString(to_string(p_guildData->getMoney()));
}

Node* MoneyFrame::genSprite(double scale)
{
  auto f = Director::getInstance()->getContentScaleFactor();
  p_sprite = Sprite::create("res/base/frame/moneyFrame.jpg");
  p_labMoney = Label::createWithSystemFont("0", "Helvetica", 16);
  p_labMoney->setAnchorPoint(Vec2(1, 0.5));
  p_labMoney->setNormalizedPosition(Vec2(0.95, 0.5));
  p_labMoney->setScale(1 / f);
  p_sprite->addChild(p_labMoney);
  auto labMoneyTag = Label::createWithSystemFont(LocalizationHelper::getLocalization("tag_money"), "Helvetica", 16);
  labMoneyTag->setAnchorPoint(Vec2(0, 0.5));
  labMoneyTag->setNormalizedPosition(Vec2(0.05, 0.5));
  labMoneyTag->setScale(1 / f);
  p_sprite->addChild(labMoneyTag);
  return p_sprite;
}
