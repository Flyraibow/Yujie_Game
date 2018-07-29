//
//  CitySceneFrame.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 7/18/18.
//

#include "CitySceneFrame.hpp"

#include "LocalizationHelper.hpp"
#include "SHCityDataHelper.hpp"
#include "SHGameDataHelper.hpp"
#include "GameData.hpp"
#include "SystemButton.hpp"
#include "CityBuildingFrame.hpp"

static const int MAX_GOODS_NUM = 5;
static const int MAX_GUILD_NUM = 3;

CitySceneFrame::CitySceneFrame()
{
  p_townPhoto = nullptr;
  p_background = Node::create();
  p_sprite = Sprite::create("res/base/frame/citySceneFrame.png");
  p_background->setContentSize(p_sprite->getContentSize());
  p_background->addChild(p_sprite, 1);
  
  Vec2 origin = Director::getInstance()->getVisibleOrigin();
  auto visibleSize = Director::getInstance()->getVisibleSize();
  p_scale = visibleSize.height / p_sprite->getContentSize().height;
  p_sprite->setScale(p_scale);
  p_sprite->setAnchorPoint(Vec2(0, 0));
  p_sprite->setNormalizedPosition(Vec2(0, 0));
  
  p_labCityName = createLabelWithScale(Vec2(0.792, 0.933));
  p_labCityType = createLabelWithScale(Vec2(0.792, 0.866));
  p_labCulture = createLabelWithScale(Vec2(0.86, 0.866));
  p_labCommerce = createLabelWithScale(Vec2(0.792, 0.802),Vec2(), LocalizationHelper::getLocalization("tag_commerce"));
  p_labMilitary = createLabelWithScale(Vec2(0.792, 0.75),Vec2(), LocalizationHelper::getLocalization("tag_military"));
  p_labCommerceValue = createLabelWithScale(Vec2(0.97, 0.802), Vec2(1, 0));
  p_labMilitaryValue = createLabelWithScale(Vec2(0.97, 0.75), Vec2(1, 0));
  p_labCityStatus = createLabelWithScale(Vec2(0.88, 0.701), Vec2(0.5, 0));
  p_labGoodsTag = createLabelWithScale(Vec2(0.81, 0.35),Vec2(), LocalizationHelper::getLocalization("tag_goods"));
  p_labData = createLabelWithScale(Vec2(0.88, 0.05),Vec2(0.5, 0.5), "2月3日", 20);
  
  for (int i = 0; i < MAX_GOODS_NUM; ++i) {
    auto label = createLabelWithScale(Vec2(0.792, 0.302 - i * 0.0498),Vec2(), LocalizationHelper::getLocalization("tag_goods"));
    p_labGoodsList.push_back(label);
  }
  for (int i = 0; i < MAX_GUILD_NUM; ++i) {
    auto label = createLabelWithScale(Vec2(0.792, 0.65 - i * 0.1),Vec2(), LocalizationHelper::getLocalization("tag_goods"));
    p_labGuildList.push_back(label);
  }
  for (int i = 0; i < MAX_GUILD_NUM; ++i) {
    auto label = createLabelWithScale(Vec2(0.968, 0.60 - i * 0.1),Vec2(1,0), LocalizationHelper::getLocalization("tag_goods"));
    p_labGuildShareList.push_back(label);
  }
  
  p_systemBarFrame.setTextScale(1/p_scale);
  auto systemBarSprite = p_systemBarFrame.getSprite();
  systemBarSprite->setAnchorPoint(Vec2(0, 0));
  systemBarSprite->setNormalizedPosition(Vec2());
  p_sprite->addChild(systemBarSprite);
  
  auto moneySprite = p_moneyFrame.getSprite();
  p_moneyFrame.setGuildData(GameData::getSharedInstance()->getGuildData());
  moneySprite->setAnchorPoint(Vec2(1, 0));
  moneySprite->setNormalizedPosition(Vec2(0.75, 0.083));
  p_sprite->addChild(moneySprite);
  
//  auto button1 = SystemButton::defaultButtonWithText(LocalizationHelper::getLocalization("test 2"),
//                                                     CC_CALLBACK_1(CitySceneFrame::clickTest2, this));
//  button1->setAnchorPoint(Vec2(0, 0));
//  button1->setNormalizedPosition(Vec2(0, 0.7));
//  p_sprite->addChild(button1);
//  auto button2 = SystemButton::defaultButtonWithText(LocalizationHelper::getLocalization("test 3"),
//                                                     CC_CALLBACK_1(CitySceneFrame::clickTest3, this));
//  button2->setAnchorPoint(Vec2(0, 0));
//  button2->setNormalizedPosition(Vec2(0, 0.3));
//  p_sprite->addChild(button2);
}

