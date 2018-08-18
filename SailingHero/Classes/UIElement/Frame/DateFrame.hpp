//
//  DateFrame.hpp
//  SailingHero
//
//  Created by Yujie Liu on 8/8/18.
//

#ifndef DateFrame_hpp
#define DateFrame_hpp

#include "cocos2d.h"
#include "SHBaseFrame.hpp"

USING_NS_CC;
using namespace std;

class DateFrame : public SHBaseFrame
{
private:
  Label* p_labDate;
protected:
  virtual Node* genSprite(double scale);
public:
  void refresh();
};


#endif /* DateFrame_hpp */
