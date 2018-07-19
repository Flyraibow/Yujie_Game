//
//  ExcelParserFriendIdVector.hpp
//  ResourcePackager
//
//  Created by Yujie Liu on 7/16/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#ifndef ExcelParserFriendIdVector_hpp
#define ExcelParserFriendIdVector_hpp

#include <stdio.h>
#include "ExcelParserBase.hpp"

class ExcelParserFriendIdVector : public ExcelParserBase {
public:
  ExcelParserFriendIdVector(const DataSchema *schema,const string & idSchemaName);
  virtual string getVariableName() const;
  virtual string getVariableGetterName() const;
  virtual string getVariableSetterName() const;
  virtual void addFunctionsInclass(CPPClass *cppClass) const;
  virtual void addHeaders(CPPFileComplete *cppFile) const;
  virtual string getType() const;
  virtual void addInitFuncBody(CPPFunction *func) const;
};
#endif /* ExcelParserFriendIdVector_hpp */
