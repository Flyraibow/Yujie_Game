//
//  TradePanel.cpp
//  MiniMonopoly
//
//  Created by Yujie Liu on 8/1/19.
//

#include "TradePanel.hpp"
#include "TeamData.hpp"
#include "CityData.hpp"
#include "GuildData.hpp"
#include "QuickAlert.hpp"

#include "SceneConstants.h"

static const float TRADE_PANEL_WIDTH = 1000;
static const float TRADE_PANEL_HEIGHT = 650;
static const float PANEL_HEIGHT = 500;

Sprite* getBackgroundPanel()
{
  auto spriteWidth = TRADE_PANEL_WIDTH / 2 - 20;
  auto spriteLeft = Sprite::create();
  spriteLeft->setContentSize(Size(spriteWidth, spriteWidth));
  auto backLeft = LayerColor::create(Color4B::GRAY, spriteWidth, PANEL_HEIGHT);
  spriteLeft->addChild(backLeft);
  spriteLeft->setAnchorPoint(Size(0, 0.5));
  return spriteLeft;
}

int getNumberFromGoodsText(const string &goodsStr)
{
  int number = 0;
  for (int i = (int)goodsStr.length() - 1; i >= 0; ++i) {
    char c = goodsStr[i];
    if (c >= '0' && c <= '9') {
      number *= 10;
      number += c - '0';
    } else {
      break;
    }
  }
  return number;
}

TradePanel::TradePanel(TeamData* teamData)
{
  p_willBuyPanel = nullptr;
  p_willSellPanel = nullptr;
  p_teamData = teamData;
  p_cityData = teamData->getCurrCity();
  
  p_panel = ui::Scale9Sprite::create("res/Graph/Frame/frame.png");
  p_panel->setContentSize(Size(TRADE_PANEL_WIDTH, TRADE_PANEL_HEIGHT));
  auto title = Label::createWithSystemFont("交易所", SYSTEM_FONT, 30);
  title->setAnchorPoint(Vec2(0.5, 1));
  title->setNormalizedPosition(Vec2(0.5, 0.99));
  p_panel->addChild(title);
  
  p_buyPanel = getBackgroundPanel();
  p_buyPanel->setPosition(Vec2(10, TRADE_PANEL_HEIGHT / 2));
  p_panel->addChild(p_buyPanel);
  
  p_sellPanel = getBackgroundPanel();
  p_sellPanel->setPosition(Vec2(TRADE_PANEL_WIDTH / 2 + 10, TRADE_PANEL_HEIGHT / 2));
  p_panel->addChild(p_sellPanel);
  
  p_menu = Menu::create();
  p_menu->setPosition(Vec2::ZERO);
  
  p_finalMoney = Label::createWithSystemFont("", SYSTEM_FONT, 25);
  p_finalMoney->setAnchorPoint(Vec2(1, 1));
  p_finalMoney->setNormalizedPosition(Vec2(0.99, 0.12));
  p_panel->addChild(p_finalMoney);
  
  // Add title
  addCityGoodsTitle(p_buyPanel);
  addTeamGoodsTitle(p_sellPanel);
  
  auto confirmButton = MenuItemLabel::create(Label::createWithSystemFont("确认交易", SYSTEM_FONT, 25), CC_CALLBACK_1(TradePanel::clickConfirm, this));
  confirmButton->setAnchorPoint(Vec2(0.5, 0));
  confirmButton->setNormalizedPosition(Vec2(0.4, 0.01));
  p_menu->addChild(confirmButton);
  
  auto closeButton = MenuItemLabel::create(Label::createWithSystemFont("关闭", SYSTEM_FONT, 25), CC_CALLBACK_1(TradePanel::clickClose, this));
  closeButton->setAnchorPoint(Vec2(0.5, 0));
  closeButton->setNormalizedPosition(Vec2(0.6, 0.01));
  p_menu->addChild(closeButton);
  p_panel->addChild(p_menu);
}

