//
//  JSONContent.hpp
//
//  Created by Yujie Liu on 9/26/18.
//

#ifndef JSONContent_hpp
#define JSONContent_hpp

#include "cocos2d.h"
#include "json.hpp"
#include "BaseComponent.hpp"
#include <vector>

USING_NS_CC;

class JSONContent
{
protected:
  nlohmann::json p_jsonContent;
public:
  JSONContent(const std::string &jsonFilePath);
  const nlohmann::json& getContent() const;
  
  std::vector<BaseComponent *> getComponentList() const;
};

#endif /* JSONContent_hpp */
