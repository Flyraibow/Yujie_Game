//
//  JsonUtils.hpp
//
//  Created by Yujie Liu on 9/26/18.
//

#ifndef JsonUtils_hpp
#define JsonUtils_hpp

#include "json.hpp"

namespace JsonUtils {
  std::string getStringFromJson(const nlohmann::json &json, const std::string &field, const std::string &defaultValue = "");
  int getIntFromJson(const nlohmann::json &json, const std::string &field, const int defaultValue = 0);
  float getFloatFromJson(const nlohmann::json &json, const std::string &field, const float defaultValue = 0);
  float getDoubleFromJson(const nlohmann::json &json, const std::string &field, const float defaultValue = 0);
  bool getBoolFromJson(const nlohmann::json &json, const std::string &field, bool defaultValue = false);
  std::vector<std::string> getStringListFromJson(const nlohmann::json &json, const std::string &field);
  std::vector<nlohmann::json> getJsonListFromJson(const nlohmann::json &json, const std::string &field);
  std::pair<double, double> getPositionPairFromJson(const nlohmann::json &json, const std::string &field, const std::pair<double, double> &defaultValue = std::make_pair(0, 0));
  nlohmann::json getChildJsonFromJson(const nlohmann::json &json, const std::string &field);
  std::vector<std::string> getKeysFromJson(const nlohmann::json &json);
}

#endif /* JsonUtil_hpp */
