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

class ExcelParserBase {
protected:
  const DataSchema* p_schema;
  string p_idSchemaName;  // e.g. p_goodsId
  string p_fileNameWithoutExt;
public:
  static ExcelParserBase* createWithSchema(const DataSchema *schema, const string &idSchemaName);
  ExcelParserBase(const DataSchema *schema, const string & idSchemaName);
  
  void setFileNameWithoutExt(const string &fileNameWithoutExt);
  
  virtual string getVariableName() const;
  virtual string getVariableGetterName() const;
  virtual string getVariableSetterName() const;
  virtual string getDescription() const;
  virtual string getType() const;

  virtual void addFunctionsInclass(CPPClass *cppClass) const;
  virtual void addHeaders(CPPFileComplete *cppFile) const;
  virtual void addInitFuncBody(CPPFunction *func) const;
};

#endif /* ExcelParserBase_hpp */
