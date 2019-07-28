//
//  SimpleLevelData.hpp
//  MiniMonopoly
//
//  Created by Yujie Liu on 7/27/19.
//

#ifndef SimpleLevelData_hpp
#define SimpleLevelData_hpp

#include <stdio.h>
#include <vector>
#include "json.hpp"

using namespace std;

static const string LEVEL_FILE_FOLDER = "res/Data/Level";

class SimpleLevelData
{
protected:
  string p_id;
  string p_name;
  string p_iconPath;
public:
  SimpleLevelData(const string &id);
  SimpleLevelData(const nlohmann::json &jsonContent);
  string getId() const {return p_id;};
  string getName() const {return p_name;};
  string getIconPath() const {return p_iconPath;};
};
#endif /* SimpleLevelData_hpp */
