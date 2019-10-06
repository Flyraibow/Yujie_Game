//
//  BackgroundContainer.cpp
//  YJStartWithNothing
//
//  Created by Yujie Liu on 10/4/19.
//

#include "BackgroundContainer.hpp"
#include "EventData.hpp"
#include "GameManager.hpp"


// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

void BackgroundContainer::initTitle()
{
  auto visibleSize = this->getContentSize();
  auto label = Label::createWithTTF("Life is Short", "fonts/Marker Felt.ttf", 48);
  if (label != nullptr)
  {
    label->setTextColor(Color4B::BLACK);
    // position the label on the center of the screen
    label->setPosition(Vec2(visibleSize.width/2,
                            visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);
    p_contents.push_back(new EventData(label));
  }
  auto subTitle = Label::createWithTTF("by Yujie Liu", "fonts/Marker Felt.ttf", 24);
  if (subTitle != nullptr)
  {
    subTitle->setTextColor(Color4B::BLACK);
    // position the label on the center of the screen
    subTitle->setPosition(Vec2(visibleSize.width * 0.65,
                            label->getPosition().y - label->getContentSize().height / 2 - subTitle->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(subTitle, 1);
    p_contents.push_back(new EventData(subTitle));
  }
  p_moving = false;
  this->scheduleUpdate();
}

void BackgroundContainer::setMoving(bool flag)
{
  p_moving = flag;
  p_positionX = this->getPosition().x;
  p_duration = 0;
}

void BackgroundContainer::addEvent(EventData* eventData)
{
  eventData->setStarted();
  auto node = eventData->getNode();
  this->addChild(node);
  auto distance = eventData->getDistantAge() * MOVE_SPEED * SECS_PER_YEAR - this->getPosition().x + this->getContentSize().width / 2;
  node->setPosition(distance, this->getContentSize().height * eventData->getHeight());
  p_contents.push_back(eventData);
}

void BackgroundContainer::update(float delta)
{
  if (p_moving) {
    GameManager::getInstance()->update(delta);
    p_duration += delta;
    auto pX = p_positionX - p_duration * MOVE_SPEED;
    this->setPosition(Vec2(pX, this->getPosition().y));
    auto windowWidth = this->getContentSize().width;
    
    for (int i = (int)p_contents.size() - 1; i >= 0; --i) {
      auto eventData = p_contents.at(i);
      auto node = eventData->getNode();
      auto leftX = node->getPosition().x + pX;
      if (eventData->getForce() && eventData->isNotSelected() && leftX <= windowWidth * 0.3) {
        eventData->forceSelect();
      }
    }
      
    if (pX + windowWidth < 0) {
      // clear
      for (int i = (int)p_contents.size() - 1; i >= 0; --i) {
        auto eventData = p_contents.at(i);
        auto node = eventData->getNode();
        auto rightX = node->getPosition().x + node->getContentSize().width + pX;
        if (rightX < 0) {
          delete eventData;
          p_contents.erase(p_contents.begin() + i);
        }
      }
      // shift to right
      p_duration = 0;
      this->setPosition(pX + windowWidth, this->getPosition().y);
      p_positionX = pX + windowWidth;
      for (auto eventData : p_contents) {
        auto node = eventData->getNode();
        auto rightX = node->getPosition().x - windowWidth;
        node->setPosition(rightX, node->getPosition().y);
      }
    }
  }
}
