//
//  ShopPanel.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 6/3/19.
//

#include "ShopPanel.hpp"
#include "ItemData.hpp"
#include "ConditionManager.hpp"
#include "SpriteComponent.hpp"
#include "LabelComponent.hpp"
#include "ui/UIScrollView.h"
#include "BaseSpriteListener.hpp"
#include "DataManager.hpp"
#include "StoryManager.hpp"

BasePanel* ShopPanel::createPanel()
{
  return new ShopPanel();
}

ShopPanel::ShopPanel() : BasePanel("shopPanel")
{
}

void ShopPanel::initialize()
{
  referesh();
}

void ShopPanel::referesh()
{
  for (int i = (int)p_itemComponents.size() - 1; i >= 0; --i) {
    delete p_itemComponents[i];
  }
  p_itemComponents.clear();
  p_itemSpriteComponents.clear();
  
  auto scrollView = getComponentById<ui::ScrollView>("scrollView");
  int index = 0;
  auto allItemMaps = *ItemData::getSharedDictionary();
  auto height = scrollView->getContentSize().height;
  for (auto itemPair : allItemMaps) {
    if (!Manager::checkConditionByString(itemPair.second->getCondition())) {
      continue;
    }
    auto component = generateItemComponent(itemPair.second);
    auto sprite = component->getNode();
    if (itemPair.second->getHaveIt()) {
      sprite->setVisible(false);
    } else {
      auto listener = BaseSpriteListener::createWithNode(sprite, false);
      listener->setTouchClicked(CC_CALLBACK_2(ShopPanel::selectItem, this), nullptr);
    }
    int row = index % 3;
    int col = index / 3;
    sprite->setPosition(col * 180, height - row * 180);
    scrollView->addChild(sprite);
    component->refresh();
    index++;
    p_itemComponents.push_back(component);
  }
}

SpriteComponent* ShopPanel::generateItemComponent(ItemData *itemData)
{
  auto component = dynamic_cast<SpriteComponent *>(BaseComponent::getComponentFromJsonFile("shopItemSprite"));
  component->setId(itemData->getId());
  component->addComponentToParent(p_itemSpriteComponents);
  component->setAssociateData(itemData);
  return component;
}

void ShopPanel::selectItem(Touch* touch, Event* event)
{
  auto scrollView = getComponentById<ui::ScrollView>("scrollView");
  if (!BaseSpriteListener::isTouchInsideNode(touch, scrollView)) {
    CCLOG("touch is out side the view, it doesn't count");
    return;
  }
  auto sprite = event->getCurrentTarget();
  auto item = ItemData::getItemDataById(sprite->getName());
  if (item != nullptr) {
    DataManager::getShareInstance()->setTempData("buyItem", item);
    StoryManager::getShareInstance()->startStory("panelAction/buyItem");
  } else {
    CCLOGERROR("couldn't find item to buy : %s", sprite->getName().c_str());
  }
}
