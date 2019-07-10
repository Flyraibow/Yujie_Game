//
//  BaseLabel.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 3/10/19.
//

#include "BaseLabel.hpp"
#include "Utils.hpp"
#include "audio/include/SimpleAudioEngine.h"

void BaseLabel::setSpeed(int speed)
{
  p_speed = speed;
}

void BaseLabel::setWait(float wait)
{
  p_wait = wait;
}

const static string kLabelContentScheduleKey = "label_content_schedule_key";


void BaseLabel::setString(const std::string& text)
{
  p_text = text;
  p_currentIndex = 0;
  if (p_speed <= 0) {
    Label::setString(text);
    textCompleteCallback();
  } else {
    p_typingEffectIndex = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(p_typingEffect.c_str(), true);
    p_contentLength = Utils::utf8_strlen(text);
    Label::setString("");
    this->schedule([this](float delta) {
      if (p_currentIndex++ < p_contentLength) {
        auto str = Utils::utf8_substr(p_text, 0, p_currentIndex);
        Label::setString(str);
      } else {
        Label::setString(p_text);
        Label::unschedule(kLabelContentScheduleKey);
        this->textCompleteCallback();
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
    ret->setCallback(nullptr);
    ret->p_typingEffectIndex = -1;
    
    ret->autorelease();
    
    return ret;
  }
  
  return nullptr;
}

void BaseLabel::textCompleteCallback()
{
  stopTypingEffect();
  if (p_callback != nullptr) {
    p_callback();
  }
}

void BaseLabel::stopTypingEffect()
{
  if (p_typingEffectIndex >= 0) {
    CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(p_typingEffectIndex);
    p_typingEffectIndex = -1;
  }
}

void BaseLabel::setCallback(LabelTextCompleteCallback callback)
{
  p_callback = callback;
}

void BaseLabel::showTextImmediately()
{
  if (p_text != Label::getString()) {
    this->unschedule(kLabelContentScheduleKey);
    Label::setString(p_text);
    textCompleteCallback();
  }
}

void BaseLabel::setTypingEffect(const std::string &typingEffect)
{
  p_typingEffect = typingEffect;
  if (typingEffect.length() > 0) {
    if (p_text != Label::getString()) {
      p_typingEffectIndex = CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(p_typingEffect.c_str(), true);
    }
  } else {
    stopTypingEffect();
  }
}
