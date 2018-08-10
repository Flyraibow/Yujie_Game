#include "SHPlotContext.h"

#include "StringParser.h"
#include "Classes/DataManager/GenerateData/SHDataManager.hpp"

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

bool SHPlotContext::evalCondition(std::string conditionName)
{
    // TODO
    return false;
}

std::string SHPlotContext::evalBuiltinFunction(const std::string & funcName,
                                               const std::vector<std::string> & arguments)
{
    // TODO
    assert(false);
    return "";
}

std::string SHPlotContext::evalGameDataQuery(const std::string & dataSetName,
                                             const std::string & id,
                                             const std::string & fieldName)
{
    // TODO: SHDataManager support lookup(dataSetName,id,fieldName)
    if (dataSetName == "HeroData" && fieldName == "firstName")
        return SHDataManager::getHeroDataById(id)->getHeroFirstName();
    else
        return "";
}

std::string SHPlotContext::evalCacheDataQuery(const std::string & key)
{
    return cache[key];
}

}
