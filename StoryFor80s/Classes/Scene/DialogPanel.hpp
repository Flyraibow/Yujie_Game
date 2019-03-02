//
//  DialogPanel.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/24/19.
//

#ifndef DialogPanel_hpp
#define DialogPanel_hpp

#include "BasePanel.hpp"
#include "StoryEventContent.hpp"
#include <vector>

using namespace std;

class DialogPanel : public BasePanel
{
private:
  int p_currentIndex;
  vector<string> p_dialogIds;
  StoryEventCallback p_callback;
  
  string p_content;
  int p_currentContentLength;
  int p_contentLength;
  
  void showNextDialog();
  void showDialogById(const string &dialogId);
  void clickDialogPanel(Touch* touch, Event* event);
public:
  static BasePanel* createPanel();
  DialogPanel();
  
  void showDialogList(const vector<string> &dialogIds, StoryEventCallback callback);
};

#endif /* DialogPanel_hpp */
