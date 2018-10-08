//
//  SceneManager.hpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 9/20/18.
//

#ifndef SceneManager_hpp
#define SceneManager_hpp

#include <stdio.h>
#include <unordered_map>
#include <vector>
#include "SHScene.hpp"

class SHPanel;

typedef SHScene* (*getScene)();

class SceneManager
{
private:
  static SceneManager* p_sharedManager;
  std::unordered_map<std::string, getScene> p_sceneFuncMap;
  
  template <typename T, typename std::enable_if<std::is_base_of<SHScene, T>::value>::type* = nullptr>
  void registerScene(const std::string &sceneName);
public:
  static SceneManager* getShareInstance();
  void pushScene(const std::string &sceneName);
  void refreshScene() const;
  void addPanel(const std::string &panelName);
  void popPanel();
  SHPanel* topPanel() const;
  void addDialog(const vector<string> &dialogIds) const;
};

#endif /* SceneManager_hpp */
