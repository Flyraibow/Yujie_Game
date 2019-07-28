//
//  ColorLayerComponent.cpp
//  YJGameLibrary
//
//  Created by Yujie Liu on 7/16/19.
//

#include "ColorLayerComponent.hpp"

LayerColor* generateFromJsonStruct(const ColorLayerJsonStruct* nodeStruct, Node* parent)
{
  auto contentSize = nodeStruct->getContentSize();
  auto layer = LayerColor::create(nodeStruct->color, contentSize.width, contentSize.height);
  return layer;
}
