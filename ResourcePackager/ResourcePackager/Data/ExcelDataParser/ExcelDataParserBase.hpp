//
//  ExcelDataParserBase.hpp
//  ResourcePackager
//
//  Created by Yujie Liu on 7/21/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#ifndef ExcelDataParserBase_hpp
#define ExcelDataParserBase_hpp

#include <string>
#include <vector>
#include <unordered_map>
#include "DataSchema.hpp"
#include "LanguageData.hpp"
#include "CPPFile.hpp"

using namespace std;

class ExcelDataParserBase
{
protected:
  string p_filePath;             // e.g. .../../city.csv
  string p_className;            // e.g. CityData
  string p_variableName;         // e.g. cityData;
  string p_classTypeName;          // GoodsData*
  string p_resDataFileName;
  string p_fileNameWithoutExt;   // e.g. city
  CPPFileComplete *p_file;
  CPPClass *p_class;
  vector<DataSchema *> p_dataSchemas;
  vector<vector<string>> p_values;
  virtual void setPrepareFunction();     // decide which header to add
  virtual void setInitFunction();
  virtual void setLoadFunction(const CPPVariable* pathVar);
  virtual void setSaveFunction(const CPPVariable* pathVar);
  virtual void setClearFunction();
  string getSaveLoadPathCode() const;
  int p_needSaveDataNumber;
  
  virtual string getInstanceCode() const;
  virtual void sanityCheck() const;
public:
  string getFilePath() const;
  string getClassName() const;
  vector<DataSchema *> getDataSchemas() const;
  
  virtual CPPFileComplete* getMainCppFile() const;
  virtual CPPClass* getMainCppClass() const;
  
  virtual void saveData(const string& folderPath, LanguageData &langData);
  void generateCode(const string& folderPath);
  
  bool containWritableData() const;
  
  static ExcelDataParserBase* createWithPath(const string &filePath);
};


#endif /* ExcelDataParserBase_hpp */