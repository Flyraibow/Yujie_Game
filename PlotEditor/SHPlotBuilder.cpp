#include "SHPlotBuilder.h"

#include "CSVReader.h"
#include "SHDirector.h"
#include "SHDataManager.h"
#include "StringParser.h"
#include "UI/Button.h"
#include "UI/Dialog.h"
#include "UI/MultiSelectList.h"
#include "UI/HeroSelectionScene.h"

namespace SailingHeroAPI {

cocos2d::Scene * SHPlotBuilder::Build(std::wstring csvFile)
{
    SHDataManager * dataManager = SHDataManager::getInstance();
    SHDirector * director = SHDirector::getInstance();

    dataManager->loadData(cocos2d::FileUtils::getInstance()->getWritablePath() + "/res/base/data");

    SHScenario * currentScenario = nullptr;
    CSVReader csvReader(csvFile);
    for (auto & lineItems : csvReader) {
        // Skip empty line
        if (lineItems.empty())
            continue;

        // New scene begin
        int id;
        if (ParseIntW(lineItems[0], &id)) {
            currentScenario = director->getScenario(id);
            continue;
        }

        assert(currentScenario);
        if (lineItems[0] == L"bgp") {
            currentScenario->setBackgroundImage(WStringToString(lineItems[1]));
            continue;
        }

        if (lineItems[0] == L"bgm") {
            currentScenario->setBackgroundMusic(WStringToString(lineItems[1]));
            continue;
        }

        // button
        if (lineItems.size() == 4
            && lineItems[0] == L"ui"
            && lineItems[1] == L"button") {
            int gotoId;
            if (!ParseIntW(lineItems[3], &gotoId)) {
                continue;
            }
            ui::Button button;
            button.templateName = "";
            button.centerPos = {0.5f, 0.6f};
            button.scale = 5.0f;
            button.text = WStringToString(lineItems[2]);
            button.onClick = [gotoId](cocos2d::ui::Button *) {
                cocos2d::Director::getInstance()->replaceScene(
                    SHDirector::getInstance()->getScenario(gotoId)->getCCScene()); };
            currentScenario->addButton(button);
            continue;
        }

        // dialog
        if (lineItems.size() ==  4
            && lineItems[0] == L"ui"
            && lineItems[1] == L"dialog") {
            DialogData *dialogData =
                dataManager->getDialogData(WStringToString(lineItems[2]));
            ui::Dialog dialog;
            dialog.templateName = dialogData->getDialogId();
            dialog.showFullName = dialogData->getShowFullNames();
            dialog.showImage = dialogData->getShowImage();
            dialog.heroId = ToInt(dialogData->getHeroIdId());
            dialog.text = dialogData->getDialogContent() + " I'm @HeroName !!!";
            currentScenario->addDialog(dialog);
            continue;
        }

        // multi select list
        if (lineItems.size() == 4
            && lineItems[0] == L"ui"
            && lineItems[1] == L"select") {
            ui::MultiSelectList select;
            for (std::wstring & text : SplitString(lineItems[2], L';')) {
                select.textList.emplace_back(WStringToString(text));
            }
            select.onSelectChange = [](std::vector<int> selected) {
                CCLOG("%d selected.", selected.size());
            };
            currentScenario->addMultiSelectList(select);
            continue;
        }

        // hero select
        // TODO: handle scene dependency
        if (lineItems.size() == 4
            && lineItems[0] == L"scene"
            && lineItems[1] == L"HeroSelection") {
            ui::HeroSelectionScene heroSelection;
            currentScenario->setCCScene(ui::SHHeroSelectionSceneToCCScene(heroSelection));
            continue;
        }
    }

    return director->getStartCCScene();
}

}
