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
#include "BaseSpriteListener.hpp"
#include "FunctionManager.hpp"
#include "SceneManager.hpp"

const static string kDialogContentScheduleKey = "dialog_content";

BasePanel* DialogPanel::createPanel()
{
  return new DialogPanel();
}

DialogPanel::DialogPanel() : BasePanel("dialogPanel")
{
}

void DialogPanel::showDialogList(const vector<string> &dialogIds, StoryEventCallback callback)
{
  p_dialogIds = dialogIds;
  p_callback = callback;
  p_currentIndex = 0;
  
  auto colorNode = getComponentById<BaseColorNode>("color_node");
  auto listener = BaseSpriteListener::createWithNode(colorNode);
  colorNode->overrideListener();
  listener->setTouchEnd(CC_CALLBACK_2(DialogPanel::clickDialogPanel, this), nullptr);
  
  showNextDialog();
}

void DialogPanel::showNextDialog()
{
  if (p_currentIndex < p_dialogIds.size()) {
    showDialogById(p_dialogIds[p_currentIndex++]);
  } else {
    SceneManager::getShareInstance()->popPanel();
    p_callback();
  }
}

void DialogPanel::showDialogById(const string &dialogId)
{
  auto dialogData = DialogData::getDialogDataById(dialogId);
  auto labName = getComponentById<Label>("lab_name");
  auto labDialog = getComponentById<Label>("lab_dialog");
  
  if (dialogData->getName().length() > 0) {
    labName->setString(DataManager::getShareInstance()->decipherString(dialogData->getName()));
  } else if (dialogData->getFriendData() != nullptr) {
    labName->setString(Manager::getFunctionValueById("friend_name", dialogData->getFriendData()));
  }
  p_content = DataManager::getShareInstance()->formatStringWithParamters(dialogData->getContent(), dialogData->getParameters());
  p_currentContentLength = 0;
  p_contentLength = Utils::utf8_strlen(p_content);

  labDialog->setString("");
  labDialog->schedule([this, labDialog](float delta) {
    if (p_currentContentLength++ < p_contentLength) {
      auto str = Utils::utf8_substr(p_content, 0, p_currentContentLength);
      labDialog->setString(str);
    } else {
      labDialog->setString(p_content);
      labDialog->unschedule(kDialogContentScheduleKey);
    }
  }, 0.2f, kDialogContentScheduleKey);
}

void DialogPanel::clickDialogPanel(Touch* touch, Event* event)
{
  auto labDialog = getComponentById<Label>("lab_dialog");
  if (p_currentContentLength + 1 < p_contentLength) {
    labDialog->setString(p_content);
    p_currentContentLength = p_contentLength;
    labDialog->unschedule(kDialogContentScheduleKey);
  } else {
    showNextDialog();
  }
}
