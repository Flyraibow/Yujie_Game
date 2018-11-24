//
//  StoryScene.cpp
//  SailingHero
//
//  Created by Yujie Liu on 8/13/18.
//

#include "StoryScene.hpp"
#include "StoryEventData.hpp"
#include "audio/include/SimpleAudioEngine.h"
#include "DialogFrame.hpp"
#include "Utils.hpp"
#include "DataManager.hpp"
#include "SceneManager.hpp"
#include "ButtonData.hpp"

USING_NS_CC;
using namespace ui;

Color4B getColorFromParameters(const map<string, string> &parameters)
{
  auto colorStr = parameters.at("color");
  auto color = Color4B();
  if (colorStr == "black") {
    color = Color4B::BLACK;
  }
  return color;
}

StoryScene* StoryScene::createScene()
{
  return StoryScene::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
  printf("Error while loading: %s\n", filename);
  printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in CityScene.cpp\n");
}

// on "init" you need to initialize your instance
bool StoryScene::init()
{
  //////////////////////////////
  // 1. super init first
  if ( !SHScene::init())
  {
    return false;
  }
  initSceneWithJson("story");
  
  this->setForegroundImage("res/base/frame/eventFrame.png");
  p_moveFast = false;
  
  // Add color
  auto colorCover = LayerColor::create(Color4B());
  s_window->addChild(colorCover, 2000);
  p_isTouching = false;
  p_touchedDuration = 0;
  auto listener = EventListenerTouchOneByOne::create();
  listener->onTouchBegan = [this](Touch *touch, Event *unused_event) {
    p_isTouching = true;
    p_touchedDuration = 0;
    CCLOG("Touch screen begin");
    return true;
  };
  listener->onTouchEnded = [this](Touch *touch, Event *unused_event) {
    p_isTouching = false;
    p_moveFast = false;
    
    CCLOG("Touch screen end");
  };
  colorCover->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
  
  return true;
}

void StoryScene::startNextStoryEvent(StoryEventData *storyData)
{
  if (storyData->getNextStoryData() != nullptr) {
    startStoryEvent(storyData->getNextStoryData());
  } else if (p_stackStories.size() > 0) {
    auto story = p_stackStories.top();
    p_stackStories.pop();
    startStoryEvent(story);
  } else {
    SceneManager::getShareInstance()->popScene();
    auto topScene = SceneManager::getShareInstance()->currentScene();
    topScene->refreshMusic();
  }
}

void StoryScene::startStoryEvent(StoryEventData *storyData)
{
  if (storyData == nullptr) {
    return;
  }
  auto type = storyData->getType();
  CCLOG("start story: %s", storyData->description().c_str());
  if (type == "stopMusic") {
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
  } else if (type == "playMusic") {
    CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(storyData->getPath().c_str(), true);
  } else if (type == "playSound") {
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(storyData->getPath().c_str());
  } else if (type == "addPicture") {
    addPictures(storyData);
  } else if (type == "movePicture") {
    movePictures(storyData);
  } else if (type == "removePicture") {
    auto name = storyData->getName();
    p_originalValue.erase(name);
    if (p_pictures.count(name)) {
      auto picture = p_pictures.at(name);
      picture->removeFromParent();
      p_pictures.erase(name);
    }
  } else if (type == "dialog") {
    if (!p_moveFast) {
      addDialogs(storyData);
      return;
    }
  } else if (type == "selection") {
    showSelections(storyData);
    return;
  } else if (type == "subStory") {
    auto parameters = storyData->getParametrsMap();
    for (auto parameter : parameters) {
      DataManager::getShareInstance()->setTempString(parameter.first, parameter.second);
    }
    if (storyData->getNextStoryData() != nullptr) {
      p_stackStories.push(storyData->getNextStoryData());
    }
    auto subStory = StoryEventData::getStoryEventDataById(storyData->getName());
    startStoryEvent(subStory);
    return;
  }
  if (storyData->getDuration() > 0) {
    if (p_storyEventDeltas.size() == 0) {
      scheduleUpdate();
    }
    p_storyEventDeltas[storyData] = storyData->getDuration();
  }
  if (type == "wait") {
    return;
  } else {
    startNextStoryEvent(storyData);
  }
}

void StoryScene::update(float delta)
{
  if (p_isTouching) {
    p_touchedDuration += delta;
    if (p_touchedDuration > 1.0) {
      p_moveFast = true;
    }
  }
  if (p_moveFast) {
    delta *= 20;
  }
  vector<StoryEventData *> removelist;
  for (auto iter = p_storyEventDeltas.begin(); iter != p_storyEventDeltas.end(); ++iter) {
    auto storyData = iter->first;
    auto duration = iter->second;
    duration -= delta;
    if (duration < 0) {
      removelist.push_back(storyData);
    }
    iter->second = duration;
    if (storyData->getType() == "movePicture") {
      auto name = storyData->getName();
      CCASSERT(p_originalValue.count(name), "original value doesn't contain picture");
      setPicture(name, p_originalValue.at(name), storyData->getParametrsMap(), storyData->getDuration(), duration);
      if (duration < 0) {
        p_originalValue[name] = storyData->getParametrsMap();
      }
    }
  }
  for (auto story : removelist) {
    p_storyEventDeltas.erase(story);
    if (story->getType() == "wait") {
      startNextStoryEvent(story);
    }
  }
  if (p_storyEventDeltas.size() == 0) {
    unscheduleUpdate();
  }
}


