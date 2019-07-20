//
//  ColorLayerJsonStruct.hpp
//  YJGameLibrary
//
//  Created by Yujie Liu on 7/16/19.
//

#ifndef ColorLayerJsonStruct_hpp
#define ColorLayerJsonStruct_hpp

#include "NodeJsonStruct.hpp"

class ColorLayerJsonStruct : public NodeJsonStruct {
public:
  cocos2d::Color4B color;
  
  ColorLayerJsonStruct(const nlohmann::json &json);
};

#endif /* ColorLayerJsonStruct_hpp */
