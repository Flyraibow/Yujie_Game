//
//  CityScene.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 7/16/18.
//

#include "CityScene.hpp"

USING_NS_CC;
using namespace ui;

Scene* CityScene::createScene()
{
  return CityScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
  printf("Error while loading: %s\n", filename);
  printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool CityScene::init()
{
  //////////////////////////////
  // 1. super init first
  if ( !Scene::init())
  {
    return false;
  }
  this->setScreenCover(Size(4, 3));

  auto cityDataSprite = p_cityDataFrame.getSprite();
  p_cityDataFrame.setCityData(CityData::getCityDataById("0"));
  
  s_window->addChild(cityDataSprite);
  
  return true;
}
