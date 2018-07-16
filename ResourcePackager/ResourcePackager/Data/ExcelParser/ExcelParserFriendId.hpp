//
//  ExcelParserFriendId.hpp
//  ResourcePackager
//
//  Created by Yujie Liu on 7/15/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#ifndef ExcelParserFriendId_hpp
#define ExcelParserFriendId_hpp

#include <stdio.h>
#include "ExcelParserBase.hpp"

class ExcelParserFriendId : public ExcelParserBase {
public:
  ExcelParserFriendId(const DataSchema *schema,const string & idSchemaName);
  virtual string getVariableName() const;
  virtual string getVariableGetterName() const;
  virtual void addFunctionsInclass(CPPClass *cppClass) const;
  virtual void addHeaders(CPPFileComplete *cppFile) const;
};

#endif /* ExcelParserFriendId_hpp */
