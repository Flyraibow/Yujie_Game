//
//  main.cpp
//  ResourcePackager
//
//  Created by Yujie Liu on 5/16/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#include <iostream>

#include "SailingHeroPackager.hpp"
#include "StoryFor80sPackager.hpp"

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
//    SailingHeroPackager packager;
//    packager.set_dataSourcePath("/Users/yujiel/Documents/cocos2dx/cocos2d-x/YUJIE_GAME/SailingHero/DataSource");
//    packager.set_outputResourcePath("/Users/yujiel/Documents/cocos2dx/cocos2d-x/YUJIE_GAME/SailingHero/Resources/res");
//    packager.set_outputCodeFolderPath("/Users/yujiel/Documents/cocos2dx/cocos2d-x/YUJIE_GAME/SailingHero/Classes/DataManager/GenerateData/");
//    packager.startPackage();
  StoryFor80sPackager packager;
  packager.set_dataSourcePath("/Users/yujiel/Documents/cocos2dx/cocos2d-x/YUJIE_GAME/StoryFor80s/DataSource");
  packager.set_outputResourcePath("/Users/yujiel/Documents/cocos2dx/cocos2d-x/YUJIE_GAME/StoryFor80s/Resources/res");
  packager.set_outputCodeFolderPath("/Users/yujiel/Documents/cocos2dx/cocos2d-x/YUJIE_GAME/StoryFor80s/Classes/GeneratedData/");
  packager.startPackage();
    return 0;
}
