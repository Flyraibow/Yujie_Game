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
#include "ExcelParserFriendIdMap.hpp"
#include "ExcelParserMap.hpp"
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
    case FRIEND_ID_MAP:
      return new ExcelParserFriendIdMap(schema, idSchemaName);
    case MAP:
      return new ExcelParserMap(schema, idSchemaName);
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


void ExcelParserBase::addSetFieldValueFuncBody(CPPFunction *setFieldFunc)
{
  setFieldFunc->addBodyStatements("\tthis->" + getVariableSetterName() + "(" + castFromStringToValue(p_schema->getType(), "value") + ");");
}

void ExcelParserBase::addGetFieldValueFuncBody(CPPFunction *getFieldFunc) const
{
  getFieldFunc->addBodyStatements("\treturn to_string(this->" + getVariableGetterName()+ "());");
}

string ExcelParserBase::getType() const
{
  string finalType;
  switch (p_schema->getType()) {
    case ID:
      finalType = p_schema->getSubtype();
      break;
    case FRIEND_ID:
    case ICON:
    case MUSIC:
    case EFFECT:
    case STRING:
    case LANGUAGE:
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
    default:
      // unknow type or load from subclass
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


string ExcelParserBase::getBufferGetString(const DataType type) const
{
  switch (type) {
    case STRING:
    case ICON:
    case MUSIC:
    case FRIEND_ID:
      return "getString()";
    case INT:
      return "getInt()";
    case FLOAT:
      return "getFloat()";
    case LONG:
      return "getLong()";
    case DOUBLE:
      return "getDouble()";
    case BOOL:
      return "getChar()";
    default:
      // not defined
      assert(false);
  }
}

void ExcelParserBase::addInitFuncBody(CPPFunction *func, const string &variableName, int level) const
{
  string schemaName = this->getVariableName();
  switch (p_schema->getType()) {
    case ID: {
      string st = variableName + "->" + schemaName + " = buffer->" + (p_schema->getSubtype() == TYPE_INT ? "getInt();" : "getString();");
      func->addBodyStatements(st, level);
      break;
    }
    case VECTOR:
    case SET:{
      func->addBodyStatementsList({
        "auto " + p_schema->getName() + "Count = buffer->getLong();",
        "for (int j = 0; j < " + p_schema->getName() + "Count; ++j) {"
      }, 3);
      string getterFuncName = p_schema->getSubtype(); // int
      getterFuncName[0] = toupper(getterFuncName[0]);  // Int
      getterFuncName = "get" + getterFuncName + "()";  // getInt()
      if (p_schema->getType() == VECTOR) {
        func->addBodyStatements(variableName + "->" + schemaName + ".push_back(buffer->" + getterFuncName + ");", level + 1);
      } else {
        func->addBodyStatements(variableName + "->" + schemaName + ".insert(buffer->" + getterFuncName + ");", level + 1);
      }
      func->addBodyStatements("}", level);
      break;
    }
    default:
      string st = variableName + "->" + schemaName + " = buffer->" + getBufferGetString(p_schema->getType()) + ";";
      func->addBodyStatements(st, level);
      break;
  }
}

void ExcelParserBase::addSaveFuncBody(CPPFunction *saveFunc, const string dataName, int level) const
{
  auto schemaName = getVariableName();
  saveFunc->addBodyStatementsList({
    "buffer->putString(\"" + schemaName + "\");",
    "buffer->putString(to_string(" + dataName + "->" + schemaName + "));",
  }, level);
}

void ExcelParserBase::addLoadFuncBody(CPPFunction *loadFunc, bool isFirstOne, const string dataName, int level) const
{
  auto schemaName = getVariableName();
  string prefix = isFirstOne ? "": "} else ";
  loadFunc->addBodyStatementsList({
    prefix + "if (key == \"" + schemaName + "\") {",
    "\t" + dataName + "->" + schemaName + " = " + castFromStringToValue(p_schema->getType(), "value") + ";",
  }, level);
}
