//
//  SystemButton.hpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 5/16/18.
//

#ifndef SystemButton_hpp
#define SystemButton_hpp

#include "cocos2d.h"
#include "ui/UIButton.h"

class SystemButton
{
public:
    static cocos2d::ui::Button* defaultButtonWithText(std::string text);
};

#endif /* SystemButton_hpp */
