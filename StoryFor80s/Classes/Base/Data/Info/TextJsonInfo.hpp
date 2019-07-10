//
//  TextJsonInfo.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 7/10/19.
//

#ifndef TextJsonInfo_hpp
#define TextJsonInfo_hpp

#include <stdio.h>

#include "cocos2d.h"

using namespace std;

struct TextJsonInfo {
  string text;
  float size;
  int typingSpeed;
  cocos2d::Color4B textColor;
  string typingEffect;
  
  TextJsonInfo() {
    text = "";
  }
};

#endif /* TextJsonInfo_hpp */
