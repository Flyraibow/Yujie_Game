#include "MultiSelectList.h"

#include "Button.h"
#include "cocos2d/cocos/2d/CCLayer.h"

namespace {

class MultiSelectListNode : public cocos2d::Layer {
public:
    CREATE_FUNC(MultiSelectListNode);

    void setSelectionCount(size_t max) {
        selected.resize(max, false);
    }

    void toggleSelect(size_t i) {
        if (i < selected.size())
            selected[i] = !selected[i];
    }

    bool isSelected(size_t i) const {
        return (i < selected.size() ? selected[i] : false);
    }

    std::vector<int> getSelected() const {
        std::vector<int> indexes;
        for (size_t i = 0; i < selected.size(); ++i) {
            if (selected[i])
                indexes.push_back(i);
        }
        return indexes;
    }

private:
    std::vector<bool> selected;
};

}

namespace SailingHeroAPI {
namespace ui {

cocos2d::Node * SHMultiSelectListToCCMultiSelectList(const MultiSelectList & multiSelectList)
{
    size_t selectionCount = multiSelectList.textList.size();
    auto onSelectChange = multiSelectList.onSelectChange;

    MultiSelectListNode * node = MultiSelectListNode::create();
    node->setSelectionCount(selectionCount);

    Button shButton;
    shButton.centerPos.x = 0.5f;
    shButton.scale = 3.0f;
    for (size_t i = 0; i < selectionCount; ++i) {
        shButton.centerPos.y = 0.2 + 0.6 * i / (selectionCount - 1);
        shButton.text = multiSelectList.textList[i];
        shButton.onClick = [node, onSelectChange, i](cocos2d::ui::Button * self) {
            node->toggleSelect(i);
            (node->isSelected(i)
             ? self->setTitleColor(cocos2d::Color3B::BLACK)
             : self->setTitleColor(cocos2d::Color3B::WHITE));
            onSelectChange(node->getSelected());
        };
        node->addChild(SHButtonToCCButton(shButton));
    }

    return node;
}

}
}