void TradePanel::addCityGoodsTitle(Node* sprite)
{
  auto cityName = Label::createWithSystemFont(p_cityData->getName() + " 提供", SYSTEM_FONT, 25);
  cityName->setAnchorPoint(Vec2(0, 1));
  cityName->setNormalizedPosition(Vec2(0.01, 0.99));
  sprite->addChild(cityName);
  
  auto levelName = Label::createWithSystemFont("Lv", SYSTEM_FONT, 25);
  levelName->setAnchorPoint(Vec2(1, 1));
  levelName->setNormalizedPosition(Vec2(0.5, 0.99));
  sprite->addChild(levelName);
  
  auto countName = Label::createWithSystemFont("数量", SYSTEM_FONT, 25);
  countName->setAnchorPoint(Vec2(1, 1));
  countName->setNormalizedPosition(Vec2(0.65, 0.99));
  sprite->addChild(countName);
  
  auto priceName = Label::createWithSystemFont("单价", SYSTEM_FONT, 25);
  priceName->setNormalizedPosition(Vec2(0.8, 0.99));
  priceName->setAnchorPoint(Vec2(1, 1));
  sprite->addChild(priceName);
  
  auto buyName = Label::createWithSystemFont("购入", SYSTEM_FONT, 25);
  buyName->setNormalizedPosition(Vec2(0.99, 0.99));
  buyName->setAnchorPoint(Vec2(1, 1));
  sprite->addChild(buyName);
  
  
  auto menu = Menu::create();
  menu->setPosition(Vec2::ZERO);
  menu->setContentSize(sprite->getContentSize());
  sprite->addChild(menu);
  
  auto top = 0.88;
  auto cityGoods = p_cityData->getGoodsList();
  for (auto goods : cityGoods) {
    if (goods && goods->getLevel() > 0) {
      auto goodsNameLabel = Label::createWithSystemFont(goods->getName(), SYSTEM_FONT, 22);
      goodsNameLabel->setAnchorPoint(Vec2(0, 1));
      goodsNameLabel->setNormalizedPosition(Vec2(0.01, top));
      sprite->addChild(goodsNameLabel);
      
      auto goodsLvLabel = Label::createWithSystemFont(to_string(goods->getLevel()), SYSTEM_FONT, 22);
      goodsLvLabel->setAnchorPoint(Vec2(1, 1));
      goodsLvLabel->setNormalizedPosition(Vec2(0.5, top));
      sprite->addChild(goodsLvLabel);
      
      auto numberStr = to_string(goods->getCurrNum()) + "/" + to_string(goods->getMaxNum());
      auto goodsCountLabel = Label::createWithSystemFont(numberStr, SYSTEM_FONT, 22);
      goodsCountLabel->setAnchorPoint(Vec2(1, 1));
      goodsCountLabel->setNormalizedPosition(Vec2(0.65, top));
      sprite->addChild(goodsCountLabel);
      
      auto goodsPriceLabel = Label::createWithSystemFont(to_string(goods->getPrice()), SYSTEM_FONT, 22);
      goodsPriceLabel->setAnchorPoint(Vec2(1, 1));
      goodsPriceLabel->setNormalizedPosition(Vec2(0.8, top));
      sprite->addChild(goodsPriceLabel);
      
      auto buy1Label = Label::createWithSystemFont("+", SYSTEM_FONT, 22);
      auto buy1Button = MenuItemLabel::create(buy1Label, [goods, this](cocos2d::Ref* pSender){
        auto willBuyNum = p_willBuyDict.count(goods) ? p_willBuyDict.at(goods) : 0;
        willBuyNum += 1;
        this->willBuyGoods(goods, willBuyNum);
      });
      buy1Button->setAnchorPoint(Vec2(1, 1));
      buy1Button->setNormalizedPosition(Vec2(0.9, top));
      menu->addChild(buy1Button);
      
      auto buyAllLabel = Label::createWithSystemFont("All", SYSTEM_FONT, 22);
      auto buyAllButton = MenuItemLabel::create(buyAllLabel, [goods, this](cocos2d::Ref* pSender){
        auto willBuyNum = goods->getCurrNum();
        this->willBuyGoods(goods, willBuyNum);
      });
      buyAllButton->setAnchorPoint(Vec2(1, 1));
      buyAllButton->setNormalizedPosition(Vec2(0.99, top));
      menu->addChild(buyAllButton);
      
      top -= 0.1;
    }
  }
}

