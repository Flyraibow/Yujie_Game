//
//  JSONContent.hpp
//
//  Created by Yujie Liu on 9/26/18.
//

#ifndef JSONContent_hpp
#define JSONContent_hpp

#include "cocos2d.h"
#include "json.hpp"
#include <vector>

USING_NS_CC;

class JSONContent
{
protected:
  nlohmann::json p_jsonContent;
public:
  JSONContent(const std::string &jsonFilePath);
  JSONContent(const nlohmann::json &jsonContent);
  const nlohmann::json& getContent() const;
};

#endif /* JSONContent_hpp */
