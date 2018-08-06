//
//  ExcelData2DBasedParser.hpp
//  ResourcePackager
//
//  Created by Yujie Liu on 8/4/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#ifndef ExcelData2DBasedParser_hpp
#define ExcelData2DBasedParser_hpp
#include "ExcelDataParserBase.hpp"

using namespace std;

class ExcelData2DBasedParser : public ExcelDataParserBase
{
private:
  const DataSchema* p_rowIdSchema;
  const DataSchema* p_colIdSchema;
  const DataSchema* p_returnSchema;
  string p_rowIdName;                  // e.g. goodsId
  string p_colIdName;                  // e.g. cultureId
  string p_returnType;                
  vector<string> p_rowIds;
  vector<string> p_colIds;
protected:
  virtual void setInitFunction();
  virtual void setLoadFunction(const CPPVariable* variable);
  virtual void setSaveFunction(const CPPVariable* variable);
  virtual void setClearFunction();
  virtual void sanityCheck() const;
  virtual string getInstanceCode() const;
  void addRegisterDataFunction();
public:
  ExcelData2DBasedParser(const vector<vector<string>> &excelData);
  virtual void saveData(const string& folderPath, LanguageData &langData);
  virtual CPPFileComplete* getMainCppFile() const;
  virtual CPPClass* getMainCppClass() const;
  virtual void addDataLoadFunction(CPPClass* dataManager) const;
  virtual bool containWritableData() const;
};

#endif /* ExcelData2DBasedParser_hpp */