void TradePanel::addTeamGoodsTitle(Node* sprite)
{
  auto teamName = Label::createWithSystemFont(p_teamData->getName() + " 持有", SYSTEM_FONT, 25);
  teamName->setAnchorPoint(Vec2(0, 1));
  teamName->setNormalizedPosition(Vec2(0.01, 0.99));
  sprite->addChild(teamName);
  
  auto levelName = Label::createWithSystemFont("Lv", SYSTEM_FONT, 25);
  levelName->setAnchorPoint(Vec2(1, 1));
  levelName->setNormalizedPosition(Vec2(0.4, 0.99));
  sprite->addChild(levelName);
  
  auto countName = Label::createWithSystemFont("数量", SYSTEM_FONT, 25);
  countName->setAnchorPoint(Vec2(1, 1));
  countName->setNormalizedPosition(Vec2(0.55, 0.99));
  sprite->addChild(countName);
  
  auto buyPriceName = Label::createWithSystemFont("进价", SYSTEM_FONT, 25);
  buyPriceName->setNormalizedPosition(Vec2(0.7, 0.99));
  buyPriceName->setAnchorPoint(Vec2(1, 1));
  sprite->addChild(buyPriceName);
  
  auto priceName = Label::createWithSystemFont("售价", SYSTEM_FONT, 25);
  priceName->setNormalizedPosition(Vec2(0.85, 0.99));
  priceName->setAnchorPoint(Vec2(1, 1));
  sprite->addChild(priceName);
  
  auto buyName = Label::createWithSystemFont("售出", SYSTEM_FONT, 25);
  buyName->setNormalizedPosition(Vec2(0.99, 0.99));
  buyName->setAnchorPoint(Vec2(1, 1));
  sprite->addChild(buyName);
  
  auto menu = Menu::create();
  menu->setPosition(Vec2::ZERO);
  menu->setContentSize(sprite->getContentSize());
  sprite->addChild(menu);
  
  auto top = 0.88;
  auto teamGoods = p_teamData->getGoodsList();
  for (auto goods : teamGoods) {
    if (goods) {
      auto goodsNameLabel = Label::createWithSystemFont(goods->getName(), SYSTEM_FONT, 22);
      goodsNameLabel->setAnchorPoint(Vec2(0, 1));
      goodsNameLabel->setNormalizedPosition(Vec2(0.01, top));
      sprite->addChild(goodsNameLabel);
      
      auto goodsLvLabel = Label::createWithSystemFont(to_string(goods->getLevel()), SYSTEM_FONT, 22);
      goodsLvLabel->setAnchorPoint(Vec2(1, 1));
      goodsLvLabel->setNormalizedPosition(Vec2(0.4, top));
      sprite->addChild(goodsLvLabel);
      
      auto numberStr = to_string(goods->getNum());
      auto goodsCountLabel = Label::createWithSystemFont(numberStr, SYSTEM_FONT, 22);
      goodsCountLabel->setAnchorPoint(Vec2(1, 1));
      goodsCountLabel->setNormalizedPosition(Vec2(0.55, top));
      sprite->addChild(goodsCountLabel);
      
      auto goodsBuyPriceLabel = Label::createWithSystemFont(to_string(goods->getBuyPrice()), SYSTEM_FONT, 22);
      goodsBuyPriceLabel->setAnchorPoint(Vec2(1, 1));
      goodsBuyPriceLabel->setNormalizedPosition(Vec2(0.7, top));
      sprite->addChild(goodsBuyPriceLabel);
      
      auto getSellPrice = goods->getSellPrice(p_cityData);
      auto goodsPriceLabel = Label::createWithSystemFont(to_string(getSellPrice), SYSTEM_FONT, 22);
      goodsPriceLabel->setAnchorPoint(Vec2(1, 1));
      goodsPriceLabel->setNormalizedPosition(Vec2(0.85, top));
      sprite->addChild(goodsPriceLabel);
      
      auto sell1Label = Label::createWithSystemFont("+", SYSTEM_FONT, 22);
      auto sell1Button = MenuItemLabel::create(sell1Label, [goods, this](cocos2d::Ref* pSender){
        auto willBuyNum = p_willSellDict.count(goods) ? p_willSellDict.at(goods) : 0;
        willBuyNum += 1;
        this->willSellGoods(goods, willBuyNum);
      });
      sell1Button->setAnchorPoint(Vec2(1, 1));
      sell1Button->setNormalizedPosition(Vec2(0.9, top));
      menu->addChild(sell1Button);
      
      auto sellAllLabel = Label::createWithSystemFont("All", SYSTEM_FONT, 22);
      auto sellAllButton = MenuItemLabel::create(sellAllLabel, [goods, this](cocos2d::Ref* pSender){
        auto willBuyNum = goods->getNum();
        this->willSellGoods(goods, willBuyNum);
      });
      sellAllButton->setAnchorPoint(Vec2(1, 1));
      sellAllButton->setNormalizedPosition(Vec2(0.99, top));
      menu->addChild(sellAllButton);
      
      top -= 0.1;
    }
  }
}

