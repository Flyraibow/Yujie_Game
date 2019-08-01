//
//  TeamIcon.cpp
//  MiniMonopoly
//
//  Created by Yujie Liu on 7/31/19.
//

#include "TeamIcon.hpp"
#include "CityData.hpp"
#include "GuildData.hpp"

TeamIcon::TeamIcon(TeamData* teamData)
{
  p_teamData = teamData;
  p_teamIconButton = nullptr;
  p_parent = nullptr;
}

TeamIcon::~TeamIcon()
{
  
}

void TeamIcon::addTeamToMap(Node* parent)
{
  if (p_teamIconButton == nullptr) {
    float teamWidth = 0.02 * Director::getInstance()->getVisibleSize().width;
    auto icon = "res/Graph/Icon/camelIcon.png";
    p_teamIconButton = MenuItemImage::create(icon, icon, CC_CALLBACK_1(TeamIcon::clickTeam, this));
    p_teamIconButton->setName(p_teamData->getId());
    auto scale = teamWidth / p_teamIconButton->getContentSize().width;
    p_teamIconButton->setScale(scale);
    
    auto mapMenu = Menu::create();
    mapMenu->setPosition(Vec2::ZERO);
    mapMenu->setContentSize(parent->getContentSize());
    parent->addChild(mapMenu, 1);
    mapMenu->addChild(p_teamIconButton);
  }
  
  p_parent = parent;
  Vec2 pos;
  if (p_teamData->getCurrCity() != nullptr) {
    auto p = p_teamData->getCurrCity()->getPosition();
    pos = Vec2(p.first, p.second);
  } else {
    pos = p_teamData->getCurrPosition();
  }
  auto parentSize = p_parent->getContentSize();
  p_teamIconButton->setNormalizedPosition(pos);//(parentSize.width * pos.first, parentSize.height * pos.second);
  p_teamIconButton->setColor(p_teamData->getGuild()->getColor());
}

void TeamIcon::clickTeam(cocos2d::Ref *pSender)
{
  CCLOG("CLICK");
}

TeamIcon* TeamIcon::createTeamIconWithTeamData(TeamData* teamData)
{
  auto teamIcon = new TeamIcon(teamData);
  return teamIcon;
}
