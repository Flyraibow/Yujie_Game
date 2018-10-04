//
//  SHInputPanel.cpp
//  SailingHero
//
//  Created by Yujie Liu on 9/27/18.
//

#include "SHInputPanel.hpp"
#include "DataManager.hpp"

#include "ui/UIEditBox/UIEditBox.h"

SHPanel* SHInputPanel::createPanel()
{
  return new SHInputPanel();
}

SHInputPanel::SHInputPanel() : SHPanel("input")
{  
}

void SHInputPanel::process()
{
  auto editBox = getComponentById<ui::EditBox>("edit_box");
  DataManager::getShareInstance()->setTempString("input", editBox->getText());
}