void TradePanel::createTradePanel(TeamData* teamData)
{
  auto tradePanel = new TradePanel(teamData);
  auto panel = tradePanel->getPanel();
  panel->setNormalizedPosition(Vec2(0.5, 0.5));
  Director::getInstance()->getRunningScene()->addChild(panel);
}

void TradePanel::willBuyGoods(CityGoodsData* cityGoodsData, int num)
{
  if (num <= 0 && p_willBuyDict.count(cityGoodsData)) {
    p_willBuyDict.erase(cityGoodsData);
  } else {
    if (num >= cityGoodsData->getCurrNum()) {
      num = cityGoodsData->getCurrNum();
    }
    p_willBuyDict[cityGoodsData] = num;
  }
  // refresh will buy area
  refreshWillBuyPanel();
}

void TradePanel::refreshWillBuyPanel()
{
  if (p_willBuyPanel != nullptr) {
    p_willBuyPanel->removeFromParent();
    p_willBuyPanel = nullptr;
  }
  if (p_willBuyDict.size() == 0) {
    return;
  }
  p_willBuyPanel = Sprite::create();
  p_willBuyPanel->setContentSize(p_buyPanel->getContentSize());
  p_willBuyPanel->setNormalizedPosition(Vec2());
  p_willBuyPanel->setAnchorPoint(Vec2());
  p_buyPanel->addChild(p_willBuyPanel);
  
  auto menu = Menu::create();
  menu->setPosition(Vec2::ZERO);
  menu->setContentSize(p_willBuyPanel->getContentSize());
  p_willBuyPanel->addChild(menu);
  
  auto bottom = 0.09;
  auto totalMoney = 0;

  for (auto willBuyGoodsPair : p_willBuyDict) {
    auto goods = willBuyGoodsPair.first;
    auto count = willBuyGoodsPair.second;
    auto nameAndLevel = goods->getName() + "(Lv" + to_string(goods->getLevel()) + ")";
    auto goodsNameLabel = Label::createWithSystemFont(nameAndLevel, SYSTEM_FONT, 22);
    goodsNameLabel->setAnchorPoint(Vec2(0, 0));
    goodsNameLabel->setNormalizedPosition(Vec2(0.01, bottom));
    p_willBuyPanel->addChild(goodsNameLabel);
    
    auto numberStr =  "× " + to_string(count);
    auto goodsCountLabel = Label::createWithSystemFont(numberStr, SYSTEM_FONT, 22);
    goodsCountLabel->setAnchorPoint(Vec2(1, 0));
    goodsCountLabel->setNormalizedPosition(Vec2(0.5, bottom));
    p_willBuyPanel->addChild(goodsCountLabel);
    
    auto goodsPriceLabel = Label::createWithSystemFont("= " + to_string( count * goods->getPrice()), SYSTEM_FONT, 22);
    goodsPriceLabel->setAnchorPoint(Vec2(1, 0));
    goodsPriceLabel->setNormalizedPosition(Vec2(0.65, bottom));
    p_willBuyPanel->addChild(goodsPriceLabel);
    
    auto cancel1Label = Label::createWithSystemFont("-", SYSTEM_FONT, 22);
    auto cancel1Button = MenuItemLabel::create(cancel1Label, [goods, count, this](cocos2d::Ref* pSender){
      this->willBuyGoods(goods, count - 1);
    });
    cancel1Button->setAnchorPoint(Vec2(1, 0));
    cancel1Button->setNormalizedPosition(Vec2(0.92, bottom));
    menu->addChild(cancel1Button);
    
    auto cancelLabel = Label::createWithSystemFont("×", SYSTEM_FONT, 22);
    auto cancelButton = MenuItemLabel::create(cancelLabel, [goods, this](cocos2d::Ref* pSender){
      this->willBuyGoods(goods, 0);
    });
    cancelButton->setAnchorPoint(Vec2(1, 0));
    cancelButton->setNormalizedPosition(Vec2(0.99, bottom));
    menu->addChild(cancelButton);
    
    bottom += 0.08;
    totalMoney += goods->getPrice() * count;
  }
  
  auto buyTotalLabel = Label::createWithSystemFont("购买合计", SYSTEM_FONT, 22);
  buyTotalLabel->setAnchorPoint(Vec2(0, 0));
  buyTotalLabel->setNormalizedPosition(Vec2(0.01, 0.01));
  p_willBuyPanel->addChild(buyTotalLabel);
  
  auto totalLabel = Label::createWithSystemFont("$" + to_string(totalMoney), SYSTEM_FONT, 22);
  totalLabel->setAnchorPoint(Vec2(1, 0));
  totalLabel->setNormalizedPosition(Vec2(0.99, 0.01));
  p_willBuyPanel->addChild(totalLabel);
  refreshFinalMoney();
}

