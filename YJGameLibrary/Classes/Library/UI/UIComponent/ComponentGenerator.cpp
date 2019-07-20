//
//  ComponentGenerator.cpp
//  YJGameLibrary
//
//  Created by Yujie Liu on 7/16/19.
//

#include "ComponentGenerator.hpp"
#include "ColorLayerComponent.hpp"

Node* createNodeFromJsonStruct(NodeJsonStruct* nodeStruct, Node* parent)
{
  Node *node = nullptr;
  switch (nodeStruct->type) {
    case NodeTypeColorLayer:
    {
      auto colorStruct = static_cast<ColorLayerJsonStruct *>(nodeStruct);
      node = generateFromJsonStruct(colorStruct, parent);
    }
  }
  if (node != nullptr && parent != nullptr) {
    parent->addChild(node);
  }
  return node;
}
