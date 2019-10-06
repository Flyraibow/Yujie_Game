//
//  FrontContainer.hpp
//  YJStartWithNothing
//
//  Created by Yujie Liu on 10/4/19.
//

#ifndef FrontContainer_hpp
#define FrontContainer_hpp

#include "cocos2d.h"
#include "MyRole.hpp"
#include "Utils.h"
#include <map>

USING_NS_CC;
using namespace std;

class FrontContainer : public Sprite
{
private:
  MyRole* p_role;
  Label* p_labAge;
  bool touchBegin(Touch* touch, Event* event);
  void touchEnd(Touch* touch, Event* event);
  map<string, Label*> p_attriLabs;
public:
  CREATE_FUNC(FrontContainer);
  virtual bool init();
  
  void initRole();
  void initMoney();
  void initAge();
  void updateAge();
  
  void setValue(string type, double value);
};

#endif /* FrontContainer_hpp */
