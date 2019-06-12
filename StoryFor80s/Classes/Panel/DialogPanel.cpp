//
//  DialogPanel.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/24/19.
//

#include "DialogPanel.hpp"
#include "DataManager.hpp"
#include "Utils.hpp"
#include "BaseColorNode.hpp"
#include "BaseSpriteListener.hpp"
#include "FunctionManager.hpp"
#include "SceneManager.hpp"
#include "BaseLabel.hpp"

const static string kDialogContentScheduleKey = "dialog_content";

BasePanel* DialogPanel::createPanel()
{
  return new DialogPanel();
}

DialogPanel::DialogPanel() : BasePanel("dialogPanel")
{
}

void DialogPanel::setCallback(StoryEventCallback callback)
{
  p_callback = callback;
}

void DialogPanel::setListener()
{
  auto colorNode = getComponentById<BaseColorNode>("color_node");
  auto listener = BaseSpriteListener::createWithNode(colorNode);
  colorNode->overrideListener();
  listener->setTouchEnd(CC_CALLBACK_2(DialogPanel::clickDialogPanel, this), nullptr);
}

void DialogPanel::showDialogList(const vector<DialogElements *> &dialogs)
{
  setListener();
  p_dialogs = dialogs;
  p_currentIndex = 0;
  
  showNextDialog();
}

void DialogPanel::showNextDialog()
{
  if (p_currentIndex < p_dialogs.size()) {
    showDialog(p_dialogs[p_currentIndex++]);
  } else {
    SceneManager::getShareInstance()->popPanel();
    p_callback();
  }
}

void DialogPanel::showDialog(const DialogElements *dialog)
{
  auto labName = getComponentById<Label>("lab_name");
  auto labDialog = getComponentById<Label>("lab_dialog");
  
  labName->setString(DataManager::getShareInstance()->decipherString(dialog->getName()));
  p_content = DataManager::getShareInstance()->formatStringWithParamters(dialog->getContent(), dialog->getParameters());
  p_currentContentLength = 0;
  p_contentLength = Utils::utf8_strlen(p_content);

  labDialog->setString(p_content);
}

void DialogPanel::clickDialogPanel(Touch* touch, Event* event)
{
  auto labDialog = getComponentById<BaseLabel>("lab_dialog");
  if (labDialog->getString() != p_content) {
    labDialog->showTextImmediately();
  } else {
    showNextDialog();
  }
}
