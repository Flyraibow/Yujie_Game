#ifndef _SH_UI_HERO_SELECTION_H_
#define _SH_UI_HERO_SELECTION_H_

#include <string>
#include <functional>

#include "cocos2d/cocos/2d/CCScene.h"

namespace SailingHeroAPI {
namespace ui {

struct HeroSelectionScene {
    std::function<void(int /* heroId */)> onSelected;
};

cocos2d::Scene * SHHeroSelectionSceneToCCScene(const HeroSelectionScene & shHeroSelection);

}
}

#endif
