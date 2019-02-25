//
//  DialogEventContent.cpp
//  StoryFor80s
//
//  Created by Yujie Liu on 2/24/19.
//

#include "DialogEventContent.hpp"
#include "JsonUtil.hpp"
#include "BaseScene.hpp"
#include "SceneManager.hpp"
#include "PanelManager.hpp"
#include "DialogPanel.hpp"

DialogEventContent::DialogEventContent(const nlohmann::json &jsonContent) : StoryEventContent(jsonContent)
{
  p_name = Utils::getStringFromJson(jsonContent, "name", "dialogPanel");
  p_dialogIds = Utils::getStringListFromJson(jsonContent, "dialogIds");
}

void DialogEventContent::runEvent(BaseScene *baseScene, StoryEventCallback callback)
{
  auto dialogPanel = dynamic_cast<DialogPanel *>(PanelManager::getShareInstance()->getPanelById(p_name));
  baseScene->addPanelWithParameters(dialogPanel, true);
  dialogPanel->showDialogList(p_dialogIds);
//  callback();
}
