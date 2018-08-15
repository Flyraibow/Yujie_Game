#ifndef _SH_UI_INPUTBOX_H_
#define _SH_UI_INPUTBOX_H_

#include <string>

#include "cocos2d/cocos/2d/CCNode.h"

namespace SailingHeroAPI {
namespace ui {

struct InputBox {
    std::string hintLabel;
    std::string defaultText;
    std::function<void(const std::string & /*text*/)> onInput;
};

cocos2d::Node * SHInputBoxToCCInputBox(const InputBox & shInputBox);

}
}

#endif
