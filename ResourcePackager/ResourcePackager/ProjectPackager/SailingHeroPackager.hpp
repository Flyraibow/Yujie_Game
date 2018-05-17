//
//  SailingHeroPackager.hpp
//  ResourcePackager
//
//  Created by Yujie Liu on 5/16/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#ifndef SailingHeroPackager_hpp
#define SailingHeroPackager_hpp

#include "ProjectPackagerBase.hpp"

#include <stdio.h>
#include <string>

using namespace std;

class SailingHeroPackager : public ProjectPackagerBase
{
private:
    void readBaseFiles();
public:
    void startPackage();
};

#endif /* SailingHeroPackager_hpp */