void StoryScene::addPictures(StoryEventData *storyEventData)
{
  Node* picture = nullptr;
  auto parameters = storyEventData->getParametrsMap();
  if (storyEventData->getPath().length() > 0) {
    picture = Sprite::create(storyEventData->getPath());
  } else if (parameters.count("color")) {
    auto color = getColorFromParameters(parameters);
    picture = LayerColor::create(color, s_window->getContentSize().width, s_window->getContentSize().height);
  } else if (parameters.count("text")) {
    auto text = DataManager::getShareInstance()->getLocalizedDialogString(parameters.at("text"));
    auto textPicture = Label::createWithSystemFont(text, "Helvetica", 30);
    textPicture->setTextColor(Color4B::WHITE);
    picture = textPicture;
  }
  
  if (parameters.count("opacity")) {
    auto destinyOpacity = atof(parameters.at("opacity").c_str());
    picture->setOpacity(destinyOpacity);
  }
  if (parameters.count("screenscale")) {
    auto f = atof(parameters.at("screenscale").c_str());
    auto scaleX = s_window->getContentSize().width / picture->getContentSize().width * f;
    auto scaleY = s_window->getContentSize().height / picture->getContentSize().height * f;
    picture->setScale(scaleX, scaleY);
  } else if (parameters.count("heightScreenScale")) {
    auto f = atof(parameters.at("heightScreenScale").c_str());
    auto scaleY = s_window->getContentSize().height / picture->getContentSize().height * f;
    picture->setScale(scaleY);
  } else {
    auto f = Director::getInstance()->getContentScaleFactor();
    picture->setScale(f);
  }
  auto anchorX = parameters.count("anchorX") ? atof(parameters.at("anchorX").c_str()) : 0.0;
  auto anchorY = parameters.count("anchorY") ? atof(parameters.at("anchorY").c_str()) : 0.0;
  picture->setAnchorPoint(Vec2(anchorX, anchorY));
  auto posX = parameters.count("posX") ? atof(parameters.at("posX").c_str()) : 0.0;
  auto posY = parameters.count("posY") ? atof(parameters.at("posY").c_str()) : 0.0;
  picture->setNormalizedPosition(Vec2(posX, posY));
  int order = 0;
  if (parameters.count("order")) {
    order = atoi(parameters.at("order").c_str());
  }
  s_window->addChild(picture, order);
  p_pictures[storyEventData->getName()] = picture;
  p_originalValue[storyEventData->getName()] = parameters;
}

void StoryScene::movePictures(StoryEventData *storyEventData)
{
  auto name = storyEventData->getName();
  if (!p_pictures.count(name) && p_originalValue.count(name)) {
    CCLOGERROR("couldn't find picture : %s", storyEventData->description().c_str());
  }
  if (storyEventData->getDuration() <= 0) {
    auto originalPrameters = p_originalValue.at(name);
    setPicture(name, originalPrameters, storyEventData->getParametrsMap());
  }
}

