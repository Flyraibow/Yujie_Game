//
//  SHScene.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 5/27/18.
//

#include "SHScene.hpp"
#include "audio/include/SimpleAudioEngine.h"

#include "SHColorNode.hpp"
#include <string>

#ifdef COVER_DEBUG
#define COVER_COLOR Color4B(255, 0, 0, 100)
#else
#define COVER_COLOR Color4B(0, 0, 0, 255)
#endif

using namespace std;

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
        s_screenSize = Size(visibleSize.width  - expectWidth, visibleSize.height);
    } else  {
        nodeSize = Size(expectWidth, (visibleSize.height - expectHeight) / 2);
        s_screenSize = Size(visibleSize.width, visibleSize.height - expectHeight);
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

Size SHScene::getScreenSize() const
{
    if (s_screenSize.width == 0 || s_screenSize.height == 0) {
        return Director::getInstance()->getVisibleSize();
    }
    return s_screenSize;
}

void SHScene::setBackgroundImage(std::string imgPath) {
    auto background = Sprite::create(imgPath);
    CCASSERT(background, ("unable to find image with path : " + imgPath).c_str());
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto contentSize = background->getContentSize();
    // TODO: ADD how to set align, vertical or horizontal or minimum or maximum or actual size
    auto r1 = visibleSize.width / contentSize.width;
    auto r2 = visibleSize.height / contentSize.height;
    auto r = max(r1, r2);
    background->setScale(r);
    background->setNormalizedPosition(Vec2(0.5, 0.5));
    this->addChild(background);
}

void SHScene::setBackgroundMusic(std::string path) {
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->preloadBackgroundMusic(path.c_str());
    audio->playBackgroundMusic(path.c_str(), true);
}
