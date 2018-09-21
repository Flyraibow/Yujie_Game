//
//  SceneManager.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 9/20/18.
//

#include "SceneManager.hpp"
#include "SelectHeroMenuScene.hpp"
#include "TestScene.hpp"

SceneManager* SceneManager::p_sharedManager = nullptr;

SceneManager* SceneManager::getShareInstance()
{
  if (p_sharedManager == nullptr) {
    p_sharedManager = new SceneManager();
    p_sharedManager->registerScene<SelectHeroMenuScene>("SelectHeroMenuScene");
    p_sharedManager->registerScene<TestScene>("TestScene");
  }
  return p_sharedManager;
}

template <typename T, typename std::enable_if<std::is_base_of<SHScene, T>::value>::type*>
void SceneManager::registerScene(std::string sceneName)
{
  p_sharedManager->p_sceneFuncMap[sceneName] = T::createScene;
}

void SceneManager::pushScene(std::string sceneName)
{
  if (p_sceneFuncMap.count(sceneName) > 0) {
    SHScene *scene = p_sceneFuncMap[sceneName]();
    Director::getInstance()->pushScene(scene);
  } else {
    CCLOGERROR("Couldn't find scene by name %s", sceneName.c_str());
  }
}
