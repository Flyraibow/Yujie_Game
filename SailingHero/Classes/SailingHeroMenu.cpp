//
//  SailingHeroMenu.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 5/16/18.
//

#include "SailingHeroMenu.hpp"

#include "SimpleAudioEngine.h"
#include "SystemButton.hpp"
#include "LocalizationHelper.hpp"
#include "SHDataManager.hpp"
#include "SelectHeroMenuScene.hpp"
#include "EventManager.hpp"

#include "SHColorNode.hpp"
#include <string>
#include <vector>

USING_NS_CC;
using namespace ui;

Scene* SailingHeroMenu::createScene()
{
  return SailingHeroMenu::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
  printf("Error while loading: %s\n", filename);
  printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SailingHeroMenu.cpp\n");
}

SailingHeroMenu::SailingHeroMenu()
{
  
}

// on "init" you need to initialize your instance
bool SailingHeroMenu::init()
{
  //////////////////////////////
  // 1. super init first
  if ( !SHScene::init() )
  {
    return false;
  }
  initSceneWithJson("menu");
  

  return true;
}

