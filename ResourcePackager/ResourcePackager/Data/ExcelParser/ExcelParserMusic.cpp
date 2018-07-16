//
//  ExcelParserMusic.cpp
//  ResourcePackager
//
//  Created by Yujie Liu on 7/15/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#include "ExcelParserMusic.hpp"
ExcelParserMusic::ExcelParserMusic(const DataSchema *schema,const string & idSchemaName) : ExcelParserBase(schema, idSchemaName)
{
  
}

void ExcelParserMusic::addFunctionsInclass(CPPClass *cppClass) const
{
  string getIconFuncName = this->getVariableGetterName(); // getMusicId
  getIconFuncName = getIconFuncName.substr(0, getIconFuncName.length() - 2) + "Path";  // getMusicPath
  auto getIconFunction = new CPPFunction(getIconFuncName, TYPE_STRING);
  getIconFunction->addBodyStatementsList({
    "static const string s_basePath = \"" + p_schema->getSubtype() + "\";",
    "return s_basePath + " + this->getVariableName() + ";",
    
  }, 0);
  cppClass->addFunction(getIconFunction, false);
  this->ExcelParserBase::addFunctionsInclass(cppClass);
}
