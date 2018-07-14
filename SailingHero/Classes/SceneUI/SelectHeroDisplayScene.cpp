//
//  SelectHeroDisplayScene.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 7/14/18.
//

#include "SelectHeroDisplayScene.hpp"
#include "SystemButton.hpp"
#include "LocalizationHelper.hpp"
#include "HeroSelectingFrame.hpp"

USING_NS_CC;
using namespace ui;

Scene* SelectHeroDisplayScene::createScene(HeroSelectData *selectHeroData)
{
  auto scene = SelectHeroDisplayScene::create();
  scene->setSelectHeroData(selectHeroData);
  return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
  printf("Error while loading: %s\n", filename);
  printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool SelectHeroDisplayScene::init()
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

  auto btnCancel = SystemButton::defaultButtonWithText(LocalizationHelper::getLocalization("sys_cancel"), [](cocos2d::Ref* pSender) {
    Director::getInstance()->popScene();
  });
  btnCancel->setAnchorPoint(Vec2(1,0));
  btnCancel->setPosition(Vec2(origin.x + visibleSize.width - 15, origin.y + 12));
  
  this->addChild(btnCancel);
  
  return true;
}

void SelectHeroDisplayScene::setSelectHeroData(HeroSelectData *selectHeroData)
{
  auto peoplePanel = HeroSelectingFrame::createBigPhotoWithSelectHeroId(selectHeroData->getSelectHeroId());
  Vec2 origin = Director::getInstance()->getVisibleOrigin();
  auto visibleSize = Director::getInstance()->getVisibleSize();
  peoplePanel->setPosition(Vec2(origin.x + visibleSize.width / 2  - 120, origin.y + visibleSize.height / 2));
  this->addChild(peoplePanel);
  
//  auto label = Label::createWithTTF(, "fonts/Marker Felt.ttf", 24);
  
  auto btnChangeHeroName = SystemButton::defaultButtonWithText(LocalizationHelper::getLocalization("change_hero_name"), [](cocos2d::Ref* pSender) {
                                                       });
  auto btnChangeGuildName = SystemButton::defaultButtonWithText(LocalizationHelper::getLocalization("change_guild_name"), [](cocos2d::Ref* pSender) {
  });
  auto btnChangeHeroBirth = SystemButton::defaultButtonWithText(LocalizationHelper::getLocalization("change_hero_birth"), [](cocos2d::Ref* pSender) {
  });
  
}
