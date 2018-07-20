//
//  SystemBarFrame.hpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 7/19/18.
//

#ifndef SystemBarFrame_hpp
#define SystemBarFrame_hpp

#include "cocos2d.h"
#include <vector>
#include "ui/UIButton.h"

USING_NS_CC;
using namespace std;

class SystemBarFrame
{
private:
  Sprite* p_sprite;
  vector<ui::Button *> p_buttonList;

  void clickSystemButton(cocos2d::Ref* pSender);
public:
  SystemBarFrame();
  void setTextScale(double f);
  Sprite* getSprite() const;
};


#endif /* SystemBarFrame_hpp */
