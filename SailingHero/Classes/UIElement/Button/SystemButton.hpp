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
#include "SHColorNode.hpp"

USING_NS_CC;

using namespace ui;

class SystemButton
{
public:
    static Button* defaultButtonWithText(std::string text);
    static Button* defaultButtonWithText(std::string text, const Widget::ccWidgetClickCallback &callback);
    static SHColorNode* getButtonGroupNode(Vector<Button *> buttons);
    static SHColorNode* getButtonGroupNode(Vector<Button *> buttons, bool italic);
};

#endif /* SystemButton_hpp */
