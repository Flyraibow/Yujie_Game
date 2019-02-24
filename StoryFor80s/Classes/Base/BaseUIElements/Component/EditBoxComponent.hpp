//
//  EditBoxComponent.hpp
//
//  Created by Yujie Liu on 9/26/18.
//

#ifndef EditBoxComponent_hpp
#define EditBoxComponent_hpp

#include "BaseComponent.hpp"
#include "ui/UIEditBox/UIEditBox.h"

class EditBoxComponent : public BaseComponent, cocos2d::ui::EditBoxDelegate
{
private:
  std::string p_iconPath;
  ui::EditBox::InputMode p_mode;
  int p_length;
  std::string p_text;
  std::string p_tempString;
protected:
public:
  EditBoxComponent(const nlohmann::json &componentJson);
  cocos2d::Node *addComponentToParent(ComponentDict &dict, cocos2d::Node *parent = nullptr);
  void editBoxTextChanged(ui::EditBox* editBox, const std::string& text);
  virtual void editBoxReturn(ui::EditBox* editBox);
};

#endif /* EditBoxComponent_hpp */
