//
//  MenuScene.cpp
//  MiniMonopoly
//
//  Created by Yujie Liu on 7/20/19.
//

#include "MenuScene.hpp"


USING_NS_CC;

Scene* MenuScene::createScene()
{
  return MenuScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
  printf("Error while loading: %s\n", filename);
  printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
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
  
  auto visibleSize = Director::getInstance()->getVisibleSize();
  Vec2 origin = Director::getInstance()->getVisibleOrigin();

  /////////////////////////////
  // 3. add your codes below...
  
  // add a label shows "Hello World"
  // create and initialize a label
  
  auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 40);
  if (label == nullptr)
  {
    problemLoading("'fonts/Marker Felt.ttf'");
  }
  else
  {
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
  }
  
  // add "HelloWorld" splash screen"
  auto sprite = Sprite::create("HelloWorld.png");
  if (sprite == nullptr)
  {
    problemLoading("'HelloWorld.png'");
  }
  else
  {
    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
  }
  
  Label *startGameLabel = Label::createWithTTF("Start Game", "fonts/Marker Felt.ttf", 24);
  auto menuItemLabel = MenuItemLabel::create(startGameLabel, CC_CALLBACK_1(MenuScene::clickStartGame, this));
  float x = origin.x + visibleSize.width/2;
  float y = origin.y + visibleSize.height * 0.3;
  menuItemLabel->setPosition(Vec2(x,y));
  
  // create menu, it's an autorelease object
  auto menu = Menu::create(menuItemLabel, NULL);
  menu->setPosition(Vec2::ZERO);
  this->addChild(menu, 1);
  
  return true;
}

#include "MapChosenScene.hpp"

void MenuScene::clickStartGame(cocos2d::Ref* pSender)
{
  auto scene = MapChosenScene::create();
  Director::getInstance()->pushScene(scene);
}
