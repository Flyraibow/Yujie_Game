#ifndef _SH_UI_MULTI_SELECT_LIST_H_
#define _SH_UI_MULTI_SELECT_LIST_H_

#include <functional>
#include <vector>
#include <string>

#include "cocos2d/cocos/2d/CCNode.h"

namespace SailingHeroAPI {
namespace ui {

struct MultiSelectList {
    std::vector<std::string> textList;
    std::function<void(std::vector<int>)> onSelectChange;
};

cocos2d::Node * SHMultiSelectListToCCMultiSelectList(const MultiSelectList & multiSelectList);

}
}

#endif
