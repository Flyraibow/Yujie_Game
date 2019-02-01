//
//  StoryManager.hpp
//  SailingHero
//
//  Created by Yujie Liu on 10/19/18.
//

#ifndef StoryManager_hpp
#define StoryManager_hpp

#include <stdio.h>

class StoryData;
class StoryScene;

using namespace std;

class StoryManager
{
private:
  static StoryManager* p_sharedManager;
  StoryScene* p_storyScene;
  
  void startStory(const StoryData *storyData);
  void startEventAfterComplete() const;
public:
  static StoryManager* getShareInstance();
  void checkAndStartStory();
};

#endif /* StoryManager_hpp */
