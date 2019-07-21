//
//  JSONContent.cpp
//  SailingHero
//
//  Created by Yujie Liu on 9/26/18.
//

#include "JSONContent.hpp"

USING_NS_CC;



nlohmann::json loadContentFromPath(const std::string &jsonFilePath)
{
  CCASSERT( FileUtils::getInstance()->isFileExist(jsonFilePath), ("file doesn't exist : " + jsonFilePath).c_str());
  auto data = FileUtils::getInstance()->getDataFromFile(jsonFilePath);
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

void JSONContent::verifyAllJsonFormatsUnder(const std::string &directoryPath)
{
  auto fileUtils = FileUtils::getInstance();
  std::vector<std::string> files;
  fileUtils->listFilesRecursively(directoryPath, &files);
  for (auto file : files) {
    CCLOG("===== %s", file.c_str());
    if (fileUtils->getFileExtension(file) == ".json") {
      CCLOG("start checking file x %s", file.c_str());
      auto j = new JSONContent(file);
      CCLOG("finish checking, content %s", j->getContent().dump().c_str());
    }
  }
}
