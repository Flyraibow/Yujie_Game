//
//  QuickAlert.hpp
//  MiniMonopoly
//
//  Created by Yujie Liu on 7/31/19.
//

#ifndef QuickAlert_hpp
#define QuickAlert_hpp

#include "cocos2d.h"

using namespace std;

USING_NS_CC;

class QuickAlert {
  
public:
  static void createAlertWithMsg(const string &msg);
  static void createAlertWithMsg(const string &msg, const Color4B &color);
};

#endif /* QuickAlert_hpp */
