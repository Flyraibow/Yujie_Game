//
//  BaseLabel.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 3/10/19.
//

#include "BaseLabel.hpp"
#include "Utils.hpp"

void BaseLabel::setSpeed(int speed)
{
  p_speed = speed;
}

const static string kLabelContentScheduleKey = "label_content_schedule_key";


void BaseLabel::setString(const std::string& text)
{
  p_text = text;
  p_currentIndex = 0;
  if (p_speed <= 0) {
    Label::setString(text);
  } else {
    p_contentLength = Utils::utf8_strlen(text);
    Label::setString("");
    this->schedule([this](float delta) {
      if (p_currentIndex++ < p_contentLength) {
        auto str = Utils::utf8_substr(p_text, 0, p_currentIndex);
        Label::setString(str);
      } else {
        Label::setString(p_text);
        Label::unschedule(kLabelContentScheduleKey);
      }
    }, 0.2f / p_speed, kLabelContentScheduleKey);
  }
}

BaseLabel* BaseLabel::createWithSystemFont(const std::string& text, const std::string& font, float fontSize, int speed,
                                           const Size& dimensions, TextHAlignment hAlignment, TextVAlignment vAlignment)
{
  auto ret = new (std::nothrow) BaseLabel(hAlignment,vAlignment);
  
  if (ret)
  {
    ret->setSpeed(speed);
    ret->setSystemFontName(font);
    ret->setSystemFontSize(fontSize);
    ret->setDimensions(dimensions.width, dimensions.height);
    ret->setString(text);
    
    ret->autorelease();
    
    return ret;
  }
  
  return nullptr;
}
