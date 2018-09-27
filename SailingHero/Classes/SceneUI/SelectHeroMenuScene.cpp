//
//  SelectHeroMenu.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 5/16/18.
//

#include "SelectHeroMenuScene.hpp"

#include "SystemButton.hpp"
#include "LocalizationHelper.hpp"
#include "HeroSelectingFrame.hpp"
#include "SHSpriteListener.hpp"
#include "HeroSelectData.hpp"
#include "SelectHeroDisplayScene.hpp"
#include "SHDataManager.hpp"


USING_NS_CC;
using namespace ui;

SHScene* SelectHeroMenuScene::createScene()
{
  return SelectHeroMenuScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
  printf("Error while loading: %s\n", filename);
  printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SelectHeroMenuScene.cpp\n");
}

static void setEventListenerForSprite(Sprite *sprite, HeroSelectData *selectData)
{
  auto listener = SHSpriteListener::createWithNode(sprite);

  // trigger when moving touch
  auto touchEnd = [selectData](Touch* touch, Event* event){
    SHDataManager::clearData();
    auto scene = SelectHeroDisplayScene::createScene(selectData);
    Director::getInstance()->pushScene(scene);
  };
  listener->setTouchOver(nullptr, nullptr);
  listener->setTouchEnd(touchEnd, nullptr);
}

// on "init" you need to initialize your instance
bool SelectHeroMenuScene::init()
{
  //////////////////////////////
  // 1. super init first
  if ( !SHScene::init() )
  {
    return false;
  }
  initSceneWithJson("selectHeroMenu");
  
  Vec2 origin = Director::getInstance()->getVisibleOrigin();
  auto visibleSize = Director::getInstance()->getVisibleSize();
  
  auto heroList = HeroSelectData::getSharedDictionary();
  int index = 0;
  for (auto iter = heroList->begin(); iter != heroList->end(); ++iter, index++) {
    
    auto peoplePanel = HeroSelectingFrame::createWithSelectHeroId(to_string(iter->first));
    setEventListenerForSprite(peoplePanel, iter->second);
    
    peoplePanel->setPosition(Vec2(origin.x + visibleSize.width / 2  - 100 + index * 200, origin.y + visibleSize.height / 2));
    this->addChild(peoplePanel);
  }
  
  return true;
}


