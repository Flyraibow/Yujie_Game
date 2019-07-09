//
//  SpecialFunctions.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/17/19.
//

#ifndef SpecialFunctions_hpp
#define SpecialFunctions_hpp

#include <stdio.h>
#include <map>
#include "json.hpp"

using namespace std;

namespace story {
  void passDay(const nlohmann::json &jsonContent);
  void passMonth(const nlohmann::json &jsonContent);
  void getTask(const nlohmann::json &jsonContent);
}

namespace game {
  void homePage(const nlohmann::json &jsonContent);
  void save(const nlohmann::json &jsonContent);
  void load(const nlohmann::json &jsonContent);
  void saveGlobal(const nlohmann::json &jsonContent);
  void updateSoundVolume(const nlohmann::json &jsonContent);
}

#endif /* SpecialFunctions_hpp */
