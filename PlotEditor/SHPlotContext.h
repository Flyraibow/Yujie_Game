#ifndef _SH_PLOT_CONTEXT_H_
#define _SH_PLOT_CONTEXT_H_

#include <string>
#include <vector>
#include <map>

namespace SailingHeroAPI {

class SHPlotContext {
public:
    static SHPlotContext * getInstance();

    void cacheSet(std::string key, std::string value);

    std::string cacheGet(std::string key);

    bool evalCondition(std::string conditionName);

    std::string evalBuiltinFunction(
        const std::string & funcName,
        const std::vector<std::string> & arguments);

    std::string evalGameDataQuery(const std::string & dataSetName,
                                  const std::string & id,
                                  const std::string & fieldName);

    std::string evalCacheDataQuery(const std::string & key);

private:

    static SHPlotContext instance;

    std::map<std::string, std::string> cache;
};

}

#endif