//
//  SelectHeroMenu.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 5/16/18.
//

#include "SelectHeroMenu.hpp"

#include "SystemButton.hpp"
#include "LocalizationHelper.hpp"
#include "HeroSelectingFrame.hpp"
#include "SHSpriteListener.hpp"
#include "HeroSelectData.hpp"


USING_NS_CC;
using namespace ui;

Scene* SelectHeroMenu::createScene()
{
  return SelectHeroMenu::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
  printf("Error while loading: %s\n", filename);
  printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

static void setEventListenerForSprite(Sprite *sprite, HeroSelectData *selectData)
{
  auto listener = SHSpriteListener::createWithNode(sprite);

  // trigger when moving touch
  auto touchEnd = [selectData](Touch* touch, Event* event){
    CCLOG("select %s", selectData->getHeroData()->getHeroFirstName().c_str());
  };
  listener->setTouchOver(nullptr, nullptr);
  listener->setTouchEnd(touchEnd, nullptr);
}

// on "init" you need to initialize your instance
bool SelectHeroMenu::init()
{
  //////////////////////////////
  // 1. super init first
  if ( !Scene::init() )
  {
    return false;
  }
  
  this->setBackgroundImage("res/default_background.png");
  
  Vec2 origin = Director::getInstance()->getVisibleOrigin();
  auto visibleSize = Director::getInstance()->getVisibleSize();
  
  auto heroList = HeroSelectData::getSharedDictionary();
  int index = 0;
  for (auto iter = heroList->begin(); iter != heroList->end(); ++iter, index++) {
    
    auto peoplePanel = HeroSelectingFrame::createWithSelectHeroId(iter->first);
    setEventListenerForSprite(peoplePanel, iter->second);
    
    peoplePanel->setPosition(Vec2(origin.x + visibleSize.width / 2  - 100 + index * 200, origin.y + visibleSize.height / 2));
    this->addChild(peoplePanel);
  }
  
  
  auto btnCancel = SystemButton::defaultButtonWithText(LocalizationHelper::getLocalization("sys_cancel"),
                                                       CC_CALLBACK_1(SelectHeroMenu::clickCancelButton, this));
  
  btnCancel->setAnchorPoint(Vec2(1,0));
  btnCancel->setPosition(Vec2(origin.x + visibleSize.width - 15, origin.y + 12));

  this->addChild(btnCancel);
  
  return true;
}

void SelectHeroMenu::clickCancelButton(cocos2d::Ref* pSender)
{
  Director::getInstance()->popScene();
}


