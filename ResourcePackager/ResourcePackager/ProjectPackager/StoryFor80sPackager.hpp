//
//  StoryFor80sPackager.hpp
//  ResourcePackager
//
//  Created by Yujie Liu on 2/10/19.
//  Copyright © 2019 Yujie Liu. All rights reserved.
//

#ifndef StoryFor80sPackager_hpp
#define StoryFor80sPackager_hpp

#include "ProjectPackagerBase.hpp"

#include <stdio.h>
#include <string>

using namespace std;

class StoryFor80sPackager : public ProjectPackagerBase
{
private:
  void readBaseFiles();
public:
  void startPackage();
};

#endif /* StoryFor80sPackager_hpp */
