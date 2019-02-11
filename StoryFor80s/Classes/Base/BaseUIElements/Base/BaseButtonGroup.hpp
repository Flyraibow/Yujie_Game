//
//  BaseButtonGroup.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/10/19.
//

#ifndef BaseButtonGroup_hpp
#define BaseButtonGroup_hpp

#include <stdio.h>
#include "BaseColorNode.hpp"
#include "BaseButton.hpp"
#include <vector>

enum GroupButtonOption {
  GroupButtonOptionNone = 0,
  GroupButtonOptionWithCloseButton = 1,
  GroupButtonOptionItalic = 1 << 1,
  GroupButtonOptionAlignAll = 1 << 2,
  GroupButtonOptionSelectClose = 1 << 3,
};

/** @class BaseButtonGroup
 * @brief BaseButtonGroup is a subclass of BaseColorNode that provide a few selections on top of the layer
 */
class BaseButtonGroup : public BaseColorNode {
private:
  GroupButtonOption p_options;
  static BaseButtonGroup * create(const Color4B& color);
public:
  CREATE_FUNC(BaseButtonGroup);
  static BaseButtonGroup* create(const vector<BaseButton *> &buttons);
  static BaseButtonGroup* create(const vector<BaseButton *> &buttons, int option);
  static BaseButtonGroup* create(const vector<BaseButton *> &buttons, int option, const Color4B& color);
};

#endif /* BaseButtonGroup_hpp */
