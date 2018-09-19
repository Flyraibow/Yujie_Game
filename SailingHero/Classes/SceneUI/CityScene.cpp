//
//  CityScene.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 7/16/18.
//

#include "CityScene.hpp"


USING_NS_CC;
using namespace ui;

CityScene* CityScene::createScene()
{
  return CityScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
  printf("Error while loading: %s\n", filename);
  printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in CityScene.cpp\n");
}

// on "init" you need to initialize your instance
bool CityScene::init()
{
  //////////////////////////////
  // 1. super init first
  if ( !SHScene::init())
  {
    return false;
  }
  initSceneWithJson("city");

  auto citySceneSprite = p_citySceneFrame.getSprite();
  
  s_window->addChild(citySceneSprite);
  

  return true;
}

void CityScene::setCityDataId(int cityDataId)
{
  p_cityData = CityData::getCityDataById(cityDataId);
  CCASSERT(p_cityData != nullptr, "City Data shouldn't be null");
  this->setBackgroundMusic(p_cityData->getCultureData()->getCityMusicPath());
  p_citySceneFrame.setCityData(p_cityData);
}

