#include "InputBox.h"

#include "cocos2d.h"
#include "cocos2d/cocos/ui/UIEditBox/UIEditBox.h"

#include "Classes/UIElement/Sprite/SHColorNode.hpp"
#include "Classes/UIElement/Button/SystemButton.hpp"
#include "Classes/Sys/LocalizationHelper.hpp"

namespace SailingHeroAPI {
namespace ui {

cocos2d::Node * SHInputBoxToCCInputBox(const InputBox & shInputBox)
{
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    auto background = SHColorNode::create(cocos2d::Color4B(cocos2d::Color3B::BLACK, 100), visibleSize.width, visibleSize.height);
    auto sprite = cocos2d::Sprite::create("res/base/frame/infoBox.png");
    sprite->setAnchorPoint(cocos2d::Vec2(0.5, 1));
    sprite->setPositionNormalized(cocos2d::Vec2(0.5, 1));
    auto f = cocos2d::Director::getInstance()->getContentScaleFactor();
    sprite->setScale(f);
    background->addChild(sprite);
    auto contentSize = sprite->getContentSize();

    auto hintLabel = cocos2d::Label::createWithSystemFont(shInputBox.hintLabel, "Arial", 18);
    hintLabel->setDimensions((contentSize.width * 0.9) * f, 0);
    hintLabel->setAnchorPoint(cocos2d::Vec2(0, 1));
    hintLabel->setPositionNormalized(cocos2d::Vec2(0.05, 0.83));
    hintLabel->setScale(1 / f);
    sprite->addChild(hintLabel);

    auto editBox = cocos2d::ui::EditBox::create(cocos2d::Size(contentSize.width, 24), "res/base/frame/inputFrame.jpg");
    editBox->setPlaceHolder(shInputBox.defaultText.c_str());
    editBox->setInputMode(cocos2d::ui::EditBox::InputMode::ANY);
    editBox->setPosition(Vec2(contentSize.width / 2, contentSize.height / 2));
    editBox->setMaxLength(50);
    editBox->setScale(1 / f);
    sprite->addChild(editBox);

    auto onInput = shInputBox.onInput;
    auto btnConfirm = SystemButton::defaultButtonWithText(
        LocalizationHelper::getLocalization("sys_confirm"),
        [editBox, onInput, background](cocos2d::Ref* pSender) {
            onInput(std::string(editBox->getText()));
        });

    auto btnCancel = SystemButton::defaultButtonWithText(
        LocalizationHelper::getLocalization("sys_cancel"),
        [background](cocos2d::Ref* pSender) {
            background->removeFromParent();
        });

    btnConfirm->setPositionNormalized(Vec2(0.3, 0.25));
    btnCancel->setPositionNormalized(Vec2(0.7, 0.25));
    btnConfirm->setScale(1 / f);
    btnCancel->setScale(1 / f);
    sprite->addChild(btnCancel);
    sprite->addChild(btnConfirm);

    return background;
}

}
}
