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
  NodeNormalizedPosition = 1 << 1,
  NodeNormalizedSize = 1 << 2,
  NodeUpEdge = 1 << 3,
  NodeDownEdge = 1 << 4,
  NodeLeftEdge = 1 << 5,
  NodeRightEdge = 1 << 6,
  NodeUpNormalizedEdge = 1 << 7,
  NodeDownNormalizedEdge = 1 << 8,
  NodeLeftNormalizedEdge = 1 << 9,
  NodeRightNormalizedEdge = 1 << 10,
};

enum NodeType {
  NodeTypeDefault,
  NodeTypeColorLayer,
};

class NodeJsonStruct {
public:
  // Node name, used to identify a node
  string name;
  NodeType type;
  NodePositionType positionType;
  cocos2d::Vec2 anchor;
  cocos2d::Vec2 poistion;
  cocos2d::Size contentSize;
  float upEdge;
  float rightEdge;
  float downEdge;
  float leftEdge;
  float scale;
  NodeJsonStruct(const nlohmann::json &json);
  
  static NodeJsonStruct* createNodeFromJson(const nlohmann::json &json);
};

#endif /* NodeJsonStruct_hpp */
