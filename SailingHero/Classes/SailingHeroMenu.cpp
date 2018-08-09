//
//  SailingHeroMenu.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 5/16/18.
//

#include "SailingHeroMenu.hpp"

#include "SimpleAudioEngine.h"
#include "SystemButton.hpp"
#include "LocalizationHelper.hpp"
#include "SHDataManager.hpp"
#include "SelectHeroMenuScene.hpp"

#include "SHColorNode.hpp"
#include <string>
#include <vector>

USING_NS_CC;
using namespace ui;

Scene* SailingHeroMenu::createScene()
{
  return SailingHeroMenu::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
  printf("Error while loading: %s\n", filename);
  printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SailingHeroMenu.cpp\n");
}

SailingHeroMenu::SailingHeroMenu()
{
  
}

// on "init" you need to initialize your instance
bool SailingHeroMenu::init()
{
  //////////////////////////////
  // 1. super init first
  if ( !Scene::init() )
  {
    return false;
  }
  this->setBackgroundImage("res/default_background.png");
  this->setBackgroundMusic("title.mp3");
  this->setFullScreenCover();
  
  Vec2 origin = Director::getInstance()->getVisibleOrigin();
  
  auto strs = std::vector<std::string>({"start_game", "load_game", "game_setting"});
  auto buttons = vector<Button *>({
    SystemButton::defaultButtonWithText(LocalizationHelper::getLocalization("start_game"),
                                        CC_CALLBACK_1(SailingHeroMenu::clickStartGame, this)),
    SystemButton::defaultButtonWithText(LocalizationHelper::getLocalization("load_game"),
                                        CC_CALLBACK_1(SailingHeroMenu::clickLoadGame, this)),
    SystemButton::defaultButtonWithText(LocalizationHelper::getLocalization("game_setting"),
                                        CC_CALLBACK_1(SailingHeroMenu::clickGameSetting, this)),
    SystemButton::defaultButtonWithText(LocalizationHelper::getLocalization("test 1"),
                                        CC_CALLBACK_1(SailingHeroMenu::clickTest1, this)),
    SystemButton::defaultButtonWithText(LocalizationHelper::getLocalization("test 2"),
                                        CC_CALLBACK_1(SailingHeroMenu::clickTest2, this)),
    SystemButton::defaultButtonWithText(LocalizationHelper::getLocalization("test 3"),
                                        CC_CALLBACK_1(SailingHeroMenu::clickTest3, this)),
    
  });
  auto node = SystemButton::getButtonGroupNode(buttons);
  this->addChild(node);
  
  return true;
}

void SailingHeroMenu::clickStartGame(cocos2d::Ref* pSender)
{
  auto scene = SelectHeroMenuScene::createScene();
  Director::getInstance()->pushScene(scene);
}

void SailingHeroMenu::clickLoadGame(cocos2d::Ref* pSender)
{
}

void SailingHeroMenu::clickGameSetting(Ref* pSender)
{
}

#include "HeroData.hpp"
#include "GoodsData.hpp"
#include "CityData.hpp"
#include "SHCityDataHelper.hpp"
#include "DialogPhotoFrame.hpp"
#include "SailMapScene.hpp"

void SailingHeroMenu::clickTest1(cocos2d::Ref* pSender)
{
  GameData::getSharedInstance()->setCityId("69");
  auto mapScene = SailMapScene::createScene();
  Director::getInstance()->pushScene(mapScene);
}

#include "MultiSelectionFrame.hpp"
#include "ShipData.hpp"
#include "ShipTeamData.hpp"
#include "ShipStyleData.hpp"
#include "CannonData.hpp"
#include "GoodsPricePercentData.hpp"

void SailingHeroMenu::clickTest2(cocos2d::Ref* pSender)
{
//  auto frame = MultiSelectionFrame::createMultiSelectFrame({"1", "2", "3", "4"}, 3, [](vector<int> selectIndexes){
//    for (auto index : selectIndexes) {
//      CCLOG("selected : %d", index);
//    }
//  });
//  this->addChild(frame);
  GoodsPricePercentData::setGoodsPricePercent(1, 1, 34);
  SHDataManager::saveData(1);
}

#include "CityScene.hpp"
#include "DialogFrame.hpp"
#include "GoodsBasePriceData.hpp"

void SailingHeroMenu::clickTest3(Ref* pSender)
{
//  auto size = GoodsData::getSharedDictionary()->size();
//  auto goods = GoodsData::getGoodsDataById(arc4random() % size);
//  size = CultureData::getSharedDictionary()->size();
//  auto culture = CultureData::getCultureDataById(arc4random() % size);
//  CCLOG("price of goods : %s in  culture : %s, is %d", goods->getGoodsName().c_str(), culture->getCultureName().c_str(), GoodsBasePriceData::getGoodsBasePrice(goods->getGoodsId(), culture->getCutureId()));
  SHDataManager::loadData(1);
  auto val = GoodsPricePercentData::getGoodsPricePercent(1, 1);
  CCLOG("======== %d", val);
  
//  auto shipDic = ShipData::getSharedDictionary();
//  for (auto iter : *shipDic) {
//    CCLOG("ship : %s ", iter.second->description().c_str());
//  }
//  SaveDataManager::loadData(1);
//  SHDataManager::loadData(2);
//  auto scene = CityScene::createScene();
//  scene->setCityDataId(0);
//  Director::getInstance()->pushScene(scene);
}


