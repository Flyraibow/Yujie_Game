//
//  SHSpriteListener.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 7/14/18.
//

#include "SHSpriteListener.hpp"

static bool isTouchInsideNode(Touch *touch, Node *node)
{
  Director *pDirector = Director::getInstance();
  Point touchPoint = pDirector->convertToGL(touch->getLocationInView());
  return node->getBoundingBox().containsPoint(touchPoint);
}

SHSpriteListener* SHSpriteListener::createWithNode(Node *node, bool swallowTouches)
{
  auto listener = SHSpriteListener::create();
  listener->s_node = node;
  listener->setSwallowTouches(swallowTouches);
  listener->setTouchBegin(nullptr);
  node->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, node);
  return listener;
}


void SHSpriteListener::setTouchBegin(ccTouchBeganCallback touchBegin)
{
  auto node = s_node;
  this->onTouchBegan = [node, touchBegin](Touch* touch, Event* event){
    if (isTouchInsideNode(touch, node)) {
      if (touchBegin == nullptr) {
        return true;
      }
      return touchBegin(touch, event);
    }
    return false;
  };
}

void SHSpriteListener::setTouchOver(ccTouchCallback touchOver, ccTouchCallback touchOverOut)
{
  auto node = s_node;
  this->onTouchMoved = [node, touchOver, touchOverOut](Touch* touch, Event* event){
    if (isTouchInsideNode(touch, node)) {
      if (touchOver != nullptr) {
        touchOver(touch, event);
      }
    } else {
      if (touchOverOut != nullptr) {
        touchOverOut(touch, event);
      }
    }
  };
}

void SHSpriteListener::setTouchEnd(ccTouchCallback touchEnd, ccTouchCallback touchCanceled)
{
  auto node = s_node;
  this->onTouchEnded = [node, touchEnd, touchCanceled](Touch* touch, Event* event){
    if (isTouchInsideNode(touch, node)) {
      touchEnd(touch, event);
    } else {
      touchCanceled(touch, event);
    }
  };
}
