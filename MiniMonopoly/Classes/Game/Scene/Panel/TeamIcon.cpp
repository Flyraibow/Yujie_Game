//
//  TeamIcon.cpp
//  MiniMonopoly
//
//  Created by Yujie Liu on 7/31/19.
//

#include "TeamIcon.hpp"
#include "CityData.hpp"
#include "GuildData.hpp"
#include "TeamInfoPanel.hpp"

TeamIcon::TeamIcon(TeamData* teamData)
{
  p_teamData = teamData;
  p_teamInfoPanel = nullptr;
  p_teamIconButton = nullptr;
  p_parent = nullptr;
  p_teamInfoPanelNode = nullptr;
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
  CCLOG("CLICK team : %s", p_teamData->getName().c_str());
  if (getTeamInfoPanelVisible()) {
    setTeamInfoPanelVisible(false);
    return;
  }
  if (p_teamInfoPanel == nullptr) {
    p_teamInfoPanel = new TeamInfoPanel(p_teamData);
    p_teamInfoPanelNode = p_teamInfoPanel->getPanel();
    auto position = p_teamIconButton->getPosition();
    auto size = p_teamIconButton->getContentSize();
    auto scale = p_teamIconButton->getScale();
    p_teamInfoPanelNode->setScale(1.0 / p_parent->getScale());
    
    auto cityNormalizedPosition = p_teamIconButton->getNormalizedPosition();
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
    p_teamInfoPanelNode->setAnchorPoint(Vec2(anchorX, anchorY));
    p_teamInfoPanelNode->setPosition(Vec2(x, y));
    p_parent->addChild(p_teamInfoPanelNode);
  } else {
    p_teamInfoPanel->refresh();
    setTeamInfoPanelVisible(true);
  }
}

TeamIcon* TeamIcon::createTeamIconWithTeamData(TeamData* teamData)
{
  auto teamIcon = new TeamIcon(teamData);
  return teamIcon;
}

bool TeamIcon::getTeamInfoPanelVisible() const
{
  if (p_teamInfoPanelNode == nullptr) {
    return false;
  }
  return p_teamInfoPanelNode->isVisible();
}

void TeamIcon::setTeamInfoPanelVisible(bool visible)
{
  if (p_teamInfoPanelNode != nullptr) {
    p_teamInfoPanelNode->setVisible(visible);
  }
}
