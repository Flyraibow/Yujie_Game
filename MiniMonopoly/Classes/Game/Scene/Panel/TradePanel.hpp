//
//  TradePanel.hpp
//  MiniMonopoly
//
//  Created by Yujie Liu on 8/1/19.
//

#ifndef TradePanel_hpp
#define TradePanel_hpp

#include "cocos2d.h"
#include "ui/UIScale9Sprite.h"

class CityData;
class TeamData;

USING_NS_CC;

class TradePanel
{
private:
  CityData* p_cityData;
  TeamData* p_teamData;
  
  Node* p_panel;
  
  void clickClose(cocos2d::Ref* pSender);
public:
  TradePanel(TeamData* teamData);
  Node* getPanel() const {return p_panel;};
  
  static void createTradePanel(TeamData* teamData);
};

#endif /* TradePanel_hpp */
