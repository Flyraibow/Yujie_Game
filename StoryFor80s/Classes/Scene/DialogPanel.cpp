//
//  DialogPanel.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/24/19.
//

#include "DialogPanel.hpp"
#include "DialogData.hpp"
#include "DataManager.hpp"
#include "Utils.hpp"
#include "BaseColorNode.hpp"

BasePanel* DialogPanel::createPanel()
{
  return new DialogPanel();
}

DialogPanel::DialogPanel() : BasePanel("dialogPanel")
{
}

void DialogPanel::showDialogList(const vector<string> &dialogIds)
{
  p_dialogIds = dialogIds;
  p_currentIndex = 0;
  
  auto colorNode = getComponentById<BaseColorNode>("color_node");
  
  showNextDialog();
}

void DialogPanel::showNextDialog()
{
  if (p_currentIndex < p_dialogIds.size()) {
    showDialogById(p_dialogIds[p_currentIndex++]);
  } else {
    // TODO: complete
  }
}

void DialogPanel::showDialogById(const string &dialogId)
{
  auto dialogData = DialogData::getDialogDataById(dialogId);
  auto labName = getComponentById<Label>("lab_name");
  auto labDialog = getComponentById<Label>("lab_dialog");
  
  if (dialogData->getName().length() > 0) {
    labName->setString(DataManager::getShareInstance()->decipherString(dialogData->getName()));
  }
  labDialog->setString(dialogData->getContent());
}
