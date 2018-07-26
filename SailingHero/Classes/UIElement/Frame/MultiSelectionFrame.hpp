//
//  MultiSelectionFrame.hpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 7/25/18.
//

#ifndef MultiSelectionFrame_hpp
#define MultiSelectionFrame_hpp

#include "cocos2d.h"
#include "ui/UIButton.h"
#include <vector>

USING_NS_CC;
using namespace std;


typedef std::function<void(vector<int> selectIndexes)> ccMultiSelectionCallback;

class MultiSelectionFrame
{
private:
  Node* p_background;
  ccMultiSelectionCallback p_callback;
  int p_totalNumber;
  vector<ui::Button *> p_buttonList;
  void clickCallback(cocos2d::Ref* pSender);
  MultiSelectionFrame(vector<string> selectList, int selectNumber, ccMultiSelectionCallback callback);
public:
  static Node* createMultiSelectFrame(vector<string> selectList, int selectNumber, ccMultiSelectionCallback callback);
};

#endif /* MultiSelectionFrame_hpp */
