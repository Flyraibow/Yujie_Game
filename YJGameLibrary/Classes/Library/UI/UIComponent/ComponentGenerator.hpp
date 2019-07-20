//
//  ComponentGenerator.hpp
//  YJGameLibrary
//
//  Created by Yujie Liu on 7/16/19.
//

#ifndef ComponentGenerator_hpp
#define ComponentGenerator_hpp

#include "cocos2d.h"
#include "NodeJsonStruct.hpp"

USING_NS_CC;

Node* createNodeFromJsonStruct(NodeJsonStruct* nodeStruct, Node* parent);

#endif /* ComponentGenerator_hpp */
