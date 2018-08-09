//
//  AreaMapFrame.cpp
//  SailingHero
//
//  Created by Yujie Liu on 8/8/18.
//

#include "AreaMapFrame.hpp"


AreaMapFrame::AreaMapFrame()
{
  p_background = Node::create();
  p_areaData = nullptr;
}

void AreaMapFrame::setAreaData(AreaData* areaData)
{
  p_areaData = areaData;
  refresh();
}

void AreaMapFrame::refresh()
{
  if (p_areaSprite != nullptr) {
    p_areaSprite->removeFromParent();
  }
  p_areaSprite = p_areaData->getIcon();
  p_areaSprite->setAnchorPoint(Vec2());
  p_background->addChild(p_areaSprite);
}

Node* AreaMapFrame::getSprite() const
{
  return p_background;
}
