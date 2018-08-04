//
//  ExcelParserBase.hpp
//  ResourcePackager
//
//  Created by Yujie Liu on 7/15/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#ifndef ExcelParserBase_hpp
#define ExcelParserBase_hpp

#include <stdio.h>

#include "DataSchema.hpp"
#include "CPPClass.hpp"
#include "CPPFile.hpp"
#include <unordered_map>

using namespace std;

static string castFromStringToValue(DataType type, const string &val) {
  if (type == INT) {
    return "atoi("+val+".c_str())";
  } else if (type == LONG) {
    return "atoll("+val+".c_str())";
  } else if (type == DOUBLE) {
    return "atof("+val+".c_str())";
  } else if (type == BOOL) {
    return "(atoi("+val+".c_str()) != 0)";
  } else if (type == SET || type == FRIEND_ID_SET) {
    return "atoset("+val+")";
  } else if (type == VECTOR || type == FRIEND_ID_VECTOR) {
    return "atovector("+val+")";
  }
  return val;
}

class ExcelParserBase {
protected:
  const DataSchema* p_schema;
  string p_idSchemaName;  // e.g. p_goodsId
  string p_fileNameWithoutExt;
public:
  static ExcelParserBase* createWithSchema(const DataSchema *schema, const string &idSchemaName);
  ExcelParserBase(const DataSchema *schema, const string & idSchemaName);
  
  void setFileNameWithoutExt(const string &fileNameWithoutExt);
  string getBufferGetString(const DataType type) const;
  
  virtual string getVariableName() const;
  virtual string getVariableGetterName() const;
  virtual string getVariableSetterName() const;
  virtual string getDescription() const;
  virtual string getType() const;

  virtual void addFunctionsInclass(CPPClass *cppClass) const;
  virtual void addHeaders(CPPFileComplete *cppFile) const;
  virtual void addInitFuncBody(CPPFunction *func, const string &variableName, int level = 3) const;
  virtual void addSaveFuncBody(CPPFunction *saveFunc, const string dataName = "data", int level = 1) const;
  virtual void addLoadFuncBody(CPPFunction *loadFunc, bool isFirstOne, const string dataName = "data" , int level = 4) const;
};

#endif /* ExcelParserBase_hpp */