void StoryScene::setPicture(const string &pictureName, const map<string, string> &originalParameters, const map<string, string> &destinyParameters, float totalDuration, float leftTime)
{
  auto originalPicture = p_pictures.at(pictureName);
  auto ratio = 1.0;
  if (totalDuration > leftTime && leftTime > 0) {
    ratio = (totalDuration - leftTime) / totalDuration;
  }
  if (destinyParameters.count("color") && originalParameters.count("color")) {
    auto destinyColor = getColorFromParameters(destinyParameters);
    auto originalColor = getColorFromParameters(originalParameters);
    auto color = Color3B(originalColor.r + ratio * ( destinyColor.r - originalColor.r),
                         originalColor.g + ratio * ( destinyColor.g - originalColor.g),
                         originalColor.b + ratio * ( destinyColor.b - originalColor.b));
    auto opacity = originalColor.a + ratio * (destinyColor.a - originalColor.a);
    originalPicture->setColor(color);
    originalPicture->setOpacity(opacity);
  }
  if (destinyParameters.count("opacity")) {
    auto destinyOpacity = atof(destinyParameters.at("opacity").c_str());
    auto originalOpacity = originalParameters.count("opacity") ? atof(originalParameters.at("opacity").c_str()) : 255;
    auto opacity = originalOpacity + ratio * (destinyOpacity - originalOpacity);
    originalPicture->setOpacity(opacity);
  }
  
  auto posX = originalPicture->getNormalizedPosition().x;
  auto posY = originalPicture->getNormalizedPosition().y;
  if (destinyParameters.count("posX")) {
    auto destinyPosX = atof(destinyParameters.at("posX").c_str());
    auto originalPosX = originalParameters.count("posX") ? atof(originalParameters.at("posX").c_str()) : 0.0;
    posX = originalPosX + ratio * (destinyPosX - originalPosX);
  }
  if (destinyParameters.count("posY")) {
    auto destinyPosY = atof(destinyParameters.at("posY").c_str());
    auto originalPosY = originalParameters.count("posY") ? atof(originalParameters.at("posY").c_str()) : 0.0;
    posY = originalPosY + ratio * (destinyPosY - originalPosY);
  }
  originalPicture->setNormalizedPosition(Vec2(posX, posY));
  
  auto anchorX = originalPicture->getAnchorPoint().x;
  auto anchorY = originalPicture->getAnchorPoint().y;
  if (destinyParameters.count("anchorX")) {
    auto destinyAnchorX = atof(destinyParameters.at("anchorX").c_str());
    auto originalAnchorX = originalParameters.count("anchorX") ? atof(originalParameters.at("anchorX").c_str()) : 0.0;
    anchorX = originalAnchorX + ratio * (destinyAnchorX - originalAnchorX);
  }
  if (destinyParameters.count("anchorY")) {
    auto destinyAnchorY = atof(destinyParameters.at("anchorY").c_str());
    auto originalAnchorY = originalParameters.count("anchorY") ? atof(originalParameters.at("anchorY").c_str()) : 0.0;
    anchorY = originalAnchorY + ratio * (destinyAnchorY - originalAnchorY);
  }
  originalPicture->setAnchorPoint(Vec2(anchorX, anchorY));
  
  if (destinyParameters.count("screenscale")) {
    auto destinyScreenScale = atof(destinyParameters.at("screenscale").c_str());
    auto originalScreenScale = originalParameters.count("screenscale") ? atof(originalParameters.at("screenscale").c_str()) : 1;
    auto screenScale = originalScreenScale + ratio * (destinyScreenScale - originalScreenScale);
    auto scaleX = s_window->getContentSize().width / originalPicture->getContentSize().width * screenScale;
    auto scaleY = s_window->getContentSize().height / originalPicture->getContentSize().height * screenScale;
    originalPicture->setScale(scaleX, scaleY);
  }
}

void StoryScene::addDialogs(StoryEventData *storyEventData)
{
  auto parameters = storyEventData->getParametrsMap();
  vector<string> dialogIds;
  if (parameters.count("dialogIds")) {
    auto dialogIdsString = storyEventData->getParametrsMap().at("dialogIds");
    dialogIds = SHUtil::split(dialogIdsString, ',');
  } else if (parameters.count("dialogPrefix") && parameters.count("from") && parameters.count("to")) {
    auto prefix = parameters.at("dialogPrefix");
    auto from = atoi(parameters.at("from").c_str());
    auto to = atoi(parameters.at("to").c_str());
    for (auto i = from; i <= to; ++i) {
      dialogIds.push_back(prefix + to_string(i));
    }
  } else {
    CCLOGERROR("error dialog format: %s", storyEventData->description().c_str());
  }
  auto dialog = DialogFrame::createWithDialogIds(dialogIds, [this, storyEventData]() {
    this->startNextStoryEvent(storyEventData);
  }, Color4B(), s_window->getContentSize());
  s_window->addChild(dialog->getSprite(), 100);
}

#include "SystemButton.hpp"

void StoryScene::showSelections(StoryEventData *storyEventData)
{
  auto parameters = storyEventData->getParametrsMap();
  CCASSERT(parameters.count("options"), ("selection must contain 'options' parameters, %s" + storyEventData->description()).c_str());
  auto selections = SHUtil::split(parameters.at("options"), ',');
  CCASSERT(selections.size() > 0, ("selection must contain more than 0 'options', %s" + storyEventData->description()).c_str());
  vector<SHButton *> buttons;
  for (auto i = 0; i < selections.size(); ++i) {
    auto selection = selections.at(i);
    auto buttonData = ButtonData::getButtonDataById(selection);
    auto button = SystemButton::defaultButtonWithText(buttonData->getLabel(), [buttonData,storyEventData, this](cocos2d::Ref* pSender) {
      auto story = StoryEventData::getStoryEventDataById(buttonData->getTriggerStoryId());
      if (story != nullptr) {
        this->startStoryEvent(story);
      } else if (storyEventData->getNextStoryData() != nullptr) {
        this->startStoryEvent(storyEventData->getNextStoryData());
      }
    });
    buttons.push_back(button);
  }
  auto buttonGroup = SystemButton::getButtonGroupNode(buttons, GroupButtonOptionSelectClose);
  s_window->addChild(buttonGroup, 100);
}
