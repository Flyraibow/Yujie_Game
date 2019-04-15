//
//  ValueEventContent.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/24/19.
//

#ifndef ValueEventContent_hpp
#define ValueEventContent_hpp

#include "StoryEventContent.hpp"

class BaseData;

class ValueEventContent : public StoryEventContent
{
private:
  vector<nlohmann::json> p_changes;
  nlohmann::json p_values;  // quick set
  string p_dataListString;
  void changeData(BaseData *associate = nullptr);
public:
  ValueEventContent(const nlohmann::json &jsonContent);
  void runEvent(StoryEventCallback callback);
};

#endif /* ValueEventContent_hpp */
