//
//  DialogFrame.hpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 7/21/18.
//

#ifndef DialogFrame_hpp
#define DialogFrame_hpp

#include "cocos2d.h"
#include <vector>
#include "DialogPhotoFrame.hpp"

USING_NS_CC;
using namespace std;

typedef std::function<void()> ccDialogCallback;

class DialogFrame
{
private:
  vector<string> p_dialogIds;
  Node* p_sprite;
  Sprite* p_dialogFrame;
  Label* p_dialogContent;
  Label* p_dialogName;
  DialogPhotoFrame p_dialogPhotoFrame;
  double p_scale;
  int p_index;
  ccDialogCallback p_callback;
  
  void clickDialogPanel(Touch* touch, Event* event);
  DialogFrame(const vector<string>&, ccDialogCallback dialogCallback, Size windowSize);
public:
  Node* getSprite() const;
  
  static DialogFrame* createWithDialogId(const string& dialogId, ccDialogCallback dialogCallback, Size windowSize = Director::getInstance()->getVisibleSize());
  static DialogFrame* createWithDialogIds(const vector<string> &dialogIdList, ccDialogCallback dialogCallback, Size windowSize = Director::getInstance()->getVisibleSize());
};

#endif /* DialogFrame_hpp */