void TradePanel::willSellGoods(TeamGoodsData* teamGoodsData, int num)
{
  if (num <= 0 && p_willSellDict.count(teamGoodsData)) {
    p_willSellDict.erase(teamGoodsData);
  } else {
    if (num >= teamGoodsData->getNum()) {
      num = teamGoodsData->getNum();
    }
    p_willSellDict[teamGoodsData] = num;
  }
  // refresh will buy area
  refreshWillSellPanel();
}


void TradePanel::refreshWillSellPanel()
{
  if (p_willSellPanel != nullptr) {
    p_willSellPanel->removeFromParent();
    p_willSellPanel = nullptr;
  }
  if (p_willSellDict.size() == 0) {
    return;
  }
  p_willSellPanel = Sprite::create();
  p_willSellPanel->setContentSize(p_sellPanel->getContentSize());
  p_willSellPanel->setNormalizedPosition(Vec2());
  p_willSellPanel->setAnchorPoint(Vec2());
  p_sellPanel->addChild(p_willSellPanel);
  
  auto menu = Menu::create();
  menu->setPosition(Vec2::ZERO);
  menu->setContentSize(p_willSellPanel->getContentSize());
  p_willSellPanel->addChild(menu);
  
  auto bottom = 0.09;
  auto totalMoney = 0;
  
  for (auto willSellGoodsPair : p_willSellDict) {
    auto goods = willSellGoodsPair.first;
    auto count = willSellGoodsPair.second;
    
    auto nameAndLevel = goods->getName() + "(Lv" + to_string(goods->getLevel()) + ")";
    auto goodsNameLabel = Label::createWithSystemFont(nameAndLevel, SYSTEM_FONT, 22);
    goodsNameLabel->setAnchorPoint(Vec2(0, 0));
    goodsNameLabel->setNormalizedPosition(Vec2(0.01, bottom));
    p_willSellPanel->addChild(goodsNameLabel);
    
    auto numberStr =  "× " + to_string(count);
    auto goodsCountLabel = Label::createWithSystemFont(numberStr, SYSTEM_FONT, 22);
    goodsCountLabel->setAnchorPoint(Vec2(1, 0));
    goodsCountLabel->setNormalizedPosition(Vec2(0.5, bottom));
    p_willSellPanel->addChild(goodsCountLabel);
    
    auto getSellPrice = goods->getSellPrice(p_cityData);
    auto goodsPriceLabel = Label::createWithSystemFont("= " + to_string(getSellPrice * count), SYSTEM_FONT, 22);
    goodsPriceLabel->setAnchorPoint(Vec2(1, 0));
    goodsPriceLabel->setNormalizedPosition(Vec2(0.65, bottom));
    p_willSellPanel->addChild(goodsPriceLabel);
    
    
    auto cancel1Label = Label::createWithSystemFont("-", SYSTEM_FONT, 22);
    auto cancel1Button = MenuItemLabel::create(cancel1Label, [goods, count, this](cocos2d::Ref* pSender){
      this->willSellGoods(goods, count - 1);
    });
    cancel1Button->setAnchorPoint(Vec2(1, 0));
    cancel1Button->setNormalizedPosition(Vec2(0.92, bottom));
    menu->addChild(cancel1Button);
    
    auto cancelAllLabel = Label::createWithSystemFont("×", SYSTEM_FONT, 22);
    auto cancelAllButton = MenuItemLabel::create(cancelAllLabel, [goods, this](cocos2d::Ref* pSender){
      this->willSellGoods(goods, 0);
    });
    cancelAllButton->setAnchorPoint(Vec2(1, 0));
    cancelAllButton->setNormalizedPosition(Vec2(0.99, bottom));
    menu->addChild(cancelAllButton);
    
    bottom += 0.08;
    totalMoney += getSellPrice * count;
  }
  
  auto sellTotalLabel = Label::createWithSystemFont("购买出售", SYSTEM_FONT, 22);
  sellTotalLabel->setAnchorPoint(Vec2(0, 0));
  sellTotalLabel->setNormalizedPosition(Vec2(0.01, 0.01));
  p_willSellPanel->addChild(sellTotalLabel);
  
  auto totalLabel = Label::createWithSystemFont("$" +to_string(totalMoney), SYSTEM_FONT, 22);
  totalLabel->setAnchorPoint(Vec2(1, 0));
  totalLabel->setNormalizedPosition(Vec2(0.99, 0.01));
  p_willSellPanel->addChild(totalLabel);
  refreshFinalMoney();
}


