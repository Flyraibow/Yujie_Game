//
//  EventManager.hpp
//  SailingHero
//
//  Created by Yujie Liu on 9/18/18.
//

#ifndef EventManager_hpp
#define EventManager_hpp

#include <stdio.h>
#include "SHScene.hpp"
#include <stack>

class EventManager
{
private:
  static EventManager* p_sharedManager;
  static SHScene* p_currentScene;
  Node *p_groupButton;
  float p_seconds;
  stack<string> p_eventStack;
  void addGroupButton(const vector<string> &parameters);
  void removeGroupButton();
  void continueEvent();
public:
  static EventManager* getShareInstance();
  EventManager();
  static void setCurrentScene(SHScene *scene);
  void runEvent(std::string eventName);
};

#endif /* EventManager_hpp */
