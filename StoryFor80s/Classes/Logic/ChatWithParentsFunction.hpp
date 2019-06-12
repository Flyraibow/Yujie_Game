//
//  ChatWithParentsFunction.hpp
//  StoryFor80s
//
//  Created by Yujie Liu on 6/11/19.
//

#ifndef ChatWithParentsFunction_hpp
#define ChatWithParentsFunction_hpp

#include <stdio.h>
#include <map>
#include "json.hpp"

using namespace std;

namespace story {
  void chatWithParents(const nlohmann::json &jsonContent);
}

#endif /* ChatWithParentsFunction_hpp */
