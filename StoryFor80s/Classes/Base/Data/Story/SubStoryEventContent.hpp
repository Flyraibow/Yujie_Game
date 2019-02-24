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
  StoryJsonData *p_subStoryData;
public:
  ~SubStoryEventContent();
  SubStoryEventContent(const nlohmann::json &jsonContent);
  void runEvent(BaseScene *baseScene, StoryEventCallback callback);
};


#endif /* SubStoryEventContent_hpp */
