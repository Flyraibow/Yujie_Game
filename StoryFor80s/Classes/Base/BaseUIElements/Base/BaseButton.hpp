//
//  BaseButton.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/10/19.
//

#ifndef BaseButton_hpp
#define BaseButton_hpp

#include "cocos2d.h"
#include "ui/UIButton.h"
#include <vector>

USING_NS_CC;

using namespace ui;
using namespace std;

class BaseButton : public Button
{
private:
  vector<Widget::ccWidgetClickCallback> _callbackList;
public:
  CREATE_FUNC(BaseButton);
  static BaseButton* create(const string &normalImage,
                            const string& selectedImage = "",
                            const string& disableImage = "",
                            TextureResType texType = TextureResType::LOCAL);
  void pushClickEventListener(const Widget::ccWidgetClickCallback &callback);
  void setClickEventListener(const Widget::ccWidgetClickCallback &callback);
  static BaseButton* defaultButtonWithText(std::string text);
  static BaseButton* defaultButtonWithText(std::string text, const Widget::ccWidgetClickCallback &callback);
};

#endif /* BaseButton_hpp */
