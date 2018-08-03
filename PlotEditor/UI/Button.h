#ifndef _SH_UI_BUTTON_H_
#define _SH_UI_BUTTON_H_

#include <string>
#include <functional>

#include "cocos2d/cocos/ui/UIButton.h"

namespace SailingHeroAPI {
namespace ui {

struct Button {
    std::string templateName;
    struct {
        float x;
        float y;
    } centerPos;
    float scale;
    std::string text;
    std::function<void(cocos2d::ui::Button *)> onClick;
};

cocos2d::ui::Button * SHButtonToCCButton(const Button & shButton);

}
}

#endif
