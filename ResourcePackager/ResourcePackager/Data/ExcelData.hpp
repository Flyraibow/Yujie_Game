//
//  ExcelData.hpp
//  ResourcePackager
//
//  Created by Yujie Liu on 5/28/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#ifndef ExcelData_hpp
#define ExcelData_hpp

#include <string>
#include <vector>
#include <unordered_map>
#include "DataSchema.hpp"
#include "LanguageData.hpp"
#include "CPPFile.hpp"

using namespace std;

class ExcelData
{
private:
  string p_filePath;
  string p_className;
  vector<DataSchema *> p_dataSchemas;
  vector<vector<string>> p_values;
  string p_resDataFileName;
  void setInitFunction(const string &className, CPPClass *cppClass, CPPFileComplete *cppFile) const;
  
public:
  string getFilePath() const;
  string getClassName() const;
  vector<DataSchema *> getDataSchemas() const;
  
  void saveData(const string& folderPath, const string& fileName, LanguageData &langData);
  void generateCode(const string& folderPath, const string& fileName);
  
  bool containWritableData() const;
  
  static ExcelData* createWithPath(const string &filePath);
};

#endif /* ExcelData_hpp */

