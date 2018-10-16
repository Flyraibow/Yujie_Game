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
  Director::getInstance()->pushScene(scene);
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

void SceneManager::addDialog(const vector<string> &dialogIds) const
{
  auto scene = dynamic_cast<SHScene *>(Director::getInstance()->getRunningScene());
  auto dialog = DialogFrame::createWithDialogIds(dialogIds, [this]() {
    
  });
  scene->addDialogFrame(dialog);
}
