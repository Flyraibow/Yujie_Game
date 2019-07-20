//
//  JSONContent.cpp
//  SailingHero
//
//  Created by Yujie Liu on 9/26/18.
//

#include "JSONContent.hpp"

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

JSONContent::JSONContent(const nlohmann::json &jsonContent)
{
  p_jsonContent = jsonContent;
}

JSONContent::JSONContent(const std::string &jsonFilePath)
{
    p_jsonContent = loadContentFromPath(jsonFilePath);
}

const nlohmann::json& JSONContent::getContent() const
{
  return p_jsonContent;
}
