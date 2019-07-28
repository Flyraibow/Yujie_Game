//
//  NodeJsonStruct.hpp
//  YJGameLibrary
//
//  Created by Yujie Liu on 7/16/19.
//

#ifndef NodeJsonStruct_hpp
#define NodeJsonStruct_hpp

#include "cocos2d.h"
#include "JsonUtils.hpp"

using namespace std;

enum NodePositionType {
  NodePositionDefault = 1,
  NodeFullScreen = 2,
};

enum NodeType {
  NodeTypeDefault,
  NodeTypeColorLayer,
};

class NodeJsonStruct {
protected:
  NodePositionType p_positionType;
public:
  // Node name, used to identify a node
  string name;
  NodeType type;
  cocos2d::Vec2 anchor;
  cocos2d::Vec2 poistion;
  float upEdge;
  float rightEdge;
  float downEdge;
  float leftEdge;
  float scale;
  NodeJsonStruct(const nlohmann::json &json);
  
  
  cocos2d::Size getContentSize() const;
  
  static NodeJsonStruct* createNodeFromJson(const nlohmann::json &json);
};

#endif /* NodeJsonStruct_hpp */
