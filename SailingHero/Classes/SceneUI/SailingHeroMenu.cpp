//
//  SailingHeroMenu.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 5/16/18.
//

#include "SailingHeroMenu.hpp"

USING_NS_CC;

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

#include "SHPanelContent.hpp"

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
  
  addPanelWithJson("input");
  getComponentById<Label>("hint_label")->setString("hint text");
  

  return true;
}

