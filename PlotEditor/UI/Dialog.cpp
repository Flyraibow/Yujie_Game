#include "Dialog.h"

#include "cocos2d.h"

#include "Classes/DataManager/GenerateData/SHDataManager.hpp"
#include "../SHPlotContext.h"
#include "../SHExpression.h"

namespace SailingHeroAPI {
namespace ui {

using cocos2d::Vec2;
using cocos2d::Color4B;

bool IsQueryCharacter(char c) {
    return isalnum(c) || c == '.';
}

std::string SubstituteTextParameters(const std::string & text) {
    std::string out;
    for (size_t i = 0; i < text.size();) {
        if (text[i] == '%') {
            i = i + 1;
            size_t j = i;
            while (j < text.size() && text[j] != '%')
                ++j;
            auto expr = BuildSHExpression(text.substr(i, j - i));
            out.append(expr->eval());
            i = j + 1;
        }
        else {
            out.push_back(text[i]);
            ++i;
        }
    }
    return out;
}

cocos2d::LayerColor * SHDialogToCCDialog(const Dialog & shDialog)
{
    cocos2d::LayerColor * dialogDarkBackground = cocos2d::LayerColor::create(Color4B(0, 0, 0, 50));
    dialogDarkBackground->setAnchorPoint(Vec2());
    dialogDarkBackground->setContentSize(cocos2d::Director::getInstance()->getVisibleSize());
    // TODO: on click

    float scale = cocos2d::Director::getInstance()->getContentScaleFactor();

    cocos2d::Sprite * dialog = cocos2d::Sprite::create("res/base/dialog/dialogFrame.png");
    dialog->setScale(scale);
    dialog->setAnchorPoint(Vec2(0.5, 0));
    dialog->setNormalizedPosition(Vec2(0.5, 0));
    dialogDarkBackground->addChild(dialog);

    SHPlotContext::getInstance()->cacheSet("heroId", std::to_string(shDialog.heroId));

    cocos2d::Label *dialogContent = cocos2d::Label::createWithSystemFont(
        SubstituteTextParameters(shDialog.text), "Arial", 14);
    dialogContent->setTextColor(Color4B::BLACK);
    dialogContent->setScale(1.0f / scale);
    dialogContent->setAnchorPoint(Vec2(0.0f, 1.0f));
    dialogContent->setNormalizedPosition(Vec2(0.1f, shDialog.showFullName ? 0.7f : 0.85f));
    dialogContent->setDimensions(dialog->getContentSize().width * scale * 0.8, 0);
    dialog->addChild(dialogContent);

    if (shDialog.showFullName) {
        cocos2d::Label *dialogSpeakerName = cocos2d::Label::createWithSystemFont(
            SHDataManager::getHeroDataById(shDialog.heroId)->getHeroFirstName(),
            "Arial", 14);
        dialogSpeakerName->setTextColor(Color4B::BLACK);
        dialogSpeakerName->setScale(1.0f / scale);
        dialogSpeakerName->setAnchorPoint(Vec2(0.0f, 1.0f));
        dialogSpeakerName->setNormalizedPosition(Vec2(0.1f, 0.85f));
        dialog->addChild(dialogSpeakerName);
    }

    if (shDialog.showImage) {
        cocos2d::Node *dialogSpeaker = cocos2d::Node::create();
        cocos2d::Sprite *dialogSpeakerBackground =
            cocos2d::Sprite::create("res/base/dialog/dialogPhotoFrame.png");
        cocos2d::Sprite * dialogSpeakerPhoto =
            SHDataManager::getHeroDataById(shDialog.heroId)->getPhoto();

        dialogSpeakerBackground->setAnchorPoint(Vec2());
        dialogSpeaker->addChild(dialogSpeakerBackground, 2);
        dialogSpeaker->setContentSize(dialogSpeakerBackground->getContentSize());

        dialogSpeakerPhoto->setAnchorPoint(Vec2());
        dialogSpeakerPhoto->setPosition(Vec2(8.0f / scale, 8.0f / scale));
        dialogSpeaker->addChild(dialogSpeakerPhoto);

        dialogSpeaker->setAnchorPoint(Vec2(1.0f, 0.0f));
        dialogSpeaker->setNormalizedPosition(Vec2());
        dialog->addChild(dialogSpeaker);
    }

    return dialogDarkBackground;
}

}
}
