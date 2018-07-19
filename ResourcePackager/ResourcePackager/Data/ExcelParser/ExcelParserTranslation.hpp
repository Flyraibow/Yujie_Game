//
//  ExcelParserTranslation.hpp
//  ResourcePackager
//
//  Created by Yujie Liu on 7/15/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#ifndef ExcelParserTranslation_hpp
#define ExcelParserTranslation_hpp

#include <stdio.h>
#include "ExcelParserBase.hpp"

class ExcelParserTranslation : public ExcelParserBase {
public:
  ExcelParserTranslation(const DataSchema *schema,const string & idSchemaName);
  
  virtual void addFunctionsInclass(CPPClass *cppClass) const;
  virtual string getDescription() const;
  virtual void addInitFuncBody(CPPFunction *func) const;
};

#endif /* ExcelParserTranslation_hpp */
