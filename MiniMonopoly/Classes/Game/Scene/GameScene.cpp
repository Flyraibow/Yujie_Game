//
//  GameScene.cpp
//  MiniMonopoly
//
//  Created by Yujie Liu on 7/20/19.
//

#include "GameScene.hpp"
#include "GameManager.hpp"


GameScene* GameScene::createScene(const std::string &levelId)
{
  auto gameScene = GameScene::create();
  gameScene->initWithLevelId(levelId);
  return gameScene;
}

GameScene::~GameScene()
{
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
  printf("Error while loading: %s\n", filename);
  printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::initWithLevelId(const std::string &levelId)
{
  //////////////////////////////
  // 1. super init first
  if ( !Scene::init() )
  {
    return false;
  }
  p_gameManager = GameManager::getSharedInstance()->setLevelId(levelId);
  p_map = Sprite::create(p_gameManager->getLevelData()->getMapPath());
  p_map->setNormalizedPosition(Vec2(0.5, 0.5));
  auto visibleSize = Director::getInstance()->getVisibleSize();
  Vec2 origin = Director::getInstance()->getVisibleOrigin();
  auto scaleX = visibleSize.width / p_map->getContentSize().width;
  auto scaleY = visibleSize.height / p_map->getContentSize().height;
  p_map->setScale(fmin(scaleX, scaleY));
  this->addChild(p_map);
  
  static const string SYSTEM_ICON_PATH = "res/Graph/Icon/systemIcon.png";
  auto sIcon = MenuItemImage::create(SYSTEM_ICON_PATH, SYSTEM_ICON_PATH);
  sIcon->setAnchorPoint(Vec2(1, 0));
  sIcon->setPosition(Vec2(origin.x + visibleSize.width, origin.y));
  sIcon->setCallback(CC_CALLBACK_1(GameScene::clickSystem, this));
  
  p_speedLab = Label::createWithSystemFont("× 1", "Helvetica", 30);
  p_speedMenuItem = MenuItemLabel::create(p_speedLab, CC_CALLBACK_1(GameScene::clickSpeed, this));
  p_speedMenuItem->setAnchorPoint(Vec2(1, 0));
  p_speedMenuItem->setPosition(Vec2(origin.x + visibleSize.width - sIcon->getContentSize().width - 10, origin.y));
  
  auto menu = Menu::create(sIcon, p_speedMenuItem, NULL);
  menu->setPosition(Vec2::ZERO);
  this->addChild(menu, 2);
  
  p_mapMenu = Menu::create();
  p_mapMenu->setPosition(Vec2::ZERO);
  p_map->addChild(p_mapMenu);
  
  this->showCityOnMap();
  
  return true;
}

void GameScene::showCityOnMap()
{
  auto cities = p_gameManager->getLevelData()->getCities();
  float cityWidth = 0.03 * Director::getInstance()->getVisibleSize().width;
  auto mapSize = p_map->getContentSize();
  for (auto city : cities) {
    auto icon = city->getIcon();
    auto cityButton = MenuItemImage::create(icon, icon, CC_CALLBACK_1(GameScene::clickCity, this));
    cityButton->setName(city->getId());
    cityButton->setScale(cityWidth / cityButton->getContentSize().width);
    auto pos = city->getPosition();
    cityButton->setPosition(mapSize.width * pos.first, mapSize.height * pos.second);
    p_mapMenu->addChild(cityButton);
  }
}


void GameScene::clickCity(cocos2d::Ref* pSender)
{
  auto btn = dynamic_cast<MenuItem*>(pSender);
  auto cityId = btn->getName();
  CCLOG("click city : %s", cityId.c_str());
}

#include "SystemScene.hpp"

void GameScene::clickSpeed(cocos2d::Ref* pSender)
{
  if (p_gameManager) {
    int speed = p_gameManager->getGameSpeed() * 2;
    if (speed >= 8) {
      speed = 1;
    }
    p_speedLab->setString("× " + to_string(speed));
    p_gameManager->setGameSpeed(speed);
    p_gameManager->setPaused(false);
  }
}

void GameScene::clickSystem(cocos2d::Ref* pSender)
{
  p_gameManager->setPaused(true);
  auto scene = SystemScene::create();
  Director::getInstance()->pushScene(scene);
}
