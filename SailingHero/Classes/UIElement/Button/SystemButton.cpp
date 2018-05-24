//
//  SystemButton.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 5/16/18.
//

#include "SystemButton.hpp"
#include <algorithm>

USING_NS_CC;
using namespace ui;

Button* SystemButton::defaultButtonWithText(std::string text)
{
    auto image = "Graph/System/button_up.png";
    auto button = Button::create(image);
    button->setScale9Enabled(true);
    button->setTitleAlignment(TextHAlignment::CENTER);
    button->setTitleText(text);
    auto lbl_size = button->getTitleRenderer()->getContentSize();
    button->setContentSize(
                           Size(
                                lbl_size.width + 23,
                                lbl_size.height + 10
                                )
                           );
    return button;
}


Button* SystemButton::defaultButtonWithText(std::string text, const Widget::ccWidgetClickCallback &callback)
{
    auto button = SystemButton::defaultButtonWithText(text);
    button->addClickEventListener(callback);
    return button;
}

SHColorNode* SystemButton::getButtonGroupNode(Vector<Button *> buttons, bool italic)
{
    auto node = SHColorNode::createInvisibleNode();
    if (!buttons.empty()) {
        static auto miniDistance = 0.09;
        static auto h_dist = - 0.02;
        auto distance = buttons.size() > 1 ? MIN(miniDistance, 1.0 / (buttons.size() - 1)) : 0;
        for (int i = 0; i < buttons.size(); ++i) {
            auto button = buttons.at(i);
            button->setAnchorPoint(Vec2(0.5, 0.5));
            button->setPositionType(Widget::PositionType::PERCENT);
            auto diff = ((buttons.size() - 1) / 2.0 - i);
            double offset_y = diff * distance;
            double offset_x = italic ? diff * h_dist : 0;
            button->setPositionPercent(Vec2(0.5 + offset_x, offset_y + 0.5));
            node->addChild(button);
        }
    }
    return node;
}

SHColorNode* SystemButton::getButtonGroupNode(Vector<Button *> buttons)
{
    return SystemButton::getButtonGroupNode(buttons, true);
}
