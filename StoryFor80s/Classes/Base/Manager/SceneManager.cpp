//
//  SceneManager.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 9/20/18.
//

#include "SceneManager.hpp"
#include "PanelManager.hpp"

SceneManager* SceneManager::p_sharedManager = nullptr;

SceneManager* SceneManager::getShareInstance()
{
  if (p_sharedManager == nullptr) {
    p_sharedManager = new SceneManager();
  }
  return p_sharedManager;
}

template <typename T, typename std::enable_if<std::is_base_of<BaseScene, T>::value>::type*>
void SceneManager::registerScene(const std::string &sceneName)
{
  p_sharedManager->p_sceneFuncMap[sceneName] = T::createScene;
}

void SceneManager::pushScene(const std::string &sceneName)
{
  BaseScene *scene = nullptr;
  if (p_sceneFuncMap.count(sceneName) > 0) {
    scene = p_sceneFuncMap[sceneName]();
  } else {
    scene = BaseScene::createScene(sceneName);
  }
  CCASSERT(scene != nullptr, ("unrecognized scene : " + sceneName).c_str());
  pushScene(scene);
}

void SceneManager::pushScene(BaseScene *scene)
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
  BaseScene *scene = nullptr;
  if (p_sceneFuncMap.count(sceneName) > 0) {
    scene = p_sceneFuncMap[sceneName]();
  } else {
    scene = BaseScene::createScene(sceneName);
  }
  CCASSERT(scene != nullptr, ("unrecognized scene : " + sceneName).c_str());
  p_sceneStack = stack<BaseScene*>({scene});
  Director::getInstance()->replaceScene(scene);
}

void SceneManager::popScene()
{
  p_sceneStack.pop();
  Director::getInstance()->popScene();
}

BaseScene* SceneManager::currentScene() const
{
  if (!p_sceneStack.empty()) {
    return p_sceneStack.top();
  }
  return nullptr;
}

void SceneManager::addPanel(const std::string &panelName)
{
  auto scene = dynamic_cast<BaseScene *>(Director::getInstance()->getRunningScene());
  if (scene != nullptr) {
    BasePanel *panel = PanelManager::getShareInstance()->getPanelById(panelName);
    scene->addPanelWithParameters(panel);
    panel->initialize();
  }
}

void SceneManager::refreshScene() const
{
  auto scene = dynamic_cast<BaseScene *>(Director::getInstance()->getRunningScene());
  scene->refreBaseScene();
}

void SceneManager::popPanel()
{
  auto scene = dynamic_cast<BaseScene *>(Director::getInstance()->getRunningScene());
  if (scene != nullptr) {
    scene->popPanel();
  }
}

BasePanel* SceneManager::topPanel() const
{
  auto scene = dynamic_cast<BaseScene *>(Director::getInstance()->getRunningScene());
  if (scene != nullptr) {
    return scene->topPanel();
  }
  return nullptr;
}
