#ifndef _SH_DIRECTOR_H_
#define _SH_DIRECTOR_H_

#include <memory>
#include <string>

#include "SHScenario.h"

namespace SailingHeroAPI {

class SHDirector {
public:
    static SHDirector * getInstance();

    SHScenario * getScenario(int id) {
        if (idToScenario.find(id) == idToScenario.end()) {
            idToScenario[id].reset(new SHScenario(id));
        }
        return idToScenario[id].get();
    }

    cocos2d::Scene * getStartCCScene() {
        for (auto & kv : idToScenario) {
            kv.second->setupCCScene();
        }
        return idToScenario.begin()->second->getCCScene();
    }

private:
    std::map<int, std::unique_ptr<SHScenario>> idToScenario;

    static SHDirector instance;
};

}

#endif