Label* CitySceneFrame::createLabelWithScale(Vec2 position, Vec2 anchor, string text, int textSize)
{
  auto label = Label::createWithSystemFont(text, "Helvetica", textSize);
  label->setScale(1 / p_scale);
  label->setAnchorPoint(anchor);
  label->setNormalizedPosition(position);
  p_sprite->addChild(label);
  return label;
}

void CitySceneFrame::setCityData(CityData *cityData)
{
  p_cityData = cityData;
  refresh();
}

void CitySceneFrame::refresh()
{
  // show city informations
  p_labCityName->setString(p_cityData->getCityName());
  p_labCityType->setString(p_cityData->getCityTypeData()->getCityTypeName());
  p_labCulture->setString(p_cityData->getCultureData()->getCultureName());
  p_labMilitaryValue->setString(to_string(p_cityData->getMilltary()));
  p_labCommerceValue->setString(to_string(p_cityData->getCommerce()));
  p_labCityStatus->setString(p_cityData->getCityStatusData()->getCityStatusName());
  
  // show goods names
  auto goodsList = p_cityData->getCityGoodsDataVector();
  int index = 0;
  for (int i = 0; i < goodsList.size(); ++i) {
    auto cityGoods = goodsList[i];
    if (!cityGoods->getIsHidden()) {
      p_labGoodsList[index++]->setString(cityGoods->getGoodsData()->getGoodsName());
    }
  }
  for (int i = index; i < MAX_GOODS_NUM; ++i) {
    p_labGoodsList[index++]->setString("");
  }
  
  // show guild shares
  auto guildShareList = getOrderedCityGuildShares(p_cityData);
  index = 0;
  for (int i = 0; i < guildShareList.size(); ++i) {
    p_labGuildList[index]->setString(guildShareList.at(i).first->getGuildName());
    p_labGuildShareList[index++]->setString(to_string(guildShareList.at(i).second) + "%");
  }
  for (int i = index; i < MAX_GUILD_NUM; ++i) {
    p_labGuildList[index]->setString("");
    p_labGuildShareList[index++]->setString("");
  }
  p_labData->setString(getGameDate());
  
  // show city icons
  // TODO: NOW it doesn't change when switch cities. or city updates
  auto buildingDataSet = p_cityData->getBuildingDataSet();
  for (auto buildingData : buildingDataSet) {
    if (p_buildingImageMap.count(buildingData->getBuildingId())) {
      auto buildingSprite = p_buildingImageMap.at(buildingData->getBuildingId());
      buildingSprite->setVisible(true);
    } else {
      auto buildingFrame = CityBuildingFrame(buildingData);
      auto buildingSprite = buildingFrame.getSprite();
      p_buildingImageMap[buildingData->getBuildingId()] = buildingSprite;
      p_sprite->addChild(buildingSprite);
    }
  }
  if (p_townPhoto != nullptr) {
    p_townPhoto->removeFromParent();
  }
  p_townPhoto = p_cityData->getBackGroundData()->getTownPhotoImage();
  p_townPhoto->setAnchorPoint(Vec2());
  p_townPhoto->setNormalizedPosition(Vec2());
  p_townPhoto->setScale(p_scale);
  p_background->addChild(p_townPhoto);
}

Node* CitySceneFrame::getSprite() const
{
  return p_background;
}

////#include "SaveDataManager.hpp"
////#include "Calendar.hpp"
//#include "DialogFrame.hpp"
////
//void CitySceneFrame::clickTest2(cocos2d::Ref* pSender)
//{
//
//  auto dialog = DialogFrame::createWithDialogIds({"1", "2", "3"}, [](){
//    CCLOG("对话结束 了");
//  }, p_sprite->getContentSize());
//
//  p_sprite->addChild(dialog->getSprite());
////  auto gameData = GameData::getSharedInstance();
////  auto date = nextDay(gameData->getYear(), gameData->getMonth(), gameData->getDay());
////  gameData->setYear(date.year);
////  gameData->setMonth(date.month);
////  gameData->setDay(date.day);
////  refresh();
//}
////
////#include "CityScene.hpp"
////
//void CitySceneFrame::clickTest3(Ref* pSender)
//{
//  //  SaveDataManager::loadData(1);
//  Director::getInstance()->popScene();
//}

