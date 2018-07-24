//
//  SHSpriteListener.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 7/14/18.
//

#include "SHSpriteListener.hpp"

static bool isTouchInsideNode(Touch *touch, Node *node)
{
  auto nodePoint = node->convertToNodeSpace(touch->getLocationInView());
  auto rect = Rect(0, 0, node->getContentSize().width, node->getContentSize().height);
  return rect.containsPoint(nodePoint);
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
