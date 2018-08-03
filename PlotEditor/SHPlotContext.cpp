#include "SHPlotContext.h"

#include "StringParser.h"
#include "SHDataManager.h"

namespace SailingHeroAPI {

SHPlotContext SHPlotContext::instance;

SHPlotContext * SHPlotContext::getInstance()
{
    return &instance;
}

void SHPlotContext::cacheSet(std::string key, std::string value)
{
    cache[key] = value;
}

std::string SHPlotContext::cacheGet(std::string key)
{
    return cache[key];
}

std::string SHPlotContext::executeQuery(std::string query)
{
    std::string result;

    if (query == "HeroName") {
        std::string heroIdStr = cacheGet("heroId");
        int heroId = ToInt(heroIdStr);
        if (!heroIdStr.empty()) {
            HeroData *heroData =
                SHDataManager::getInstance()->getHeroData(heroId);
            if (heroData) {
                result += heroData->getHeroFirstName();
                result += ' ';
                result += heroData->getHeroLastName();
            }
        }
    }

    return result;
}

}
