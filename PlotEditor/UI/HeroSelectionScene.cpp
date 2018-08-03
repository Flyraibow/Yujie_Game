#include "HeroSelectionScene.h"

#include "Classes/UIElement/Sprite/SHScene.hpp"
#include "Classes/UIElement/Frame/HeroSelectingFrame.hpp"
#include "Classes/DataManager/GenerateData/HeroSelectData.hpp"

namespace {

class CCSceneWrapper : public SHScene {
public:
    bool init() override {
        if (!Scene::init())
        {
            return false;
        }
        setFullScreenCover();
        setBackgroundImage("res/default_background.png");

        cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
        auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

        auto heroList = HeroSelectData::getSharedDictionary();
        int index = 0;
        for (auto iter = heroList->begin(); iter != heroList->end(); ++iter, index++) {

            auto peoplePanel = HeroSelectingFrame::createWithSelectHeroId(to_string(iter->first));
            //setEventListenerForSprite(peoplePanel, iter->second);

            peoplePanel->setPosition(Vec2(origin.x + visibleSize.width / 2 - 100 + index * 200, origin.y + visibleSize.height / 2));
            addChild(peoplePanel);
        }

        //auto btnCancel = SystemButton::defaultButtonWithText(LocalizationHelper::getLocalization("sys_cancel"), [](cocos2d::Ref* pSender) {
        //    Director::getInstance()->popScene();
        //                                                     });
        //btnCancel->setAnchorPoint(Vec2(0.5, 0));
        //btnCancel->setNormalizedPosition(Vec2(0.5, 0.05));
        //s_window->addChild(btnCancel);

        return true;
    }

    CREATE_FUNC(CCSceneWrapper);
};

}

namespace SailingHeroAPI {
namespace ui {

cocos2d::Scene * SHHeroSelectionSceneToCCScene(const HeroSelectionScene & shHeroSelection) {
    return CCSceneWrapper::create();
}

} // namespace ui
} // namespace SailingHeroAPI
