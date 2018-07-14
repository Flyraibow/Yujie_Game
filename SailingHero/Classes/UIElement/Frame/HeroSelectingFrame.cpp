//
//  HeroSelectingFrame.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 7/12/18.
//

#include "HeroSelectingFrame.hpp"
#include "HeroSelectData.hpp"

USING_NS_CC;
using namespace std;

Sprite * HeroSelectingFrame::createWithSelectHeroId(const string &selectHeroId)
{
  auto sprite = Sprite::create("res/base/frame/peopleFrame.png");
  auto heroSprite = HeroSelectData::getHeroSelectDataById(selectHeroId)->getIcon();
  heroSprite->setAnchorPoint(Vec2(0, 0));
  auto f = Director::getInstance()->getContentScaleFactor();
  heroSprite->setPosition(Vec2(13 / f, 19 / f));
  heroSprite->setContentSize(Size(112 / f, 144 / f));
  sprite->addChild(heroSprite);
  sprite->setScale(3);
  return sprite;
}

Sprite* HeroSelectingFrame::createBigPhotoWithSelectHeroId(const string &selectHeroId)
{
  auto sprite = Sprite::create("res/base/frame/bigPhotoFrame.png");
  auto heroSprite = HeroSelectData::getHeroSelectDataById(selectHeroId)->getIcon();
  heroSprite->setAnchorPoint(Vec2(0, 0));
  auto f = Director::getInstance()->getContentScaleFactor();
  heroSprite->setPosition(Vec2(32 / f, 64 / f));
  heroSprite->setContentSize(Size(210 / f, 258 / f));
  sprite->addChild(heroSprite);
  sprite->setScale(2.5);
  return sprite;
}
