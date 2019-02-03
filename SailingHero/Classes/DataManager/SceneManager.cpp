//
//  SceneManager.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 9/20/18.
//

#include "SceneManager.hpp"
#include "SelectHeroMenuScene.hpp"
#include "TestScene.hpp"
#include "PanelManager.hpp"
#include "EventManager.hpp"

SceneManager* SceneManager::p_sharedManager = nullptr;

SceneManager* SceneManager::getShareInstance()
{
  if (p_sharedManager == nullptr) {
    p_sharedManager = new SceneManager();
    p_sharedManager->registerScene<SelectHeroMenuScene>("SelectHeroMenuScene");
  }
  return p_sharedManager;
}

template <typename T, typename std::enable_if<std::is_base_of<SHScene, T>::value>::type*>
void SceneManager::registerScene(const std::string &sceneName)
{
  p_sharedManager->p_sceneFuncMap[sceneName] = T::createScene;
}

void SceneManager::pushScene(const std::string &sceneName)
{
  SHScene *scene = nullptr;
  if (p_sceneFuncMap.count(sceneName) > 0) {
    scene = p_sceneFuncMap[sceneName]();
  } else {
    scene = SHScene::createScene(sceneName);
  }
  CCASSERT(scene != nullptr, ("unrecognized scene : " + sceneName).c_str());
  pushScene(scene);
}

void SceneManager::pushScene(SHScene *scene)
{
  CCASSERT(scene != nullptr, "cannot push null scene!");
  if (p_sceneStack.empty()) {
    Director::getInstance()->runWithScene(scene);
  } else {
    Director::getInstance()->pushScene(scene);
  }
  p_sceneStack.push(scene);
}

void SceneManager::setScene(const std::string &sceneName)
{
  SHScene *scene = nullptr;
  if (p_sceneFuncMap.count(sceneName) > 0) {
    scene = p_sceneFuncMap[sceneName]();
  } else {
    scene = SHScene::createScene(sceneName);
  }
  CCASSERT(scene != nullptr, ("unrecognized scene : " + sceneName).c_str());
  p_sceneStack = stack<SHScene*>({scene});
  Director::getInstance()->replaceScene(scene);
}

void SceneManager::popScene()
{
  p_sceneStack.pop();
  Director::getInstance()->popScene();
  EventManager::setCurrentScene(currentScene());
}

SHScene* SceneManager::currentScene() const
{
  if (!p_sceneStack.empty()) {
    return p_sceneStack.top();
  }
  return nullptr;
}

void SceneManager::addPanel(const std::string &panelName)
{
  auto scene = dynamic_cast<SHScene *>(Director::getInstance()->getRunningScene());
  if (scene != nullptr) {
    SHPanel *panel = PanelManager::getShareInstance()->getPanelById(panelName);
    scene->addPanelWithParameters(panel);
  }
}

void SceneManager::refreshScene() const
{
  auto scene = dynamic_cast<SHScene *>(Director::getInstance()->getRunningScene());
  scene->refreshScene();
}

void SceneManager::popPanel()
{
  auto scene = dynamic_cast<SHScene *>(Director::getInstance()->getRunningScene());
  if (scene != nullptr) {
    scene->popPanel();
  }
}

SHPanel* SceneManager::topPanel() const
{
  auto scene = dynamic_cast<SHScene *>(Director::getInstance()->getRunningScene());
  if (scene != nullptr) {
    return scene->topPanel();
  }
  return nullptr;
}

#include "DialogFrame.hpp"

void SceneManager::addDialog(const vector<string> &dialogIds)
{
  auto scene = dynamic_cast<SHScene *>(Director::getInstance()->getRunningScene());
  p_dialogFrame = DialogFrame::createWithDialogIds(dialogIds, [this]() {
    p_dialogFrame = nullptr;
  });
  scene->addDialogFrame(p_dialogFrame);
}

void SceneManager::removeDialog()
{
  if (p_dialogFrame != nullptr) {
    p_dialogFrame->getSprite()->removeFromParent();
    p_dialogFrame = nullptr;
  }
}

bool SceneManager::showDialog() const
{
  return p_dialogFrame != nullptr;
}
