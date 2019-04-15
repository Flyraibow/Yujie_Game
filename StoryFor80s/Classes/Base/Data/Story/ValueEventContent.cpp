//
//  ValueEventContent.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/24/19.
//

#include "ValueEventContent.hpp"
#include "JsonUtil.hpp"
#include "Utils.hpp"
#include "DataManager.hpp"


ValueEventContent::ValueEventContent(const nlohmann::json &jsonContent) : StoryEventContent(jsonContent)
{
  p_changes = Utils::getJsonListFromJson(jsonContent, "changes");
  if (jsonContent.count("values")) {
    p_values = jsonContent.at("values");
  }
  p_dataListString = Utils::getStringFromJson(jsonContent, "dataList");
}

void ValueEventContent::changeData(BaseData *associate)
{
  for (auto changeJson : p_changes) {
    auto dataStr = Utils::getStringFromJson(changeJson, "data");
    CCASSERT(dataStr.length() > 0, "Value must have data");
    auto type = Utils::getStringFromJson(changeJson, "type");
    auto field = Utils::getStringFromJson(changeJson, "field");
    auto valueStr = Utils::getStringFromJson(changeJson, "value");
    
    auto data = DataManager::getShareInstance()->decipherData(dataStr, associate);
    auto value = DataManager::getShareInstance()->decipherString(valueStr, associate);
    if (type == "add") {
      auto intValue = atoi(data->getFieldValue(field).c_str()) + atoi(value.c_str());
      value = to_string(intValue);
    }
    data->setFieldValue(field, value);
  }
}


void ValueEventContent::runEvent(StoryEventCallback callback)
{
  if (!p_values.empty()) {
    // // quick value set
    for (auto iter = p_values.begin(); iter != p_values.end(); ++iter) {
      auto key = iter.key();
      auto value = Utils::getStringFromJson(p_values, key);
      DataManager::getShareInstance()->setValue(key, value);
    }
  }
  if (p_dataListString.size() > 0) {
    auto dataList = DataManager::getShareInstance()->decipherDataList(p_dataListString);
    for (auto data : dataList) {
      changeData(data);
    }
  } else {
    changeData();
  }
  callback();
}


