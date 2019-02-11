//
//  LocalizationHelper.cpp
//
//  Created by Yujie Liu on 5/16/18.
//

#include "LocalizationHelper.hpp"

#include <string>

#include "cocos2d.h"

#include "ByteBuffer.hpp"
#include "Utils.hpp"

USING_NS_CC;

using namespace std;

static LocalizationHelper *s_sharedLocalizationHelper = nullptr;

LocalizationHelper* LocalizationHelper::getInstance()
{
  if (!s_sharedLocalizationHelper)
  {
    s_sharedLocalizationHelper = new (std::nothrow) LocalizationHelper();
    s_sharedLocalizationHelper->load("res/base/translation/chinese.lang");
  }
  
  return s_sharedLocalizationHelper;
}

void LocalizationHelper::load(const std::string &filename)
{
  auto data = FileUtils::getInstance()->getDataFromFile(filename);
  
  if (!data.isNull())
  {
    auto bytes = data.getBytes();
    
    auto buffer = std::make_unique<bb::ByteBuffer>(bytes, data.getSize());
    auto count = buffer->getLong();
    for (int i = 0; i < count; ++i) {
      string localId = buffer->getString();
      string translation = buffer->getString();
      s_map[localId] = translation;
    }
  }
  else CCLOGWARN("FILE %s not found", filename.c_str());
}

string LocalizationHelper::getLocalization(const string &localId)
{
  if (LocalizationHelper::getInstance()->s_map.count(localId)) {
    return LocalizationHelper::getInstance()->s_map.at(localId);
  }
  CCLOGWARN("Local id doesn't have translation: %s", localId.c_str());
  return localId;
}

string LocalizationHelper::getLocalization(const string &localId, const string &param)
{
  if (LocalizationHelper::getInstance()->s_map.count(localId)) {
    return SHUtil::format(LocalizationHelper::getInstance()->s_map.at(localId).c_str(), param.c_str());
  }
  CCLOGWARN("Local id doesn't have translation: %s", localId.c_str());
  return localId;
}

