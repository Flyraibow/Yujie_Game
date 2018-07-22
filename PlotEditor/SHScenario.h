#ifndef _SCENARIO_H_
#define _SCENARIO_H_

#include <vector>

#include "cocos2d.h"

namespace SailingHeroAPI {

class SHScenario {
public:
    void setBackgroundImage(std::string imgPath) {
        bgImage = imgPath;
    }
    const std::string & getBackgroundImage() const {
        return bgImage;
    }
    void setBackgroundMusic(std::string path) {
        bgMusic = path;
    }
    const std::string & getBackgroundMusic() const {
        return bgMusic;
    }
    void addButton(std::string text, std::function<void()> onClick) {
        btText = text;
        btOnClick = onClick;
    }
    const std::string & getButtonText() const {
        return btText;
    }
    std::function<void()> getButtonCallback() const {
        return btOnClick;
    }
    cocos2d::Scene * getCCScene();
private:
    friend class SHDirector;
    SHScenario(int scenarioId)
        : id(scenarioId), ccScene(nullptr), ccSceneReady(false) {}
    void setupCCScene();

    int id;
    std::string bgImage;
    std::string bgMusic;
    std::string btText;
    std::function<void()> btOnClick;
    cocos2d::Scene * ccScene;
    bool ccSceneReady;
};

}

#endif
