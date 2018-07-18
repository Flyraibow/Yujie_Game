//
//  ExcelParserBase.cpp
//  ResourcePackager
//
//  Created by Yujie Liu on 7/15/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#include "ExcelParserBase.hpp"
#include "ExcelParserFriendId.hpp"
#include "ExcelParserTranslation.hpp"
#include "ExcelParserIcon.hpp"
#include "ExcelParserMusic.hpp"
#include "ExcelParserFriendIdSet.hpp"
#include "ExcelParserFriendIdVector.hpp"
#include "Utils.hpp"

ExcelParserBase* ExcelParserBase::createWithSchema(const DataSchema *schema, const string &idSchemaName)
{
  switch (schema->getType())
  {
    case FRIEND_ID:
      return new ExcelParserFriendId(schema, idSchemaName);
    case LANGUAGE:
      return new ExcelParserTranslation(schema,idSchemaName);
    case ICON:
      return new ExcelParserIcon(schema,idSchemaName);
    case MUSIC:
      return new ExcelParserMusic(schema,idSchemaName);
    case FRIEND_ID_SET:
      return new ExcelParserFriendIdSet(schema,idSchemaName);
    case FRIEND_ID_VECTOR:
      return new ExcelParserFriendIdVector(schema,idSchemaName);
    default:
      return new ExcelParserBase(schema,idSchemaName);
  }
}

ExcelParserBase::ExcelParserBase(const DataSchema *schema,const string & idSchemaName)
{
  p_schema = schema;
  p_idSchemaName = idSchemaName;
}

void ExcelParserBase::setFileNameWithoutExt(const string &fileNameWithoutExt)
{
  p_fileNameWithoutExt = fileNameWithoutExt;
}

string ExcelParserBase::getVariableName() const
{
  return "p_" + p_schema->getName();
}

string ExcelParserBase::getVariableGetterName() const
{
  std::locale loc;
  string getSchemaFuncName = p_schema->getName();
  getSchemaFuncName[0] = toupper(getSchemaFuncName[0], loc);
  getSchemaFuncName = "get" + getSchemaFuncName;  // getGoodsId
  return getSchemaFuncName;
}

string ExcelParserBase::getVariableSetterName() const
{
  std::locale loc;
  string setSchemaFuncName = p_schema->getName();
  setSchemaFuncName[0] = toupper(setSchemaFuncName[0], loc);
  setSchemaFuncName = "set" + setSchemaFuncName;  // setGoodsId
  return setSchemaFuncName;
}

string ExcelParserBase::getDescription() const
{
  string descriptState_1 = "desc += \"\\t" + p_schema->getName() + " : \" + ";
  string descriptState_2 = "to_string(" + this->getVariableName() + ") ";
  string descriptState_3 = "+ \"\\n\";";
  
  return descriptState_1 + descriptState_2 + descriptState_3;
}


string ExcelParserBase::getType() const
{
  string finalType;
  switch (p_schema->getType()) {
    case ID:
      // Never set ID
      assert(!p_schema->isWritable());
      finalType = p_schema->getSubtype();
      break;
    case FRIEND_ID:
    case ICON:
    case MUSIC:
    case EFFECT:
    case STRING:
      finalType = TYPE_STRING;
      break;
    case INT:
      finalType = TYPE_INT;
      break;
    case FLOAT:
      finalType = TYPE_FLOAT;
      break;
    case LONG:
      finalType = TYPE_LONG;
      break;
    case DOUBLE:
      finalType = TYPE_DOUBLE;
      break;
    case BOOL:
      finalType = TYPE_BOOL;
      break;
    case VECTOR: {
      finalType = TYPE_VECTOR(p_schema->getSubtype());
      break;
    }
    case SET: {
      finalType = TYPE_SET(p_schema->getSubtype());
      break;
    }
    case FRIEND_ID_SET: {
      finalType = TYPE_SET(TYPE_STRING);
      break;
    }
    case FRIEND_ID_VECTOR: {
      finalType = TYPE_VECTOR(TYPE_STRING);
      break;
    }
    default:
      // unknow type
      assert(false);
      break;
  }
  return finalType;
}

