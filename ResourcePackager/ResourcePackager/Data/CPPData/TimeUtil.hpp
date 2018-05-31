//
//  TimeUtil.hpp
//  ResourcePackager
//
//  Created by Yujie Liu on 5/30/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#ifndef TimeUtil_hpp
#define TimeUtil_hpp

#include <stdio.h>
#include <string>
#include <ctime>

using namespace std;

string dateTimeToString(const tm& t, const char* format);
tm now();

#endif /* TimeUtil_hpp */
