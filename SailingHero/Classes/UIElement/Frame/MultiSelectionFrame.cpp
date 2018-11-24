//
//  MultiSelectionFrame.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 7/25/18.
//

#include "MultiSelectionFrame.hpp"
#include "SystemButton.hpp"

void setButtonSelected(Button *button, bool selected)
{
  auto color = selected ? Color3B::BLACK : Color3B::WHITE;
  button->setTitleColor(color);
}

bool getButtonSelected(Button *button)
{
  return button->getTitleColor() == Color3B::BLACK;
}

MultiSelectionFrame::MultiSelectionFrame(vector<string> selectList, int selectNumber, ccMultiSelectionCallback callback)
{
  for (int i = 0; i < selectList.size(); ++i) {
    auto button = SystemButton::defaultButtonWithText(selectList[i]);
    p_buttonList.push_back(button);
  }
  p_background = SystemButton::getButtonGroupNode(p_buttonList, GroupButtonOptionWithCloseButton, Color4B(100, 0, 0, 100));
  p_callback = callback;
  p_totalNumber = selectNumber;
}

Node* MultiSelectionFrame::createMultiSelectFrame(vector<string> selectList, int selectNumber, ccMultiSelectionCallback callback)
{
  MultiSelectionFrame frame(selectList, selectNumber, callback);
  for (int i = 0; i < selectList.size(); ++i) {
    frame.p_buttonList[i]->addClickEventListener(CC_CALLBACK_1(MultiSelectionFrame::clickCallback, frame));
  }
  return frame.p_background;
}

void MultiSelectionFrame::clickCallback(cocos2d::Ref *pSender)
{
  Button* button = dynamic_cast<Button *>(pSender);
  bool selected = !getButtonSelected(button);
  setButtonSelected(button, selected);
  vector<int> selectedList;
  for (int i = 0; i < p_buttonList.size(); ++i) {
    if (getButtonSelected(p_buttonList[i])) {
      selectedList.push_back(i);
    }
  }
  if (selectedList.size() == p_totalNumber) {
    this->p_background->removeFromParent();
    p_callback(selectedList);
  }
}
