//
//  StoryJsonData.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/23/19.
//

#ifndef StoryJsonData_hpp
#define StoryJsonData_hpp

#include <stdio.h>
#include "base/CCRef.h"
#include "StoryEventContent.hpp"

using namespace std;

class StoryJsonData : public cocos2d::Ref
{
private:
  string p_sceneName;
  void initDataWithJson(const std::string &jsonFileName);
  vector<StoryEventContent *> p_storyEventList;
public:
  CREATE_FUNC(StoryJsonData);
  bool init() { return true;}
  string getSceneName() const;
  vector<StoryEventContent *> getStoryEventsList();
  static StoryJsonData* createStoryData(const string &jsonFileName);
};

#endif /* StoryJsonData_hpp */
