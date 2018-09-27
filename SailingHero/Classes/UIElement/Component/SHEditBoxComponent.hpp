//
//  SHEditBoxComponent.hpp
//  SailingHero
//
//  Created by Yujie Liu on 9/26/18.
//

#ifndef SHEditBoxComponent_hpp
#define SHEditBoxComponent_hpp

#include "SHComponent.hpp"
#include "ui/UIEditBox/UIEditBox.h"

class SHEditBoxComponent : public SHComponent
{
private:
  std::string p_iconPath;
  ui::EditBox::InputMode p_mode;
  int p_length;
  std::string p_text;
  
protected:
public:
  SHEditBoxComponent(nlohmann::json componentJson);
  cocos2d::Node *addComponentToParent(unordered_map<string, Node *> &dict, cocos2d::Node *parent = nullptr) const;
};

#endif /* SHEditBoxComponent_hpp */
