//
//  EditBoxComponent.hpp
//
//  Created by Yujie Liu on 9/26/18.
//

#ifndef EditBoxComponent_hpp
#define EditBoxComponent_hpp

#include "BaseComponent.hpp"
#include "ui/UIEditBox/UIEditBox.h"

class EditBoxComponent : public BaseComponent
{
private:
  std::string p_iconPath;
  ui::EditBox::InputMode p_mode;
  int p_length;
  std::string p_text;
  
protected:
public:
  EditBoxComponent(nlohmann::json componentJson);
  cocos2d::Node *addComponentToParent(ComponentDict &dict, cocos2d::Node *parent = nullptr);
};

#endif /* EditBoxComponent_hpp */
