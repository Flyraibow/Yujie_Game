//
//  SHBaseSceneContent.cpp
//  SailingHero
//
//  Created by Yujie Liu on 9/17/18.
//

#include "SHBaseSceneContent.hpp"

using namespace nlohmann;

SHBaseSceneContent* SHBaseSceneContent::loadContentFromPath(std::string jsonFilePath)
{
  auto data = FileUtils::getInstance()->getDataFromFile(jsonFilePath);
  std::string str(reinterpret_cast<char*>(data.getBytes()));
  // data.getBytes() is not accurate, only the first size chars are needed
  str = str.substr(0, data.getSize());
  auto sceneContent = new SHBaseSceneContent();
  sceneContent->p_jsonContent = json::parse(str);
  CCLOG("json scene : %s", sceneContent->p_jsonContent.dump().c_str());
  return sceneContent;
}



std::string SHBaseSceneContent::getBackgroundImage()
{
  if (p_jsonContent.count("backgroundImage")) {
    return p_jsonContent.at("backgroundImage");
  }
  return "";
}

bool SHBaseSceneContent::isFullScreenCover()
{
  if (p_jsonContent.count("fullScreenCover")) {
    return p_jsonContent.at("fullScreenCover");
  }
  return false;
}

