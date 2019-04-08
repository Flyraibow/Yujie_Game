//
//  SubStoryEventContent.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/23/19.
//

#ifndef SubStoryEventContent_hpp
#define SubStoryEventContent_hpp

#include "StoryEventContent.hpp"

class StoryJsonData;

class SubStoryEventContent : public StoryEventContent
{
private:
  string p_subStoryName;
  nlohmann::json p_subStoryJson;
  StoryJsonData *p_subStoryData;
  bool p_noCallback;
public:
  ~SubStoryEventContent();
  SubStoryEventContent(const nlohmann::json &jsonContent);
  void runEvent(StoryEventCallback callback);
};


#endif /* SubStoryEventContent_hpp */
