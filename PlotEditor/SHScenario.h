#ifndef _SH_SCENARIO_H_
#define _SH_SCENARIO_H_

#include <vector>

#include "cocos2d.h"
#include "UI/Button.h"
#include "UI/Dialog.h"
#include "UI/MultiSelectList.h"

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
    void addMultiSelectList(const ui::MultiSelectList & multiSelectList) {
        multiSelectLists.push_back(multiSelectList);
    }
    const std::vector<ui::MultiSelectList> & getAllMultiSelectList() const {
        return multiSelectLists;
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
    std::vector<ui::MultiSelectList> multiSelectLists;
    cocos2d::Scene * ccScene;
    bool ccSceneReady;
};

}

#endif
