//
//  QuickAlert.cpp
//  MiniMonopoly
//
//  Created by Yujie Liu on 7/31/19.
//

#include "QuickAlert.hpp"


void QuickAlert::createAlertWithMsg(const string &msg)
{
  createAlertWithMsg(msg, Color4B::WHITE);
}

void QuickAlert::createAlertWithMsg(const string &msg, const Color4B &color)
{
  auto scene = Director::getInstance()->getRunningScene();
  auto label = Label::createWithSystemFont(msg, "Helvetica", 30);
  label->setTextColor(color);
  label->setNormalizedPosition(Vec2(0.5, 0.5));
  scene->addChild(label, 100);
  string key = "quick_alert_key";
  static const double speed = 30;
  label->schedule([label, key](double delta) {
    int opacity = label->getOpacity();
    if (opacity > 200) {
      opacity -= 1;
    } else {
      opacity -= 4;
    }
    if (opacity < 0) {
      opacity = 0;
    }
    label->setOpacity(opacity);
    label->setPosition(label->getPosition().x, label->getPosition().y + delta * speed);
    if (opacity == 0) {
      label->unschedule(key);
      label->removeFromParent();
    }
  }, key);
}
