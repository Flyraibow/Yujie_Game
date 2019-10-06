//
//  MyRole.hpp
//  YJStartWithNothing
//
//  Created by Yujie Liu on 10/4/19.
//

#ifndef MyRole_hpp
#define MyRole_hpp

#include "cocos2d.h"

USING_NS_CC;

class MyRole : public Sprite
{
public:
  CREATE_FUNC(MyRole);
  virtual bool init();
  
  void initRole();
};
#endif /* MyRole_hpp */
