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

enum GroupButtonOption {
  GroupButtonOptionNone = 0,
  GroupButtonOptionWithCloseButton = 1,
  GroupButtonOptionSelectClose = 1 << 1, // not working
  GroupButtonOptionItalic = 1 << 2,
  GroupButtonOptionAlignAll = 1 << 3,
};

using namespace ui;
using namespace std;

class SHButton : public Button
{
private:
  vector<Widget::ccWidgetClickCallback> _callbackList;
public:
  CREATE_FUNC(SHButton);
  static SHButton* create(const std::string &normalImage,
                          const std::string& selectedImage = "",
                          const std::string& disableImage = "",
                          TextureResType texType = TextureResType::LOCAL);
  void pushClickEventListener(const Widget::ccWidgetClickCallback &callback);
};

class SystemButton
{
public:
  static SHButton* defaultButtonWithText(std::string text);
  static SHButton* defaultButtonWithText(std::string text, const Widget::ccWidgetClickCallback &callback);
  // default option is italic
  static SHColorNode* getButtonGroupNode(const vector<SHButton *> &buttons);
  static SHColorNode* getButtonGroupNode(const vector<SHButton *> &buttons, int option);
  static SHColorNode* getButtonGroupNode(const vector<SHButton *> &buttons, int option, const Color4B& color);
  static SHColorNode* getButtonGroupFromEvent(vector<string> parameters);
};

#endif /* SystemButton_hpp */

