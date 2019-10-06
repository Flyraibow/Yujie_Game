//
//  MenuScene.cpp
//  YJStartWithNothing
//
//  Created by Yujie Liu on 10/4/19.
//

#include "MenuScene.hpp"

#include "SimpleAudioEngine.h"
#include "GameManager.hpp"

USING_NS_CC;

Scene* MenuScene::createScene()
{
  return MenuScene::create();
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
  //////////////////////////////
  // 1. super init first
  if ( !Scene::init() )
  {
      return false;
  }
  p_background = nullptr;
  p_front = nullptr;
  
  restart();
  return true;
}


void MenuScene::restart()
{
  // clear everything.
  if (p_background != nullptr) {
    p_background->removeFromParent();
  }
  if (p_front != nullptr) {
    p_front->removeFromParent();
  }
  
  
  p_background = BackgroundContainer::create();
  p_front = FrontContainer::create();
  GameManager::getInstance()->setContainers(p_background, p_front);

  auto visibleSize = Director::getInstance()->getVisibleSize();
  Vec2 origin = Director::getInstance()->getVisibleOrigin();
  
  auto layer = LayerColor::create(Color4B::WHITE, visibleSize.width, visibleSize.height);
  layer->setPosition(origin);
  this->addChild(layer);
  p_background->setContentSize(visibleSize);
  p_background->setPosition(origin);
  p_front->setContentSize(visibleSize);
  p_front->setPosition(origin);
  p_background->setAnchorPoint(Vec2());
  p_front->setAnchorPoint(Vec2());
  this->addChild(p_background, 1);
  this->addChild(p_front, 100);
  
  p_background->initTitle();
}
