#ifndef _SH_DATA_MANAGER_H_
#define _SH_DATA_MANAGER_H_

#include <string>

#include "GameData/GameData.hpp"
#include "GameData/DialogData.hpp"
#include "GameData/HeroData.hpp"

namespace SailingHeroAPI {

class SHDataManager {
public:
    static SHDataManager * getInstance();

    template <class T>
    void set(std::string key, T value);

    template <class T>
    T getWithDefault(std::string key, T defaultValue);

    void loadData(std::string basePath);

    GameData * getGameData();

    DialogData * getDialogData(std::string dialogId);

    HeroData * getHeroData(int heroId);

private:
    static SHDataManager instance;
};

}

#endif