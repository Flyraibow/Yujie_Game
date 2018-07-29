#include "SHPlotBuilder.h"

#include "CSVReader.h"
#include "SHDirector.h"
#include "SHDataManager.h"

namespace SailingHeroAPI {

int ToInt(const std::string & str)
{
    if (str.empty())
        return 0;

    int i = 0;
    for (char c : str) {
        i *= 10;
        if (c >= '0' && c <= '9')
            i += (int)(c - '0');
        else
            return 0;
    }
    return i;
}

bool ParseIntW(const std::wstring & str, int * out)
{
    if (str.empty())
        return false;

    int i = 0;
    for (wchar_t c : str) {
        i *= 10;
        if (c >= '0' && c <= '9')
            i += (int)(c - '0');
        else
            return false;
    }
    *out = i;
    return true;
}

std::string WStringToString(const std::wstring & wstr)
{
    std::string str;
    str.reserve(wstr.size());
    for (wchar_t c : wstr) {
        str.push_back((char)c);
    }
    return str;
}

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
            cocos2d::Scene * gotoScene = director->getScenario(gotoId)->getCCScene();
            ui::Button button;
            button.templateName = "";
            button.centerPos = {0.5f, 0.6f};
            button.text = WStringToString(lineItems[2]);
            button.onClick = [gotoScene]() {
                cocos2d::Director::getInstance()->replaceScene(gotoScene); };
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
            dialog.text = dialogData->getDialogContent();
            currentScenario->addDialog(dialog);
        }
    }

    return director->getStartCCScene();
}

}
