//
//  BaseDropDownMenu.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 6/8/19.
//

#include "BaseDropDownMenu.hpp"
#include "BaseSpriteListener.hpp"

BaseDropDownMenu * BaseDropDownMenu::create(const Color4B& color)
{
  BaseDropDownMenu * layer = new (std::nothrow) BaseDropDownMenu();
  if(layer && layer->initWithColor(color))
  {
    layer->autorelease();
    return layer;
  }
  CC_SAFE_DELETE(layer);
  return nullptr;
}

void BaseDropDownMenu::setSelections(const vector<string> &selections)
{
  p_selections = selections;
  p_selectedIndex = -1;
}

void BaseDropDownMenu::setSelectedIndex(int index)
{
  if (index >= 0 &&index < p_selections.size()) {
    p_selectedIndex = index;
  }
  p_selectedIndex = -1;
}

void BaseDropDownMenu::setDropDownMenuItem(const Size &spriteSize, const Color4B& spriteColor, const Color4B& selectedColor)
{
  p_spriteSize = spriteSize;
  p_spriteColor = spriteColor;
  p_selectedColor = selectedColor;
}

void BaseDropDownMenu::setDropDownLabel(const Label* exampleLabel)
{
  p_exampleLabel = exampleLabel;
}

void BaseDropDownMenu::render()
{
  if (p_scrollView != nullptr) {
    p_scrollView->removeFromParent();
  }
  p_scrollView = ui::ScrollView::create();
  auto height = p_selections.size() * p_spriteSize.height;
  int index = 0;
  for (auto selection : p_selections) {
    Label* label = nullptr;
    if (p_exampleLabel == nullptr) {
      label = Label::createWithSystemFont(selection, "Helvetica", 15);
      label->setNormalizedPosition(Vec2(0.5, 0.5));
      label->setAnchorPoint(Vec2(0.5, 0.5));
    } else {
      label = Label::createWithSystemFont(selection, p_exampleLabel->getSystemFontName(), p_exampleLabel->getSystemFontSize());
      label->setNormalizedPosition(p_exampleLabel->getNormalizedPosition());
      label->setAnchorPoint(p_exampleLabel->getAnchorPoint());
    }
    auto sprite = Sprite::create();
    sprite->setContentSize(p_spriteSize);
    sprite->setAnchorPoint(Vec2(0, 1));
    sprite->setPosition(0, height - index * p_spriteSize.height);
    LayerColor* colorLayer;
    if (index == p_selectedIndex) {
      colorLayer = LayerColor::create(p_selectedColor, p_spriteSize.width, p_spriteSize.height);
    } else {
      colorLayer = LayerColor::create(p_spriteColor, p_spriteSize.width, p_spriteSize.height);
    }
    sprite->addChild(colorLayer);
    sprite->addChild(label);
    sprite->setTag(index);
    p_scrollView->addChild(sprite);
    auto listener = BaseSpriteListener::createWithNode(sprite, false);
    listener->setTouchClicked(CC_CALLBACK_2(BaseDropDownMenu::selectItem, this), nullptr);
    index++;
  }
  p_scrollView->setInnerContainerSize(Size(p_spriteSize.width, height));
  if (height >= p_maxHeight) {
    p_scrollView->setContentSize(Size(p_spriteSize.width, p_maxHeight));
  } else {
    p_scrollView->setContentSize(Size(p_spriteSize.width, height));
  }
  p_scrollView->setBackGroundColorType(ui::Layout::BackGroundColorType::SOLID);
  p_scrollView->setBackGroundColor(Color3B(200,0,0));
  p_scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
  p_scrollView->setAnchorPoint(Vec2(0.5, 0.5));
  p_scrollView->setNormalizedPosition(Vec2(0.5, 0.5));
  this->addChild(p_scrollView);
  auto bglistener = BaseSpriteListener::createWithNode(this, true);
  this->overrideListener();
  bglistener->setTouchEnd(CC_CALLBACK_2(BaseDropDownMenu::cancel, this), nullptr);
}

void BaseDropDownMenu::selectItem(Touch* touch, Event* event)
{
  if (!BaseSpriteListener::isTouchInsideNode(touch, p_scrollView)) {
    CCLOG("touch is out side the view, it doesn't count");
    cancel(touch, event);
    return;
  }
  auto sprite = event->getCurrentTarget();
  if (p_callback != nullptr) {
    p_callback(sprite->getTag());
    this->removeFromParent();
  }
}

void BaseDropDownMenu::cancel(Touch* touch, Event* event)
{
  if (p_callback != nullptr) {
    p_callback(-1);
    this->removeFromParent();
  }
}

BaseDropDownMenu* BaseDropDownMenu::create(BaseDropDownMenuCallback callback)
{
  auto node = BaseDropDownMenu::create(Color4B(40, 40, 40,20));
  node->p_callback = callback;
  return node;
}
