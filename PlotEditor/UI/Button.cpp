#include "Button.h"

#include "cocos2d.h"

namespace SailingHeroAPI {
namespace ui {

cocos2d::ui::Button *SHButtonToCCButton(const Button &shButton) {
    auto image = "res/button_up.png";
    cocos2d::ui::Button *button = cocos2d::ui::Button::create(image);
    button->setScale9Enabled(true);
    button->setTitleAlignment(cocos2d::TextHAlignment::CENTER);
    button->setTitleText(shButton.text);
    auto lbl_size = button->getTitleRenderer()->getContentSize();
    button->setContentSize(
        cocos2d::Size(lbl_size.width + 20, lbl_size.height + 10));
    button->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
    button->setPositionType(cocos2d::ui::Widget::PositionType::PERCENT);
    button->setScale(shButton.scale);
    button->setPositionPercent(
        cocos2d::Vec2(shButton.centerPos.x, shButton.centerPos.y));
    auto onClick = shButton.onClick;
    button->addClickEventListener([onClick, button](cocos2d::Ref *) {
        if (onClick) onClick(button); });

    return button;
}

} // namespace ui
} // namespace SailingHeroAPI
