#ifndef _SH_PLOT_BUILDER_H_
#define _SH_PLOT_BUILDER_H_

#include "cocos2d.h"

namespace SailingHeroAPI {

// Build cocos2d scene graph from csv file
class SHPlotBuilder
{
public:
    static cocos2d::Scene * Build(std::wstring csvFile);
};

}

#endif
