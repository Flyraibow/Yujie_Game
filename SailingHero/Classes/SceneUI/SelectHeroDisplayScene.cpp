//
//  SelectHeroDisplayScene.cpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 7/14/18.
//

#include "SelectHeroDisplayScene.hpp"
#include "SystemButton.hpp"
#include "LocalizationHelper.hpp"
#include "HeroSelectingFrame.hpp"
#include "SHGameDataHelper.hpp"
#include "Calendar.hpp"
#include "DataManager.hpp"

USING_NS_CC;
using namespace ui;

Scene* SelectHeroDisplayScene::createScene(HeroSelectData *selectHeroData)
{
  DataManager::getShareInstance()->setTempData("selectHero", selectHeroData);
  auto scene = SelectHeroDisplayScene::create();
  return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
  printf("Error while loading: %s\n", filename);
  printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SelectHeroDisplayScene.cpp\n");
}

// on "init" you need to initialize your instance
bool SelectHeroDisplayScene::init()
{
  //////////////////////////////
  // 1. super init first
  if ( !SHScene::init() )
  {
    return false;
  }

  initSceneWithJson("selectHeroDisplay");

  return true;
}

// TODO: Move this logic to event too

#include "DialogFrame.hpp"
#include "MultiSelectionFrame.hpp"
#include "AbilityData.hpp"

//void SelectHeroDisplayScene::clickChangeStartGame(cocos2d::Ref* pSender)
//{
//  auto dialog = DialogFrame::createWithDialogIds({"1"}, [this](){
//    // 对话结束了
//    auto abilityMapList = AbilityData::getSharedDictionary();
//    vector<AbilityData *> datalist;
//    vector<string> selectList;
//    for(auto it = abilityMapList->begin(); it != abilityMapList->end(); ++it ) {
//      datalist.push_back(it->second);
//      selectList.push_back(it->second->getAbilityDescription());
//    }
//    
//    auto frame = MultiSelectionFrame::createMultiSelectFrame(selectList, 3, [datalist, this](vector<int> selectedIndexes){
//      for (int i = 0; i < selectedIndexes.size(); ++i) {
//        int index = selectedIndexes[i];
//        CCLOG("选择了 %d", index);
//        CCLOG("选择了 %s", datalist.at(index)->getAbilityName().c_str());
//      }
////      this->selectHero();
//      
//    });
//    this->addChild(frame, 2);
//  });
//  s_window->addChild(dialog->getSprite());
//}
