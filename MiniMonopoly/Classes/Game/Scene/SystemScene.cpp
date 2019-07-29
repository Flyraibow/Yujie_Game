//
//  SystemScene.cpp
//  MiniMonopoly
//
//  Created by Yujie Liu on 7/28/19.
//

#include "SystemScene.hpp"
#include "GameManager.hpp"


USING_NS_CC;

Scene* SystemScene::createScene()
{
  return SystemScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
  printf("Error while loading: %s\n", filename);
  printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool SystemScene::init()
{
  //////////////////////////////
  // 1. super init first
  if ( !Scene::init() )
  {
    return false;
  }
  
  auto visibleSize = Director::getInstance()->getVisibleSize();
  Vec2 origin = Director::getInstance()->getVisibleOrigin();
  
  Label* resume = Label::createWithSystemFont("Resume Game", "Helvetica", 30);
  auto btnResume = MenuItemLabel::create(resume, CC_CALLBACK_1(SystemScene::resume, this));
  btnResume->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 0.7);
  
  Label* restart = Label::createWithSystemFont("Restart Game", "Helvetica", 30);
  auto btnRestart = MenuItemLabel::create(restart, CC_CALLBACK_1(SystemScene::restartLevel, this));
  btnRestart->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 0.5);
  
  Label* quit = Label::createWithSystemFont("Quit Level", "Helvetica", 30);
  auto btnQuit = MenuItemLabel::create(quit, CC_CALLBACK_1(SystemScene::quitLevel, this));
  btnQuit->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height * 0.3);
  
  auto menu = Menu::create(btnResume, btnRestart, btnQuit, NULL);
  menu->setPosition(Vec2::ZERO);
  this->addChild(menu);
  
  return true;
}

void SystemScene::quitLevel(cocos2d::Ref* pSender)
{
  Director::getInstance()->popToSceneStackLevel(2);
}

void SystemScene::resume(cocos2d::Ref* pSender)
{
  Director::getInstance()->popScene();
}

void SystemScene::restartLevel(cocos2d::Ref* pSender)
{
  Director::getInstance()->popScene();
  GameManager::getSharedInstance()->restartLevel();
}
