//
//  ColorLayerComponent.hpp
//  YJGameLibrary
//
//  Created by Yujie Liu on 7/16/19.
//

#ifndef ColorLayerComponent_hpp
#define ColorLayerComponent_hpp

#include "cocos2d.h"
#include "ColorLayerJsonStruct.hpp"

USING_NS_CC;

LayerColor* generateFromJsonStruct(const ColorLayerJsonStruct* nodeStruct, Node* parent);


#endif /* ColorLayerComponent_hpp */
