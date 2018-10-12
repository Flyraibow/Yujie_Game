//
//  SHScene.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 5/27/18.
//

#include "SHScene.hpp"
#include "audio/include/SimpleAudioEngine.h"

#include "SHColorNode.hpp"
#include <string>

#ifdef COVER_DEBUG
#define COVER_COLOR Color4B(255, 0, 0, 100)
#else
#define COVER_COLOR Color4B(0, 0, 0, 255)
#endif

using namespace std;


void SHScene::setFullScreenCover()
{
  auto visibleSize = Director::getInstance()->getVisibleSize();
  Vec2 origin = Director::getInstance()->getVisibleOrigin();
  s_window = Node::create();
  s_window->setAnchorPoint(Vec2());
  s_window->setContentSize(visibleSize);
  s_window->setPosition(origin);
  this->addChild(s_window, 1);
  s_isFullScreen = true;
  if (s_background != nullptr) {
    auto contentSize = s_background->getContentSize();
    auto r1 = visibleSize.width / contentSize.width;
    auto r2 = visibleSize.height / contentSize.height;
    s_background->setScale(r1, r2);
  }
}

void SHScene::setScreenCover(Size ratioSize)
{
  assert(ratioSize.width > 0 && ratioSize.height > 0);
  auto visibleSize = Director::getInstance()->getVisibleSize();
  Vec2 origin = Director::getInstance()->getVisibleOrigin();
  double ratio = ratioSize.width / ratioSize.height;
  double expectHeight = visibleSize.width / ratio;
  double expectWidth = visibleSize.width;
  bool verticalFlag = true;
  Size nodeSize;
  Vec2 windowOrigin;
  if (expectHeight > visibleSize.height) {
    expectWidth = visibleSize.height * ratio;
    verticalFlag = false;
    nodeSize = Size((visibleSize.width - expectWidth) / 2, visibleSize.height);
    s_screenSize = Size(expectWidth, visibleSize.height);
    windowOrigin = Vec2(nodeSize.width, origin.y);
  } else  {
    nodeSize = Size(expectWidth, (visibleSize.height - expectHeight) / 2);
    s_screenSize = Size(visibleSize.width, expectHeight);
    windowOrigin = Vec2(origin.x, nodeSize.height);
  }
  
  s_window = Node::create();
  s_window->setContentSize(s_screenSize);
  s_window->setPosition(windowOrigin);
  this->addChild(s_window, 1);
  
  if (nodeSize.width < 1 || nodeSize.height < 1) {
    // there is no need to create a cover
    return;
  }
  auto n1 = SHColorNode::create(COVER_COLOR, nodeSize.width, nodeSize.height);
  auto n2 = SHColorNode::create(COVER_COLOR, nodeSize.width, nodeSize.height);
  if (verticalFlag) {
    n2->setPosition(0, visibleSize.height - nodeSize.height);
  } else {
    n2->setPosition(visibleSize.width - nodeSize.width, 0);
  }
  n1->setName("Cover page 1");
  n2->setName("Cover page 2");
  auto node = Node::create();
  node->addChild(n1);
  node->addChild(n2);
  node->setPosition(origin);
  this->addChild(node, SCREEN_COVER_LAYER_HEIGHT);
}

Size SHScene::getScreenSize() const
{
  if (s_screenSize.width == 0 || s_screenSize.height == 0) {
    return Director::getInstance()->getVisibleSize();
  }
  return s_screenSize;
}

void SHScene::setBackgroundImage(const std::string &imgPath) {
  if (imgPath.length() == 0) {
    return;
  }
  s_background = Sprite::create(imgPath);
  CCASSERT(s_background, ("unable to find image with path : " + imgPath).c_str());
  auto visibleSize = this->getScreenSize();
  auto contentSize = s_background->getContentSize();
  // TODO: ADD how to set align, vertical or horizontal or minimum or maximum or actual size
  auto r1 = visibleSize.width / contentSize.width;
  auto r2 = visibleSize.height / contentSize.height;
  if (s_isFullScreen) {
    s_background->setScale(r1, r2);
  } else {
    auto r = max(r1, r2);
    s_background->setScale(r);
  }
  s_background->setNormalizedPosition(Vec2(0.5, 0.5));
  this->addChild(s_background);
}

void SHScene::setForegroundImage(const std::string &imgPath)
{
  s_foreground = Sprite::create(imgPath);
  CCASSERT(s_foreground, ("unable to find image with path : " + imgPath).c_str());
  auto visibleSize = this->getScreenSize();
  auto contentSize = s_foreground->getContentSize();
  // TODO: ADD how to set align, vertical or horizontal or minimum or maximum or actual size
  auto r1 = visibleSize.width / contentSize.width;
  auto r2 = visibleSize.height / contentSize.height;
  if (s_isFullScreen) {
    s_foreground->setScale(r1, r2);
  } else {
    auto r = max(r1, r2);
    s_foreground->setScale(r);
  }
  s_foreground->setNormalizedPosition(Vec2(0.5, 0.5));
  this->addChild(s_foreground, SCREEN_FOREGROUND_LAYER_HEIGHT);
}

Node* SHScene::getBackground()
{
  return s_background;
}

void SHScene::setBackgroundMusic(const std::string &path) {
  if (path.length() == 0) {
    return;
  }
  auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
  audio->stopBackgroundMusic();
  audio->preloadBackgroundMusic(path.c_str());
  audio->playBackgroundMusic(path.c_str(), true);
}


void SHScene::addPanelWithParameters(SHPanel *panel)
{
  auto panelName = panel->getPanelName();
  CCLOG("Add panel %s", panelName.c_str());
  panel->addToParent(s_window);
  p_panelStack.push(panel);
}

#include "EventManager.hpp"

SHSceneContent* SHScene::initSceneWithJson(const std::string &jsonFileName)
{
  auto content = new SHSceneContent(jsonFileName);
  setBackgroundMusic(content->getBackgroundMusic());
  setBackgroundImage(content->getBackgroundImage());
  if (content->isFullScreenCover()) {
    setFullScreenCover();
  } else {
    Size ratio = content->getScreenCoverRatio();
    if (ratio.width > 0 && ratio.height > 0) {
      setScreenCover(ratio);
    }
  }
  
  EventManager::getShareInstance()->runEvent(content->getInitialEvent());
  
  auto components = content->getComponentList();
  for (int i = 0; i < components.size(); ++i) {
    auto component = components.at(i);
    component->addComponentToParent(p_componentDict, s_window);
  }
  
  return content;
}

void SHScene::refreshScene()
{
  for (auto component : p_componentDict) {
    component.second->refresh();
  }
}

void SHScene::popPanel()
{
  if (p_panelStack.size() == 0) {
    return;
  }
  auto panel = p_panelStack.top();
  p_panelStack.pop();
  panel->removeFromParent();
  delete panel;
}

SHPanel* SHScene::topPanel () const
{
  if (p_panelStack.size() == 0) {
    return nullptr;
  }
  return p_panelStack.top();
}

#include "DialogFrame.hpp"

void SHScene::addDialogFrame(DialogFrame* dialog)
{
  s_window->addChild(dialog->getSprite());
}

bool SHScene::init()
{
  //////////////////////////////
  // 1. super init first
  if ( !Scene::init() )
  {
    return false;
  }
  EventManager::setCurrentScene(this);
  return true;
}
