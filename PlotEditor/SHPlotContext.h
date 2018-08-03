#ifndef _SH_PLOT_CONTEXT_H_
#define _SH_PLOT_CONTEXT_H_

#include <string>
#include <map>

namespace SailingHeroAPI {

class SHPlotContext {
public:
    static SHPlotContext * getInstance();

    void cacheSet(std::string key, std::string value);

    std::string cacheGet(std::string key);

    std::string executeQuery(std::string query);

private:
    static SHPlotContext instance;

    std::map<std::string, std::string> cache;
};

}

#endif