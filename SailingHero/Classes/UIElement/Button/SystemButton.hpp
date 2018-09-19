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
#include <vector>

USING_NS_CC;

using namespace ui;
using namespace std;

class SystemButton
{
public:
  static Button* defaultButtonWithText(std::string text);
  static Button* defaultButtonWithText(std::string text, const Widget::ccWidgetClickCallback &callback);
  static SHColorNode* getButtonGroupNode(const vector<Button *> &buttons);
  static SHColorNode* getButtonGroupNode(const vector<Button *> &buttons, bool withCloseButton);
  static SHColorNode* getButtonGroupNode(const vector<Button *> &buttons, bool withCloseButton, bool italic);
  static SHColorNode* getButtonGroupNode(const vector<Button *> &buttons, bool withCloseButton, bool italic, const Color4B& color);
  static SHColorNode* getButtonGroupFromEvent(vector<string> parameters);
};

#endif /* SystemButton_hpp */

