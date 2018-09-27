//
//  SHJSONContent.hpp
//  SailingHero
//
//  Created by Yujie Liu on 9/26/18.
//

#ifndef SHJSONContent_hpp
#define SHJSONContent_hpp

#include "cocos2d.h"
#include "json.hpp"
#include "SHComponent.hpp"
#include <vector>

USING_NS_CC;

class SHJSONContent
{
protected:
  nlohmann::json p_jsonContent;
public:
  SHJSONContent(const std::string &jsonFilePath);
  const nlohmann::json& getContent() const;
  
  std::vector<SHComponent *> getComponentList() const;
};

#endif /* SHJSONContent_hpp */
