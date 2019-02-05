//
//  SailMapScene.cpp
//  SailingHero
//
//  Created by Yujie Liu on 8/8/18.
//

#include "SailMapScene.hpp"

USING_NS_CC;
using namespace ui;

SHScene* SailMapScene::createScene()
{
  return SailMapScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
  printf("Error while loading: %s\n", filename);
  printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in CityScene.cpp\n");
}

// on "init" you need to initialize your instance
bool SailMapScene::init()
{
  //////////////////////////////
  // 1. super init first
  if ( !SHScene::init())
  {
    return false;
  }
  initSceneWithJson("sailMap");
  
  p_sailMapFrame.addToParent(s_window);

  return true;
}

