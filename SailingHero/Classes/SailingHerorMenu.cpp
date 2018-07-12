//
//  SailingHerorMenu.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 5/16/18.
//

#include "SailingHerorMenu.hpp"

#include "SimpleAudioEngine.h"
#include "SystemButton.hpp"
#include "LocalizationHelper.hpp"
#include "SaveDataManager.hpp"

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
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
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

    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto strs = std::vector<std::string>({"start_game", "load_game", "game_setting"});
    auto buttons = Vector<Button *>({
        SystemButton::defaultButtonWithText(LocalizationHelper::getLocalization("start_game"),
                                            CC_CALLBACK_1(SailingHeroMenu::clickStartGame, this)),
        SystemButton::defaultButtonWithText(LocalizationHelper::getLocalization("load_game"),
                                            CC_CALLBACK_1(SailingHeroMenu::clickLoadGame, this)),
        SystemButton::defaultButtonWithText(LocalizationHelper::getLocalization("game_setting"),
                                            CC_CALLBACK_1(SailingHeroMenu::clickGameSetting, this)),
        
    });
    auto node = SystemButton::getButtonGroupNode(buttons);
    this->addChild(node);
    
    return true;
}

#include "HeroData.hpp"
void SailingHeroMenu::clickStartGame(cocos2d::Ref* pSender)
{
  HeroData *hero = HeroData::getHeroDataById("1");
  hero->setHeroFirstName("予杰");
  hero->setLevel(arc4random() % 100);
  SaveDataManager::saveData(1);
}

void SailingHeroMenu::clickLoadGame(cocos2d::Ref* pSender)
{
  HeroData *hero = HeroData::getHeroDataById("1");
  printf("%s\n", hero->description().c_str());
}

#include "GoodsData.hpp"

void SailingHeroMenu::clickGameSetting(Ref* pSender)
{
  SaveDataManager::clearData();
  
//    auto id = arc4random() % 114;
//    printf("%d\n", id);
//    auto goodData = GoodsData::getGoodsDataById(to_string(id));
//    printf("%s\n", goodData->description().c_str());
//    printf("%s\n", goodData->getGoodsCategoryData()->description().c_str());
//    printf("%s\n", goodData->getGoodsCategoryData()->getCategoryUpdateData()->description().c_str());
}

