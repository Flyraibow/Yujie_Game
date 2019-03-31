//
//  RefreshEventContent.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 3/23/19.
//

#ifndef RefreshEventContent_hpp
#define RefreshEventContent_hpp

#include "StoryEventContent.hpp"

class StoryJsonData;

class RefreshEventContent : public StoryEventContent
{
private:
  vector<string> p_refreshIds;
public:
  RefreshEventContent(const nlohmann::json &jsonContent);
  void runEvent(StoryEventCallback callback);
};

#endif /* RefreshEventContent_hpp */
