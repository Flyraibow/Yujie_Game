#ifndef _SH_SCENARIO_H_
#define _SH_SCENARIO_H_

#include <vector>

#include "cocos2d.h"

namespace SailingHeroAPI {

namespace ui {

struct Button {
    std::string templateName;
    struct {
        float x;
        float y;
    } centerPos;
    std::string text;
    std::function<void()> onClick;
};

struct Dialog {
    std::string templateName;
    std::string text;
};

}

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
    void addButton(const ui::Button & bt) {
        buttons.push_back(bt);
    }
    const std::vector<ui::Button> & getAllButton() const {
        return buttons;
    }
    void addDialog(const ui::Dialog & dialog) {
        dialogs.push_back(dialog);
    }
    const std::vector<ui::Dialog> & getAllDialog() const {
        return dialogs;
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
    std::vector<ui::Button> buttons;
    std::vector<ui::Dialog> dialogs;
    cocos2d::Scene * ccScene;
    bool ccSceneReady;
};

}

#endif
