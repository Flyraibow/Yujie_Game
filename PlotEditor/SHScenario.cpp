#include "SHScenario.h"

#include "cocos2d/cocos/audio/include/SimpleAudioEngine.h"
#include "cocos2d/cocos/platform/CCPlatformMacros.h"

#include "Classes/UIElement/Sprite/SHScene.hpp"

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
        for (auto & bt : scenario->getAllButton()) {
            addChild(SailingHeroAPI::ui::SHButtonToCCButton(bt));
        }
        for (auto & dialog : scenario->getAllDialog()) {
            addChild(SailingHeroAPI::ui::SHDialogToCCDialog(dialog));
        }
        for (auto & inputBox : scenario->getAllInputBox()) {
            addChild(SailingHeroAPI::ui::SHInputBoxToCCInputBox(inputBox));
        }
        for (auto & multiSelectList : scenario->getAllMultiSelectList()) {
            addChild(SailingHeroAPI::ui::SHMultiSelectListToCCMultiSelectList(multiSelectList));
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

void SHScenario::setCCScene(cocos2d::Scene * scene)
{
    assert(ccScene == nullptr);
    ccScene = scene;
    ccScene->retain();
    ccSceneReady = true;
}

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