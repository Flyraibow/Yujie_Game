#include "SHScenario.h"

#include "SHScene.hpp"
#include "SHDataManager.h"
#include "ui/UIButton.h"
#include "audio/include/SimpleAudioEngine.h"

namespace {

using ::SailingHeroAPI::SHScenario;
using ::SailingHeroAPI::SHDataManager;

cocos2d::ui::Button * SHButtonToCCButton(const SailingHeroAPI::ui::Button & shButton) {
    auto image = "res/button_up.png";
    cocos2d::ui::Button * button = cocos2d::ui::Button::create(image);
    button->setScale9Enabled(true);
    button->setTitleAlignment(cocos2d::TextHAlignment::CENTER);
    button->setTitleText(shButton.text);
    auto lbl_size = button->getTitleRenderer()->getContentSize();
    button->setContentSize(cocos2d::Size(lbl_size.width + 20, lbl_size.height + 10));
    button->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
    button->setPositionType(cocos2d::ui::Widget::PositionType::PERCENT);
    button->setScale(5.0f);
    button->setPositionPercent(cocos2d::Vec2(shButton.centerPos.x, shButton.centerPos.y));
    auto onClick = shButton.onClick;
    button->addClickEventListener([onClick](Ref *) {
            if (onClick)
                onClick();
        });

    return button;
}

cocos2d::LayerColor * SHDialogToCCDialog(const SailingHeroAPI::ui::Dialog & shDialog) {
    cocos2d::LayerColor * dialogDarkBackground = cocos2d::LayerColor::create(Color4B(0, 0, 0, 50));
    dialogDarkBackground->setAnchorPoint(Vec2());
    dialogDarkBackground->setContentSize(Director::getInstance()->getVisibleSize());
    // TODO: on click

    float scale = Director::getInstance()->getContentScaleFactor();

    cocos2d::Sprite * dialog = cocos2d::Sprite::create("res/base/dialog/dialogFrame.png");
    dialog->setScale(scale);
    dialog->setAnchorPoint(Vec2(0.5, 0));
    dialog->setNormalizedPosition(Vec2(0.5, 0));
    dialogDarkBackground->addChild(dialog);

    cocos2d::Label * dialogContent =
        cocos2d::Label::createWithSystemFont(shDialog.text, "Arial", 14);
    dialogContent->setTextColor(Color4B::BLACK);
    dialogContent->setScale(1.0f / scale);
    dialogContent->setAnchorPoint(Vec2(0.0f, 1.0f));
    dialogContent->setNormalizedPosition(Vec2(0.1f, shDialog.showFullName ? 0.7f : 0.85f));
    dialogContent->setDimensions(dialog->getContentSize().width * scale * 0.8, 0);
    dialog->addChild(dialogContent);

    if (shDialog.showFullName) {
        cocos2d::Label *dialogSpeakerName = cocos2d::Label::createWithSystemFont(
            SHDataManager::getInstance()->getHeroData(shDialog.heroId)->getHeroFirstName(),
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
            SHDataManager::getInstance()->getHeroData(shDialog.heroId)->getPhoto();

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

class CCSceneWrapper : public SHScene {
    friend ::SailingHeroAPI::SHScenario;
public:
    CREATE_FUNC(CCSceneWrapper);

    bool init() override {
        if (!SHScene::init())
            return false;

        shScenario = nullptr;
        return true;
    }

    void setupWith(SHScenario *scenario) {
        shScenario = scenario;

        if (!scenario->getBackgroundImage().empty())
            setBackgroundImage(scenario->getBackgroundImage());
        if (!scenario->getBackgroundMusic().empty())
            CocosDenshion::SimpleAudioEngine::getInstance()
                ->preloadBackgroundMusic(scenario->getBackgroundMusic().data());
        for (auto & bt : scenario->getAllButton()) {
            addChild(SHButtonToCCButton(bt));
        }
        for (auto & dialog : scenario->getAllDialog()) {
            addChild(SHDialogToCCDialog(dialog));
        }
    }

    void onEnter() override {
        SHScene::onEnter();

        if (shScenario && !shScenario->getBackgroundMusic().empty()) {
            CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(
                shScenario->getBackgroundMusic().c_str(), true);
        }
    }
    void onEnterTransitionDidFinish() override {
        SHScene::onEnterTransitionDidFinish();
        // do something
    }
    void onExit() override {
        // do something
        SHScene::onExit();
    }
    void onExitTransitionDidStart() override {
        if (shScenario && !shScenario->getBackgroundMusic().empty()) {
            CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(
                false);
        }

        SHScene::onExitTransitionDidStart();
    }

private:
    SHScenario * shScenario;
};

}

namespace SailingHeroAPI {

cocos2d::Scene * SHScenario::getCCScene()
{
    if (ccScene == nullptr) {
        ccScene = CCSceneWrapper::create();
        ccScene->retain();
    }
    return ccScene;
}

void SHScenario::setupCCScene() {
    if (!ccSceneReady) {
        CCSceneWrapper * scene = dynamic_cast<CCSceneWrapper *>(getCCScene());
        scene->setupWith(this);
        ccSceneReady = true;
    }
}

}