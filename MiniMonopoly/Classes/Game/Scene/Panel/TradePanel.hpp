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
class CityGoodsData;
class TeamGoodsData;

USING_NS_CC;
using namespace std;

class TradePanel
{
private:
  CityData* p_cityData;
  TeamData* p_teamData;
  unordered_map<CityGoodsData *, int> p_willBuyDict;
  unordered_map<TeamGoodsData *, int> p_willSellDict;
  
  Node* p_panel;
  Menu* p_menu;
  Node* p_buyPanel;
  Node* p_sellPanel;
  Node* p_willBuyPanel;
  Node* p_willSellPanel;
  Label* p_finalMoney;
  
  void addCityGoodsTitle(Node* sprite);
  void addTeamGoodsTitle(Node* sprite);
  
  void willBuyGoods(CityGoodsData* cityGoodsData, int num);
  void willSellGoods(TeamGoodsData* cityGoodsData, int num);
  void refreshWillBuyPanel();
  void refreshWillSellPanel();
  void refreshFinalMoney();
  void clickClose(cocos2d::Ref* pSender);
  void clickConfirm(cocos2d::Ref* pSender);
public:
  TradePanel(TeamData* teamData);
  Node* getPanel() const {return p_panel;};
  
  static void createTradePanel(TeamData* teamData);
};

#endif /* TradePanel_hpp */
