//
//  StoryScene.cpp
//  SailingHero
//
//  Created by Yujie Liu on 8/13/18.
//

#include "StoryScene.hpp"

USING_NS_CC;
using namespace ui;

StoryScene* StoryScene::createScene()
{
  return StoryScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
  printf("Error while loading: %s\n", filename);
  printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in CityScene.cpp\n");
}

// on "init" you need to initialize your instance
bool StoryScene::init()
{
  //////////////////////////////
  // 1. super init first
  if ( !Scene::init())
  {
    return false;
  }
  this->setScreenCover(Size(4, 3));
  
  this->setForegroundImage("res/base/frame/eventFrame.png");
  
  return true;
}
