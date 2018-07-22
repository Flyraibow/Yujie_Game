#include "SHScenario.h"

#include "SHScene.hpp"
#include "SystemButton.hpp"
#include "audio/include/SimpleAudioEngine.h"

namespace {

using ::SailingHeroAPI::SHScenario;

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
        if (!scenario->getButtonText().empty()) {
            auto btOnClick = scenario->getButtonCallback();
            auto buttons = Vector<Button *>({ SystemButton::defaultButtonWithText(
                scenario->getButtonText(), [btOnClick](Ref *) {
                    if (btOnClick)
                        btOnClick();
                })});
            auto node = SystemButton::getButtonGroupNode(buttons);
            addChild(node);
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