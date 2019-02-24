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

class StoryData;
class BaseScene;
class StoryEventContent;

using namespace std;

class StoryManager
{
private:
  static StoryManager* p_sharedManager;
  BaseScene* p_storyScene;
  stack<StoryEventContent *> p_stackStories;
  
  void startStory(const StoryData *storyData);
  void startStoryEventList(const vector<StoryEventContent *> &storyEventList);
  void startStoryEvent(const StoryEventContent *storyEventContent);
  void startNextStoryEvent();
public:
  static StoryManager* getShareInstance();
  void checkAndStartStory();
};

#endif /* StoryManager_hpp */
