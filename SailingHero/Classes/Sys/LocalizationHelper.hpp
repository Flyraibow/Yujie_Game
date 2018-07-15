//
//  LocalizationHelper.hpp
//  SailingHero-mobile
//
//  Created by Yujie Liu on 5/16/18.
//

#ifndef LocalizationHelper_hpp
#define LocalizationHelper_hpp

#include "base/CCRef.h"
#include <unordered_map>

class LocalizationHelper
{
private:
  std::unordered_map<std::string, std::string> s_map;
  void load(const std::string &filename);
public:
  static LocalizationHelper*  getInstance();
  
  static std::string getLocalization(const std::string &localId);
};

#endif /* LocalizationHelper_hpp */

