#include "HeroSelectionScene.h"

#include "Classes/UIElement/Sprite/SHScene.hpp"
#include "Classes/UIElement/Frame/HeroSelectingFrame.hpp"
#include "Classes/UIElement/Sprite/SHSpriteListener.hpp"
#include "Classes/DataManager/GenerateData/HeroSelectData.hpp"
#include "../SHPlotContext.h"
#include "../SHDirector.h"

namespace {

using ::SailingHeroAPI::SHDirector;
using ::SailingHeroAPI::SHPlotContext;

class CCSceneWrapper : public SHScene {
public:
    bool init(std::function<void(int /*heroId*/)> onHeroSelected) {
        if (!Scene::init()) {
            return false;
        }
        setFullScreenCover();
        setBackgroundImage("res/default_background.png");

        cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();
        auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

        int index = 0;
        for (auto & heroId_heroData : *HeroSelectData::getSharedDictionary()) {
            int heroId = heroId_heroData.first;
            std::string heroIdStr = ::std::to_string(heroId);
            cocos2d::Sprite * heroPanel = HeroSelectingFrame::createWithSelectHeroId(heroIdStr);
            heroPanel->setPosition(Vec2(origin.x + visibleSize.width / 2 - 100 + index * 200, origin.y + visibleSize.height / 2));

            // listener register to heroPanel's event dispatcher
            auto listener = SHSpriteListener::createWithNode(heroPanel);
            listener->setTouchEnd(
                [heroId, heroIdStr, onHeroSelected](Touch*, Event*) {
                    SHPlotContext::getInstance()->cacheSet("heroId", heroIdStr);
                    if (onHeroSelected)
                        onHeroSelected(heroId); },
                nullptr);

            addChild(heroPanel);
            ++index;
        }

        //auto btnCancel = SystemButton::defaultButtonWithText(LocalizationHelper::getLocalization("sys_cancel"), [](cocos2d::Ref* pSender) {
        //    Director::getInstance()->popScene(); });
        //btnCancel->setAnchorPoint(Vec2(0.5, 0));
        //btnCancel->setNormalizedPosition(Vec2(0.5, 0.05));
        //s_window->addChild(btnCancel);

        return true;
    }

    static CCSceneWrapper* create(std::function<void(int /*heroId*/ )> callback) {
        CCSceneWrapper *pRet = new(std::nothrow) CCSceneWrapper();
        if (pRet && pRet->init(std::move(callback))) {
            pRet->autorelease();
            return pRet;
        } else {
            delete pRet;
            pRet = nullptr;
            return nullptr;
        }
    }
};

}

namespace SailingHeroAPI {
namespace ui {

cocos2d::Scene * SHHeroSelectionSceneToCCScene(const HeroSelectionScene & shHeroSelection) {    
    return CCSceneWrapper::create(shHeroSelection.onSelected);
}

} // namespace ui
} // namespace SailingHeroAPI
