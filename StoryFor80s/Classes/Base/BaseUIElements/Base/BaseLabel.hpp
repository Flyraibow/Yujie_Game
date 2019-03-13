//
//  BaseLabel.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 3/10/19.
//

#ifndef BaseLabel_hpp
#define BaseLabel_hpp

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

/**
 * allow user to set speed of the text
 */
class BaseLabel : public Label
{
private:
  int p_speed = 0;
  int p_currentIndex = 0;
  int p_contentLength = 0;
  string p_text;
public:
  CREATE_FUNC(BaseLabel);
  virtual void setSpeed(int speed);
  virtual void setString(const std::string& text) override;
  static BaseLabel* createWithSystemFont(const std::string& text, const std::string& font, float fontSize, int speed = 0,
                                         const Size& dimensions = Size::ZERO, TextHAlignment hAlignment = TextHAlignment::LEFT,
                                         TextVAlignment vAlignment = TextVAlignment::TOP);
  
  BaseLabel(TextHAlignment hAlignment = TextHAlignment::LEFT,
            TextVAlignment vAlignment = TextVAlignment::TOP) : Label(hAlignment, vAlignment) {};
};


#endif /* BaseLabel_hpp */
