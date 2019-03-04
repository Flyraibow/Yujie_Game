//
//  StoryJsonData.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/23/19.
//

#ifndef StoryJsonData_hpp
#define StoryJsonData_hpp

#include <stdio.h>
#include "StoryEventContent.hpp"

using namespace std;

class StoryJsonData
{
private:
  string p_sceneName;
  void initDataWithJson(const std::string &jsonFileName);
  void initDataWithJsonContent(const nlohmann::json &jsonContent);
  vector<StoryEventContent *> p_storyEventList;
public:
  ~StoryJsonData();
  string getSceneName() const;
  vector<StoryEventContent *> getStoryEventsList() const;
  static StoryJsonData* createStoryData(const string &jsonFileName);
  static StoryJsonData* createStoryData(const nlohmann::json &jsonContent);
};

#endif /* StoryJsonData_hpp */
