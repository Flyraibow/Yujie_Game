//
//  ExcelParserIcon.hpp
//  ResourcePackager
//
//  Created by Yujie Liu on 7/15/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#ifndef ExcelParserIcon_hpp
#define ExcelParserIcon_hpp

#include <stdio.h>
#include "ExcelParserBase.hpp"

class ExcelParserIcon : public ExcelParserBase {
public:
  ExcelParserIcon(const DataSchema *schema,const string & idSchemaName);
  virtual void addFunctionsInclass(CPPClass *cppClass) const;
  virtual void addGetFieldValueFuncBody(CPPFunction *getFieldFunc) const;
};

#endif /* ExcelParserIcon_hpp */
