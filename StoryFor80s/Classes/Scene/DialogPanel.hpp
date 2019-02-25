//
//  DialogPanel.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/24/19.
//

#ifndef DialogPanel_hpp
#define DialogPanel_hpp

#include "BasePanel.hpp"
#include <vector>

using namespace std;

class DialogPanel : public BasePanel
{
private:
  int p_currentIndex;
  vector<string> p_dialogIds;
  void showNextDialog();
  void showDialogById(const string &dialogId);
public:
  static BasePanel* createPanel();
  DialogPanel();
  
  void showDialogList(const vector<string> &dialogIds);
};

#endif /* DialogPanel_hpp */
