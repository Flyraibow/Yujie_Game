#include "SHPlotBuilder.h"

#include "CSVReader.h"
#include "SHDirector.h"

#include "SailingHerorMenu.hpp"

namespace SailingHeroAPI {

bool ParseInt(const std::wstring & str, int * out)
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
    //return SailingHeroMenu::createScene();

    SHDirector * director = SHDirector::getInstance();

    SHScenario * currentScenario = nullptr;
    CSVReader csvReader(csvFile);
    for (auto & lineItems : csvReader) {
        // Skip empty line
        if (lineItems.empty())
            continue;

        // New scene begin
        int id;
        if (ParseInt(lineItems[0], &id)) {
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
            if (!ParseInt(lineItems[3], &gotoId)) {
                continue;
            }
            cocos2d::Scene * gotoScene = director->getScenario(gotoId)->getCCScene();
            currentScenario->addButton(WStringToString(lineItems[2]),
                [gotoScene]() {
                    cocos2d::Director::getInstance()->replaceScene(gotoScene);
                });
        }
    }

    return director->getStartCCScene();
}

}
