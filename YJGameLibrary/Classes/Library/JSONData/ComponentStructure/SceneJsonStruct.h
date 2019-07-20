//
//  SceneJsonStruct.h
//  YJGameLibrary
//
//  Created by Yujie Liu on 7/16/19.
//

#ifndef SceneJsonStruct_h
#define SceneJsonStruct_h

#include "cocos2d.h"
#include "NodeJsonStruct.hpp"
#include <vector>
#include "JsonUtil.hpp"

struct SceneJsonStruct {
  std::string backgroundMusic;
  std::vector<NodeJsonStruct *> componentStructs;
  
  SceneJsonStruct(const nlohmann::json &json) {
    backgroundMusic = JsonUtils::getStringFromJson(json, "music");
    std::vector<NodeJsonStruct *> components;
    auto jsonList = JsonUtils::getJsonListFromJson(json, "components");
    for (auto j : jsonList) {
      auto nodeStruct = NodeJsonStruct::createNodeFromJson(j);
      components.push_back(nodeStruct);
    }
    componentStructs = components;
  }
  
  ~SceneJsonStruct() {
    for (auto component : componentStructs) {
      delete component;
    }
    componentStructs.clear();
  }
};

#endif /* SceneJsonStructure_h */
