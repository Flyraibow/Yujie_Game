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


DialogElements::DialogElements(const nlohmann::json &jsonContent)
{
  p_name = Utils::getStringFromJson(jsonContent, "name");
  p_content = Utils::getStringFromJson(jsonContent, "content");
  p_parameters = Utils::getStringListFromJson(jsonContent, "parameters");
}

DialogElements::DialogElements(const string &name, const string &content, const vector<string> parameters)
{
  p_name = name;
  p_content = content;
  p_parameters = parameters;
}

string DialogElements::getName() const
{
  return p_name;
}

string DialogElements::getContent() const
{
  return p_content;
}

vector<string> DialogElements::getParameters() const
{
  return p_parameters;
}

DialogEventContent::DialogEventContent(const nlohmann::json &jsonContent) : StoryEventContent(jsonContent)
{
  p_name = Utils::getStringFromJson(jsonContent, "name", "dialogPanel");
  if (jsonContent.count("dialogs")) {
    auto dialogs = jsonContent.at("dialogs");
    for (int i = 0; i < dialogs.size(); ++i) {
      nlohmann::json dialogJson = dialogs.at(i);
      DialogElements *dialogElement = new DialogElements(dialogJson);
      p_dialogs.push_back(dialogElement);
    }
  }
}

DialogEventContent::~DialogEventContent()
{
  for (int i = 0; i < p_dialogs.size(); ++i) {
    delete p_dialogs[i];
  }
  p_dialogs.clear();
}

void DialogEventContent::runEvent(StoryEventCallback callback)
{
  auto dialogPanel = dynamic_cast<DialogPanel *>(PanelManager::getShareInstance()->getPanelById(p_name));
  auto baseScene = SceneManager::getShareInstance()->currentScene();
  baseScene->addPanelWithParameters(dialogPanel, true);
  dialogPanel->setCallback(callback);
  dialogPanel->showDialogList(p_dialogs);
}
