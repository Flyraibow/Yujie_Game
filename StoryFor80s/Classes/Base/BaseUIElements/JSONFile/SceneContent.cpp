//
//  SceneContent.cpp
//
//  Created by Yujie Liu on 9/17/18.
//

#include "SceneContent.hpp"
#include "JsonUtil.hpp"

using namespace nlohmann;

SceneContent::SceneContent(const std::string &jsonFileName) : JSONContent("res/base/scene/" + jsonFileName + ".json")
{
}

std::string SceneContent::getBackgroundImage() const
{
  return SHUtil::getStringFromJson(p_jsonContent, "backgroundImage");
}

std::string SceneContent::getBackgroundMusic() const
{
  return SHUtil::getStringFromJson(p_jsonContent, "backgroundMusic");
}

std::string SceneContent::getInitialEvent() const
{
  return SHUtil::getStringFromJson(p_jsonContent, "initialEvent");
}

std::string SceneContent::getAddOnEvent() const
{
  return SHUtil::getStringFromJson(p_jsonContent, "addOnEvent");
}

bool SceneContent::isFullScreenCover() const
{
  return SHUtil::getBoolFromJson(p_jsonContent, "fullScreenCover");
}

Size SceneContent::getScreenCoverRatio() const
{
  return SHUtil::getSizeFromJson(p_jsonContent, "screenCoverRatio");
}