void TradePanel::refreshFinalMoney()
{
  auto money = p_teamData->getGuild()->getMoney();
  for (auto willSellGoodsPair : p_willSellDict) {
    auto goods = willSellGoodsPair.first;
    auto count = willSellGoodsPair.second;
    money += goods->getSellPrice(p_cityData) * count;
  }
  for (auto willBuyGoodsPair : p_willBuyDict) {
    auto goods = willBuyGoodsPair.first;
    auto count = willBuyGoodsPair.second;
    money -= goods->getPrice() * count;
  }
  p_finalMoney->setString("结算：$" + to_string(money));
}


void TradePanel::clickConfirm(cocos2d::Ref* pSender)
{
  auto totalMoney = p_teamData->getGuild()->getMoney();
  for (auto willSellGoodsPair : p_willSellDict) {
    auto goods = willSellGoodsPair.first;
    auto count = willSellGoodsPair.second;
    totalMoney += goods->getSellPrice(p_cityData) * count;
  }
  for (auto willBuyGoodsPair : p_willBuyDict) {
    auto goods = willBuyGoodsPair.first;
    auto count = willBuyGoodsPair.second;
    totalMoney -= goods->getPrice() * count;
  }
  if (totalMoney < 0) {
    QuickAlert::createAlertWithMsg("金钱不足", Color4B::RED);
    return;
  }
  p_panel->removeFromParent();
  
  // 进行交易
  p_teamData->sellGoodsInCity(p_willSellDict, p_cityData);
  p_teamData->buyGoodsInCity(p_willBuyDict, p_cityData);
  p_teamData->getGuild()->setMoney(totalMoney);
  QuickAlert::createAlertWithMsg("交易成功", Color4B::GREEN);
}

void TradePanel::clickClose(cocos2d::Ref* pSender)
{
  p_panel->removeFromParent();
}
