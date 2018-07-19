//
//  ExcelParserFriendIdSet.hpp
//  ResourcePackager
//
//  Created by Yujie Liu on 7/15/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#ifndef ExcelParserFriendIdSet_hpp
#define ExcelParserFriendIdSet_hpp

#include <stdio.h>
#include "ExcelParserBase.hpp"

class ExcelParserFriendIdSet : public ExcelParserBase {
public:
  ExcelParserFriendIdSet(const DataSchema *schema,const string & idSchemaName);
  virtual string getVariableName() const;
  virtual string getVariableGetterName() const;
  virtual string getVariableSetterName() const;
  virtual void addFunctionsInclass(CPPClass *cppClass) const;
  virtual void addHeaders(CPPFileComplete *cppFile) const;
  virtual string getType() const;
  virtual void addInitFuncBody(CPPFunction *func) const;
};

#endif /* ExcelParserFriendIdSet_hpp */
