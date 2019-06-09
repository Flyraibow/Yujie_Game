//
//  ShopPanel.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 6/3/19.
//

#ifndef ShopPanel_hpp
#define ShopPanel_hpp

#include "BasePanel.hpp"

class SpriteComponent;
class ItemData;

class ShopPanel : public BasePanel
{
private:
  ComponentDict p_itemSpriteComponents;
  vector<BaseComponent *> p_itemComponents;
  SpriteComponent* generateItemComponent(ItemData *itemData);
  void selectItem(Touch* touch, Event* event);
public:
  static BasePanel* createPanel();
  ShopPanel();
  void initialize();
  void referesh();
};

#endif /* ShopPanel_hpp */
