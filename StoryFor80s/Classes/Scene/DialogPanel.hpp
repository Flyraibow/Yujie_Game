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
#include "DialogEventContent.hpp"
#include <vector>

using namespace std;

class DialogPanel : public BasePanel
{
private:
  int p_currentIndex;
  vector<DialogElements *> p_dialogs;
  StoryEventCallback p_callback;
  
  string p_content;
  int p_currentContentLength;
  int p_contentLength;
  
  void setListener();
  void showNextDialog();
  void showDialog(const DialogElements *dialog);
  void clickDialogPanel(Touch* touch, Event* event);
public:
  static BasePanel* createPanel();
  DialogPanel();
  
  void setCallback(StoryEventCallback callback);
  void showDialogList(const vector<DialogElements *> &dialogs);
};

#endif /* DialogPanel_hpp */
