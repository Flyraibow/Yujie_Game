//
//  ExcelData.hpp
//  ResourcePackager
//
//  Created by Yujie Liu on 5/28/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#ifndef ExcelData_hpp
#define ExcelData_hpp

#include "ExcelDataParserBase.hpp"

using namespace std;

class ExcelDataIdBasedParser : public ExcelDataParserBase
{
private:
  const DataSchema* p_idSchema;
  string p_idName;                  // e.g. goodsId
protected:
  virtual void setInitFunction();
  virtual void setPrepareFunction();     // decide which header to add
  virtual void setLoadFunction(const CPPVariable* variable);
  virtual void setSaveFunction(const CPPVariable* variable);
  virtual void setClearFunction();
  void addEnum(CPPFileComplete *cppFile,const DataSchema *schema) const;
  virtual void sanityCheck() const;
  virtual string getInstanceCode() const;
  void addRegisterDataFunction();
public:
  ExcelDataIdBasedParser(const DataSchema *idSchema);
  virtual void saveData(const string& folderPath, LanguageData &langData);
  virtual CPPFileComplete* getMainCppFile() const;
  virtual CPPClass* getMainCppClass() const;
  virtual void addDataLoadFunction(CPPClass* dataManager) const;
};

#endif /* ExcelData_hpp */

