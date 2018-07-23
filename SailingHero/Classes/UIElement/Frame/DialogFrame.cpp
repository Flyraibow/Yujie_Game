//
//  DialogFrame.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 7/21/18.
//

#include "DialogFrame.hpp"
#include "SHSpriteListener.hpp"

DialogFrame::DialogFrame(const string& text)
{
  p_sprite = LayerColor::create(Color4B(0,0,0,50));
  p_sprite->setAnchorPoint(Vec2());
  p_sprite->setContentSize(Director::getInstance()->getVisibleSize());
  auto listener = SHSpriteListener::createWithNode(p_sprite);
  listener->setTouchEnd([](Touch* touch, Event* event){
    CCLOG("======== click");
  }, nullptr);
  
  p_dialogFrame = Sprite::create("res/base/dialog/dialogFrame.png");
  
  p_scale = Director::getInstance()->getContentScaleFactor() * 0.7;
  p_dialogFrame->setScale(p_scale);
  p_dialogFrame->setAnchorPoint(Vec2(0.5, 0));
  p_dialogFrame->setNormalizedPosition(Vec2(0.5, 0));
  p_sprite->addChild(p_dialogFrame);
  p_dialogContent = Label::createWithSystemFont(text, "Helvetica", 12);
  p_dialogContent->setTextColor(Color4B::BLACK);
  p_dialogContent->setScale(1 / p_scale);
  p_dialogContent->setAnchorPoint(Vec2(0, 1));
  p_dialogContent->setNormalizedPosition(Vec2(0.1, 0.9));
  p_dialogContent->setDimensions(p_dialogFrame->getContentSize().width * p_scale * 0.8, 0);
  p_dialogFrame->addChild(p_dialogContent);
}


Node* DialogFrame::getSprite() const
{
  return p_sprite;
}

void DialogFrame::setText(const string& text)
{
  
}

DialogFrame* DialogFrame::createWithContent(const string& text)
{
  auto dialogFrame = new DialogFrame(text);
  return dialogFrame;
}
