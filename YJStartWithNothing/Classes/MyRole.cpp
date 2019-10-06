//
//  MyRole.cpp
//  YJStartWithNothing
//
//  Created by Yujie Liu on 10/4/19.
//

#include "MyRole.hpp"

bool MyRole::init()
{
  // 1. super init first
  if ( !Sprite::initWithFile("res/man_1.png") )
  {
      return false;
  }
//  this->setScale(0.4);
  
  return true;
}
