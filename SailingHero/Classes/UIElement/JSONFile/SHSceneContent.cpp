//
//  SHSceneContent.cpp
//  SailingHero
//
//  Created by Yujie Liu on 9/17/18.
//

#include "SHSceneContent.hpp"
#include "JsonUtil.hpp"

using namespace nlohmann;

SHSceneContent::SHSceneContent(const std::string &jsonFileName) : SHJSONContent("res/base/scene/" + jsonFileName + ".json")
{
}

std::string SHSceneContent::getBackgroundImage() const
{
  return SHUtil::getStringFromJson(p_jsonContent, "backgroundImage");
}

std::string SHSceneContent::getBackgroundMusic() const
{
  return SHUtil::getStringFromJson(p_jsonContent, "backgroundMusic");
}

std::string SHSceneContent::getInitialEvent() const
{
  return SHUtil::getStringFromJson(p_jsonContent, "initialEvent");
}

bool SHSceneContent::isFullScreenCover() const
{
  return SHUtil::getBoolFromJson(p_jsonContent, "fullScreenCover");
}

Size SHSceneContent::getScreenCoverRatio() const
{
  return SHUtil::getSizeFromJson(p_jsonContent, "screenCoverRatio");
}
