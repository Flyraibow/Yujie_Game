//
//  DialogPhotoFrame.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 7/23/18.
//

#include "DialogPhotoFrame.hpp"


DialogPhotoFrame::DialogPhotoFrame()
{
  p_background = Node::create();
  auto frame = Sprite::create("res/base/dialog/dialogPhotoFrame.png");
  frame->setAnchorPoint(Vec2());
  p_background->addChild(frame, 2);
  p_background->setContentSize(frame->getContentSize());
  p_heroData = nullptr;
  p_photoSprite = nullptr;
}

Node* DialogPhotoFrame::getSprite() const
{
  return p_background;
}

void DialogPhotoFrame::setHeroData(HeroData* heroData)
{
  if (p_heroData != heroData) {
    p_heroData = heroData;
    if (p_photoSprite == nullptr) {
      p_photoSprite = heroData->getPhoto();
    } else {
      p_photoSprite->removeFromParent();
      p_photoSprite = heroData->getPhoto();
    }
    auto f = Director::getInstance()->getContentScaleFactor();
    p_photoSprite->setAnchorPoint(Vec2());
    p_photoSprite->setPosition(Vec2(8 / f, 8 / f));
    p_background->addChild(p_photoSprite);
  }
}
