//
//  SHJSONContent.cpp
//  SailingHero
//
//  Created by Yujie Liu on 9/26/18.
//

#include "SHJSONContent.hpp"

nlohmann::json loadContentFromPath(const std::string &jsonFilePath)
{
  CCASSERT( cocos2d::FileUtils::getInstance()->isFileExist(jsonFilePath), ("file doesn't exist : " + jsonFilePath).c_str());
  auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(jsonFilePath);
  std::string str(reinterpret_cast<char*>(data.getBytes()));
  // data.getBytes() is not accurate, only the first size chars are needed
  str = str.substr(0, data.getSize());
  nlohmann::json content = nlohmann::json::parse(str);
  return content;
}

SHJSONContent::SHJSONContent(const std::string &jsonFilePath)
{
    p_jsonContent = loadContentFromPath(jsonFilePath);
}

std::vector<SHComponent *> SHJSONContent::getComponentList() const
{
  return SHComponent::getComponentsFromJson(p_jsonContent);
}


const nlohmann::json& SHJSONContent::getContent() const
{
  return p_jsonContent;
}
