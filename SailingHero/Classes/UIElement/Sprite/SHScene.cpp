//
//  SHScene.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 5/27/18.
//

#include "SHScene.hpp"

#include "SHColorNode.hpp"

#ifdef COVER_DEBUG
#define COVER_COLOR Color4B(255, 0, 0, 100)
#else
#define COVER_COLOR Color4B(0, 0, 0, 255)
#endif


void SHScene::setScreenCover(Size ratioSize)
{
    assert(ratioSize.width > 0 && ratioSize.height > 0);
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    double ratio = ratioSize.width / ratioSize.height;
    double expectHeight = visibleSize.width / ratio;
    double expectWidth = visibleSize.width;
    bool verticalFlag = true;
    Size nodeSize;
    if (expectHeight > visibleSize.height) {
        expectWidth = visibleSize.height * ratio;
        verticalFlag = false;
        nodeSize = Size((visibleSize.width - expectWidth) / 2, visibleSize.height);
    } else  {
        nodeSize = Size(expectWidth, (visibleSize.height - expectHeight) / 2);
    }
    if (nodeSize.width < 1 || nodeSize.height < 1) {
        // there is no need to create a cover
        return;
    }
    
    auto n1 = SHColorNode::create(COVER_COLOR, nodeSize.width, nodeSize.height);
    auto n2 = SHColorNode::create(COVER_COLOR, nodeSize.width, nodeSize.height);
    if (verticalFlag) {
        n2->setPosition(0, visibleSize.height - nodeSize.height);
    } else {
        n2->setPosition(visibleSize.width - nodeSize.width, 0);
    }
    n1->setName("Cover page 1");
    n2->setName("Cover page 2");
    auto node = Node::create();
    node->addChild(n1);
    node->addChild(n2);
    node->setPosition(origin);
    this->addChild(node, SCREEN_COVER_LAYER_HEIGHT);
}
