//
//  SHBaseFrame.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 8/15/18.
//

#include "SHBaseFrame.hpp"
#include "SHScene.hpp"
#include "SHColorNode.hpp"

SHBaseFrame::SHBaseFrame(SCALE_TYPE scaleType)
{
  p_type = scaleType;
  p_cover = nullptr;
  p_sprite = nullptr;
}

void SHBaseFrame::addToParent(Node* node, int order, bool withCover)
{
  assert(p_cover == nullptr);
  p_sprite = getSprite(node->getScale());
  if (withCover) {
    // TODO: NEED RE-ADJUST THE SIZE AND POSIITON FOR COVER
    p_cover = SHColorNode::create(Color4B());
    node->addChild(p_cover, order);
    node->addChild(p_sprite, order);
  } else {
    node->addChild(p_sprite, order);
  }
}

void SHBaseFrame::removeFromParent()
{
  if (p_sprite != nullptr) {
    p_sprite->removeFromParent();
    p_sprite = nullptr;
  }
  if (p_cover != nullptr) {
    p_cover->removeFromParent();
    p_cover = nullptr;
  }
}

void SHBaseFrame::setVisible(bool visible)
{
  if (p_sprite != nullptr) {
    p_sprite->setVisible(visible);
    if (visible) {
      p_sprite->getEventDispatcher()->resumeEventListenersForTarget(p_sprite);
    } else {
      p_sprite->getEventDispatcher()->pauseEventListenersForTarget(p_sprite);
    }
  }
  if (p_cover != nullptr) {
    p_cover->setVisible(visible);
    if (visible) {
      p_cover->getEventDispatcher()->resumeEventListenersForTarget(p_cover);
    } else {
      p_cover->getEventDispatcher()->pauseEventListenersForTarget(p_cover);
    }
  }
}
