//
//  ExcelParserMusic.hpp
//  ResourcePackager
//
//  Created by Yujie Liu on 7/15/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#ifndef ExcelParserMusic_hpp
#define ExcelParserMusic_hpp

#include <stdio.h>
#include "ExcelParserBase.hpp"
class ExcelParserMusic : public ExcelParserBase {
public:
  ExcelParserMusic(const DataSchema *schema,const string & idSchemaName);
  virtual void addFunctionsInclass(CPPClass *cppClass) const;
};

#endif /* ExcelParserMusic_hpp */
