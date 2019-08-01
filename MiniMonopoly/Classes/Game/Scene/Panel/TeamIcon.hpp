//
//  TeamIcon.hpp
//  MiniMonopoly
//
//  Created by Yujie Liu on 7/31/19.
//

#ifndef TeamIcon_hpp
#define TeamIcon_hpp

#include "cocos2d.h"
#include "TeamData.hpp"

USING_NS_CC;

class TeamIcon
{
private:
  // Data
  TeamData* p_teamData;
//  CityInfoPanel* p_cityInfoData;
  
  // Sprite
  Node* p_parent;
  MenuItemImage* p_teamIconButton;
//  Node* p_cityInfoPanel;
  
  void clickTeam(cocos2d::Ref* pSender);
public:
  TeamIcon(TeamData* teamData);
  ~TeamIcon();
  void addTeamToMap(Node* parent);
  static TeamIcon* createTeamIconWithTeamData(TeamData* teamData);
};

#endif /* TeamIcon_hpp */
