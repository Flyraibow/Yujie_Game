//
//  ColorLayerComponent.cpp
//  YJGameLibrary
//
//  Created by Yujie Liu on 7/16/19.
//

#include "ColorLayerComponent.hpp"

LayerColor* generateFromJsonStruct(const ColorLayerJsonStruct* nodeStruct, Node* parent)
{
  auto layer = LayerColor::create(nodeStruct->color, nodeStruct->contentSize.width, nodeStruct->contentSize.height);
  return layer;
}
