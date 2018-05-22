//
//  SystemButton.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 5/16/18.
//

#include "SystemButton.hpp"

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
