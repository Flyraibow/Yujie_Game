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
#include "SHBaseFrame.hpp"

USING_NS_CC;
using namespace std;

class SystemBarFrame : public SHBaseFrame
{
private:
  vector<ui::Button *> p_buttonList;

  void clickSystemButton(cocos2d::Ref* pSender);
protected:
  virtual Node* genSprite(double scale);
public:
  void setTextScale(double f);
};


#endif /* SystemBarFrame_hpp */
