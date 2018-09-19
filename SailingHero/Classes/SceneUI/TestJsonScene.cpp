//
//  TestJsonScene.cpp
//  SailingHero
//
//  Created by Yujie Liu on 9/17/18.
//

#include "TestJsonScene.hpp"

USING_NS_CC;
using namespace ui;

TestJsonScene* TestJsonScene::createScene()
{
  return TestJsonScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
  printf("Error while loading: %s\n", filename);
  printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in CityScene.cpp\n");
}

// on "init" you need to initialize your instance
bool TestJsonScene::init()
{
  //////////////////////////////
  // 1. super init first
  if ( !SHScene::init())
  {
    return false;
  }
  initSceneWithJson("testJson");
  return true;
}
