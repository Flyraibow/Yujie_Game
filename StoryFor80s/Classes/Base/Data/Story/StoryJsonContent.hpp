//
//  StoryJsonContent.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/23/19.
//

#ifndef StoryJsonContent_hpp
#define StoryJsonContent_hpp

#include <stdio.h>
#include "JSONContent.hpp"
#include "StoryEventContent.hpp"
#include <vector>

using namespace std;

class StoryJsonContent : public JSONContent
{
public:
  StoryJsonContent(const std::string &jsonFileName);
  StoryJsonContent(const nlohmann::json &jsonContent) : JSONContent(jsonContent) {};
  std::string getScene() const;
  vector<StoryEventContent *> getStoryEventList();
};


#endif /* StoryJsonContent_hpp */