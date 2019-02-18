//
//  EventManager.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/11/19.
//

#ifndef EventManager_hpp
#define EventManager_hpp

#include <stdio.h>
#include "BaseScene.hpp"
#include <stack>
#include <unordered_map>
#include <map>

typedef void (*SpecialFunctionWithDict)(const map<string, string> &parameters);

class EventManager
{
private:
  static EventManager* p_sharedManager;
  static BaseScene* p_currentScene;
  Node *p_groupButton;
  float p_seconds;
  stack<string> p_eventStack;
  unordered_map<string, SpecialFunctionWithDict> p_specialEventMap;
  void addGroupButton(const vector<string> &parameters);
  void removeGroupButton();
  void continueEvent();
public:
  static EventManager* getShareInstance();
  EventManager();
  static void setCurrentScene(BaseScene *scene);
  void runEvent(std::string eventName);
  void registerSpecialEventFunction(const string &eventId, SpecialFunctionWithDict function);
};

#endif /* EventManager_hpp */
