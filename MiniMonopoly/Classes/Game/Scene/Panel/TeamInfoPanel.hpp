//
//  TeamInfoPanel.hpp
//  MiniMonopoly
//
//  Created by Yujie Liu on 8/1/19.
//

#ifndef TeamInfoPanel_hpp
#define TeamInfoPanel_hpp

#include "cocos2d.h"
#include "ui/UIScale9Sprite.h"
#include "TeamData.hpp"

USING_NS_CC;

class TeamInfoPanel
{
private:
  static std::unordered_map<std::string, TeamInfoPanel *> s_sharedTeamInfoPanel;
  TeamData* p_teamData;
  ui::Scale9Sprite* p_panel;
  Label* p_labelName;
  Label* p_labelGuild;
  MenuItem* p_tradeBtn;
  void generateTeamPanel();
  
  void clickTrade(cocos2d::Ref* pSender);
public:
  TeamInfoPanel(TeamData* teamData);
  Node* getPanel() const {return p_panel;};
  void refresh();
};

#endif /* TeamInfoPanel_hpp */
