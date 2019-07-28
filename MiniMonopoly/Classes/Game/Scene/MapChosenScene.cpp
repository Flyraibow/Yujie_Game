//
//  MapChosenScene.cpp
//  MiniMonopoly
//
//  Created by Yujie Liu on 7/20/19.
//

#include "MapChosenScene.hpp"
#include "LevelManager.hpp"

USING_NS_CC;

Scene* MapChosenScene::createScene()
{
  return MapChosenScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
  printf("Error while loading: %s\n", filename);
  printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MapChosenScene::init()
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
  
  auto label = Label::createWithTTF("Choose Level", "fonts/Marker Felt.ttf", 40);
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
  
  Label *returnLabel = Label::createWithTTF("Return", "fonts/Marker Felt.ttf", 24);
  auto menuItemLabel = MenuItemLabel::create(returnLabel, CC_CALLBACK_1(MapChosenScene::popScene, this));
  float x = origin.x + menuItemLabel->getContentSize().width / 2;
  float y = origin.y + menuItemLabel->getContentSize().height / 2;
  menuItemLabel->setPosition(Vec2(x,y));
  
  // create menu, it's an autorelease object
  auto menu = Menu::create(menuItemLabel, NULL);
  menu->setPosition(Vec2::ZERO);
  this->addChild(menu, 1);
  
  _showLevelsMethod1();

  return true;
}

void MapChosenScene::popScene(cocos2d::Ref* pSender)
{
  Director::getInstance()->popScene();
}

void MapChosenScene::_showLevelsMethod1()
{
  static const int kMaxLevelsPerLine = 3;

  // 显示所有的关卡
  Vector<MenuItem *> levelIcons;
  auto levels = getAllLevelInfo();
  for (int i = 0; i < levels.size(); ++i) {
    int rows = i / kMaxLevelsPerLine;
    int cols = i % kMaxLevelsPerLine;
    auto levelData = levels[i];
    auto iconPath = levelData->getIconPath();
    auto icon = MenuItemImage::create(iconPath, iconPath, CC_CALLBACK_1(MapChosenScene::_clickLevel, this));
    float x = 1.0 / (kMaxLevelsPerLine + 1) * (cols + 1);
    float y = 0.8 - 0.3 * (rows + 1);
    icon->setAnchorPoint(Vec2(0.5, 0));
    icon->setNormalizedPosition(Vec2(x, y));
    levelIcons.pushBack(icon);
    auto levelName = Label::createWithSystemFont(levelData->getName(), "Helvetica", 24);
    levelName->setAnchorPoint(Vec2(0.5, 1));
    levelName->setNormalizedPosition(Vec2(x, y));
    this->addChild(levelName);
    icon->setName(levelData->getId());
    delete levelData;
  }
  auto menu = Menu::createWithArray(levelIcons);
  menu->setPosition(Vec2::ZERO);
  this->addChild(menu);
  levels.clear();
}

void MapChosenScene::_clickLevel(cocos2d::Ref* pSender)
{
  auto btn = dynamic_cast<MenuItem*>(pSender);
  CCLOG("click %s", btn->getName().c_str() );
}
