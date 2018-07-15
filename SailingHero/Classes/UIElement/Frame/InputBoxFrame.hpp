//
//  InputBoxFrame.hpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 7/14/18.
//

#ifndef InputBoxFrame_hpp
#define InputBoxFrame_hpp

#include "cocos2d.h"
#include "ui/UIEditBox/UIEditBox.h"

USING_NS_CC;
using namespace std;

typedef function<void(const string &result, bool canceled, Node* pSender)> ccInputCallback;

/** @class SHColorNode
 * @brief SHColorNode is a subclass of LayerColor that can swallow all touches
 
 */
class InputBoxFrame
{
public:
  static Node* createWithHint(const string &message,
                              const string &defaultValue,
                              ccInputCallback inputCallback,
                              int maxLength = 8,
                              ui::EditBox::InputMode mode = ui::EditBox::InputMode::ANY);
};

#endif /* InputBoxFrame_hpp */
