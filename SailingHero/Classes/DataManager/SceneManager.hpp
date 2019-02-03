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
#include <stack>


class SHPanel;
class DialogFrame;

typedef SHScene* (*getScene)();

class SceneManager
{
private:
  static SceneManager* p_sharedManager;
  std::unordered_map<std::string, getScene> p_sceneFuncMap;
  std::stack<SHScene*> p_sceneStack;
  DialogFrame* p_dialogFrame;
  template <typename T, typename std::enable_if<std::is_base_of<SHScene, T>::value>::type* = nullptr>
  void registerScene(const std::string &sceneName);
public:
  static SceneManager* getShareInstance();
  void pushScene(const std::string &sceneName);
  void pushScene(SHScene *scene);
  void setScene(const std::string &sceneName);
  void popScene();
  void refreshScene() const;
  void addPanel(const std::string &panelName);
  void popPanel();
  SHPanel* topPanel() const;
  void addDialog(const vector<string> &dialogIds);
  void removeDialog();
  bool showDialog() const;
  SHScene *currentScene() const;
};

#endif /* SceneManager_hpp */
