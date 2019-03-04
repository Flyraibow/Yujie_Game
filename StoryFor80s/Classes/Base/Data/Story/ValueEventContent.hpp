//
//  ValueEventContent.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/24/19.
//

#ifndef ValueEventContent_hpp
#define ValueEventContent_hpp

#include "StoryEventContent.hpp"

class ValueEventContent : public StoryEventContent
{
private:
  nlohmann::json p_values;
public:
  ValueEventContent(const nlohmann::json &jsonContent);
  void runEvent(StoryEventCallback callback);
};

#endif /* ValueEventContent_hpp */
