//
//  SHSpriteListener.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 7/14/18.
//

#include "SHSpriteListener.hpp"

bool isTouchInsideNode()
{
  Director *pDirector = Director::getInstance();
  Point touchPoint = pDirector->convertToGL(touch->getLocationInView());
  auto flag = this->getBoundingBox().containsPoint(touchPoint);
  if (flag) {
    CCLOG("Touch is swallowed by current view SHColorNode : %s", this->getName().c_str());
  }
  return flag;}

SHSpriteListener* SHSpriteListener::createWithNode(Node *node)
{
  auto listener = SHSpriteListener::create();
  listener->s_node = node;
  return listener;
}
