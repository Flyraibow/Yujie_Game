//
//  ExcelParserTranslation.cpp
//  ResourcePackager
//
//  Created by Yujie Liu on 7/15/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#include "ExcelParserTranslation.hpp"

ExcelParserTranslation::ExcelParserTranslation(const DataSchema *schema,const string & idSchemaName) : ExcelParserBase(schema, idSchemaName)
{
  
}


void ExcelParserTranslation::addFunctionsInclass(CPPClass *cppClass) const
{
  auto schemaName = this->getVariableName();
  string id_string_name = "p_" + p_idSchemaName;  // p_goodsId;
  auto getSchemaFuncName = this->getVariableGetterName();
  auto getSchemaFunc = new CPPFunction(getSchemaFuncName, TYPE_STRING);
  if (p_schema->isWritable()) {
    cppClass->addVariable(schemaName, TYPE_STRING, true);
    getSchemaFunc->addBodyStatementsList({
      "if (" + schemaName + ".length() > 0) {",
      "\treturn " + schemaName + ";",
      "}"
    }, 0);
    
    auto setSchemaFuncName = this->getVariableSetterName();
    
    auto setSchemaFunc = new CPPFunction(setSchemaFuncName, TYPE_VOID, {new CPPVariable(p_schema->getName(), TYPE_STRING)}, false, false);
    setSchemaFunc->addBodyStatements(schemaName + " = " + p_schema->getName() + ";");
    cppClass->addFunction(setSchemaFunc, false);
  }
  getSchemaFunc->addBodyStatementsList({
    "string localId = \"" + p_fileNameWithoutExt + "_" + p_schema->getName() + "_\" + to_string(" + id_string_name + ");",
    "return LocalizationHelper::getLocalization(localId);"
  }, 0);
  cppClass->addFunction(getSchemaFunc, false);
}

string ExcelParserTranslation::getDescription() const
{
  string descriptState_1 = "desc += \"\\t" + p_schema->getName() + " : \" + ";
  string descriptState_3 = "+ \"\\n\";";
  
  return descriptState_1 + this->getVariableGetterName() + "() " + descriptState_3;
}
