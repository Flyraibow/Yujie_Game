//
//  StoryManager.hpp
//  StoryFor80s-mobile
//
//  Created by Yujie Liu on 2/23/19.
//

#ifndef StoryManager_hpp
#define StoryManager_hpp

#include <stdio.h>
#include <stack>
#include <unordered_map>
#include "json.hpp"

class StoryData;
class BaseScene;
class StoryEventContent;
class StoryJsonData;

using namespace std;

typedef void (*SpecialFunctionWithDict)(const nlohmann::json &jsonContent);

class StoryManager
{
private:
  static StoryManager* p_sharedManager;
  static unordered_map<string, SpecialFunctionWithDict> s_specialEventMap;
  
  BaseScene* p_storyScene;
  stack<StoryEventContent *> p_stackStories;
  StoryEventContent *p_currentEvent = nullptr;
  
  void startStory(const StoryData *storyData);
  void addStoryEventList(const vector<StoryEventContent *> &storyEventList);
  void startStoryEvent(StoryEventContent *storyEventContent);
  void startNextStoryEvent();
public:
  static StoryManager* getShareInstance();
  static void registerSpecialEventFunction(const string &functionId, SpecialFunctionWithDict function);
  static bool isFunctionRegistered(const string &functionId);
  static void runFunction(const string &functionId, const nlohmann::json &jsonContent);
  
  void checkAndStartStory();
  bool startStory(const string &storyName);
  bool startStory(const StoryJsonData *storyName);
  void stopStory();
};

#endif /* StoryManager_hpp */
