//
//  TestScene.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 8/14/18.
//

#include "TestScene.hpp"
#include "SystemButton.hpp"

USING_NS_CC;
using namespace ui;

TestScene* TestScene::createScene()
{
  return TestScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
  printf("Error while loading: %s\n", filename);
  printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in CityScene.cpp\n");
}

// on "init" you need to initialize your instance
bool TestScene::init()
{
  //////////////////////////////
  // 1. super init first
  if ( !Scene::init())
  {
    return false;
  }
  this->setFullScreenCover();
  this->setBackgroundImage("res/default_background.png");
  
  auto buttonList = {
    SystemButton::defaultButtonWithText("测试航海图",  CC_CALLBACK_1(TestScene::testSailMap, this)),
    SystemButton::defaultButtonWithText("返回",  CC_CALLBACK_1(TestScene::clickBack, this)),
  };
  
  auto node = SystemButton::getButtonGroupNode(buttonList);
  this->addChild(node);
  
  return true;
}

void TestScene::clickBack(cocos2d::Ref* pSender)
{
  Director::getInstance()->popScene();
}

#include "GameData.hpp"
#include "SailMapScene.hpp"

void TestScene::testSailMap(cocos2d::Ref* pSender)
{
  GameData::getSharedInstance()->setCityId("69");
  auto mapScene = SailMapScene::createScene();
  Director::getInstance()->pushScene(mapScene);
}

