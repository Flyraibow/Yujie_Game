#ifndef _SH_UI_DIALOG_H_
#define _SH_UI_DIALOG_H_

#include <string>

#include "cocos2d/cocos/2d/CCLayer.h"

namespace SailingHeroAPI {
namespace ui {

struct Dialog {
    std::string templateName;
    bool showFullName;
    bool showImage;
    int heroId;
    std::string text;
};

cocos2d::LayerColor * SHDialogToCCDialog(const Dialog & shDialog);

}
}

#endif