void ExcelParserBase::addFunctionsInclass(CPPClass *cppClass) const
{
  auto finalType = this->getType();
  auto getSchemaFuncName = this->getVariableGetterName();
  auto schemaName = this->getVariableName();
  auto getSchemaFunc = new CPPFunction(getSchemaFuncName, finalType);
  cppClass->addVariable(schemaName, finalType, true);
  getSchemaFunc->addBodyStatements("return " + schemaName + ";");
  cppClass->addFunction(getSchemaFunc, false);
  // todo: need release data
  //            delete getSchemaFunc;
  if (p_schema->isWritable()) {
    auto setSchemaFuncName = this->getVariableSetterName();
    auto setSchemaFunc = new CPPFunction(setSchemaFuncName, TYPE_VOID, {new CPPVariable(p_schema->getName(), finalType)}, false, false);
    setSchemaFunc->addBodyStatements(schemaName + " = " + p_schema->getName() + ";");
    cppClass->addFunction(setSchemaFunc, false);
  }
}

void ExcelParserBase::addHeaders(CPPFileComplete *cppFile) const
{
  
}

void ExcelParserBase::addInitFuncBody(CPPFunction *func) const
{
  int level = 3;
  string schemaName = this->getVariableName();
  auto variableName = p_fileNameWithoutExt + "Data";
  switch (p_schema->getType()) {
    case ID: {
      string st = variableName + "->" + schemaName + " = buffer->" + (p_schema->getSubtype() == TYPE_INT ? "getInt();" : "getString();");
      func->addBodyStatements(st, level);
      break;
    }
    case FRIEND_ID:
    case ICON:
    case MUSIC:
    case STRING: {
      string st = variableName + "->" + schemaName + " = buffer->" + "getString();";
      func->addBodyStatements(st, level);
      break;
    }
    case INT: {
      string st = variableName + "->" + schemaName + " = buffer->" + "getInt();";
      func->addBodyStatements(st, level);
      break;
    }
    case FLOAT: {
      string st = variableName + "->" + schemaName + " = buffer->" + "getFloat();";
      func->addBodyStatements(st, level);
      break;
    }
    case LONG: {
      string st = variableName + "->" + schemaName + " = buffer->" + "getLong();";
      func->addBodyStatements(st, level);
      break;
    }
    case DOUBLE: {
      string st = variableName + "->" + schemaName + " = buffer->" + "getDouble();";
      func->addBodyStatements(st, level);
      break;
    }
    case BOOL: {
      string st = variableName + "->" + schemaName + " = buffer->" + "getChar();";
      func->addBodyStatements(st, level);
      break;
    }
    case VECTOR:
    case SET:
    case FRIEND_ID_SET:
    case FRIEND_ID_VECTOR:{
      func->addBodyStatementsList({
        "auto " + p_schema->getName() + "Count = buffer->getLong();",
        "for (int j = 0; j < " + p_schema->getName() + "Count; ++j) {"
      }, 3);
      string getterFuncName = p_schema->getSubtype(); // int
      if (p_schema->getType() == FRIEND_ID_SET || p_schema->getType() == FRIEND_ID_VECTOR) {
        getterFuncName = TYPE_STRING;
      }
      getterFuncName[0] = toupper(getterFuncName[0]);  // Int
      getterFuncName = "get" + getterFuncName + "()";  // getInt()
      if (p_schema->getType() == VECTOR || p_schema->getType() == FRIEND_ID_VECTOR) {
        func->addBodyStatements(variableName + "->" + schemaName + ".push_back(buffer->" + getterFuncName + ");", level + 1);
      } else {
        func->addBodyStatements(variableName + "->" + schemaName + ".insert(buffer->" + getterFuncName + ");", level + 1);
      }
      func->addBodyStatements("}", level);
      
      break;
    }
    default:
      break;
  }
}
