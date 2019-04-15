//
//  ExcelParserFriendIdMap.hpp
//  ResourcePackager
//
//  Created by Yujie Liu on 7/18/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#ifndef ExcelParserFriendIdMap_hpp
#define ExcelParserFriendIdMap_hpp

#include <stdio.h>
#include "ExcelParserBase.hpp"

class ExcelParserFriendIdMap : public ExcelParserBase {
private:
  string p_keyType;
  string p_valueType;
  string getVariableType() const;
  string convertMapLine(const string &value) const;
  string convertMapDefine() const;
public:
  ExcelParserFriendIdMap(const DataSchema *schema,const string & idSchemaName);
  virtual string getVariableName() const;
  virtual string getVariableGetterName() const;
  virtual string getVariableSetterName() const;
  virtual string getDescription() const;
  virtual void addHeaders(CPPFileComplete *cppFile) const;
  virtual string getType() const;
  virtual void addSaveFuncBody(CPPFunction *saveFunc, const string dataName = "data", int level = 1) const;
  virtual void addLoadFuncBody(CPPFunction *loadFunc, bool isFirstOne, const string dataName = "data", int level = 4) const;
  virtual void addInitFuncBody(CPPFunction *func, const string &variableName, int level = 3) const;
  virtual void addSetFieldValueFuncBody(CPPFunction *setFieldFunc);
  virtual void addFunctionsInclass(CPPClass *cppClass) const;
  virtual void addGetFieldListFuncBody(CPPFunction *getFieldListFunc) const;
  virtual void addGetMapFieldWithKeyFuncBody(CPPFunction *getFieldListFunc) const;
};

#endif /* ExcelParserFriendIdMap_hpp */
