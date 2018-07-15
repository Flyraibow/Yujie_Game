//
//  ExcelData.cpp
//  ResourcePackager
//
//  Created by Yujie Liu on 5/28/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#include "ExcelData.hpp"
#include "ReadCSV.hpp"
#include "ByteBuffer.hpp"
#include "Utils.hpp"
#include "CPPFile.hpp"

const static unordered_map<string, DataType> s_subtype_map({
  {"bool", BOOL},
  {"int", INT},
  {"long", LONG},
  {"float", FLOAT},
  {"double", DOUBLE},
  {"string", STRING},
});

static string castFromStringToValue(DataType type, const string &val) {
  if (type == INT) {
    return "atoi("+val+".c_str())";
  } else if (type == LONG) {
    return "atoll("+val+".c_str())";
  } else if (type == DOUBLE) {
    return "atof("+val+".c_str())";
  }
  return val;
}

void addVectorToBuffer(std::unique_ptr<bb::ByteBuffer> &buffer, const vector<string> &vals, const string &type)
{
  buffer->putLong(vals.size());
  DataType subType = s_subtype_map.at(type);
  for (int i = 0; i < vals.size(); ++i) {
    auto val = vals.at(i).c_str();
    switch (subType) {
      case BOOL:
        buffer->putChar(atoi(val));
        break;
      case INT:
        buffer->putInt(atoi(val));
        break;
      case DOUBLE:
        buffer->putDouble(atof(val));
        break;
      case LONG:
        buffer->putLong(atoll(val));
        break;
      case STRING:
        buffer->putString(vals.at(i));
        break;
      case FLOAT:
        buffer->putFloat(atof(val));
        break;
      default:
        // unknown type
        assert(false);
        break;
    }
  }
}

string ExcelData::getFilePath() const
{
  return p_filePath;
}

string ExcelData::getClassName() const
{
  return p_className;
}

vector<DataSchema*> ExcelData::getDataSchemas() const
{
  return p_dataSchemas;
}


bool ExcelData::containWritableData() const
{
  for (int i = 0; i < p_dataSchemas.size(); ++i) {
    if (p_dataSchemas.at(i)->isWritable()) {
      return true;
    }
  }
  return false;
}

void ExcelData::saveData(const string& folderPath, const string& fileName, LanguageData &langData)
{
  auto buffer = std::make_unique<bb::ByteBuffer>();
  buffer->putLong(p_values.size());
  for (int i = 0; i < p_values.size(); ++i) {
    auto row = p_values.at(i);
    string id;
    for (int j = 0; j < p_dataSchemas.size(); ++j) {
      DataSchema *schema = p_dataSchemas.at(j);
      auto value = row.at(j);
      switch (schema->getType()) {
        case ID:
          id = value;
        case FRIEND_ID:
        case STRING:
        case ICON:
        case MUSIC:
        case EFFECT:
          buffer->putString(value);
          break;
        case BOOL:
          buffer->put(atoi(value.c_str()));
          break;
        case INT:
          buffer->putInt(atoi(value.c_str()));
          break;
        case LONG:
          buffer->putLong(atoll(value.c_str()));
          break;
        case DOUBLE:
          buffer->putDouble(atof(value.c_str()));
          break;
        case FLOAT:
          buffer->putLong(atof(value.c_str()));
          break;
        case LANGUAGE: {
          string fileNameWithoutExt = fileName.substr(0, fileName.find_last_of("."));
          string localId = fileNameWithoutExt + "_" + schema->getName() + "_" + id;
          langData.addTranslation(schema->getSubtype(), localId, value);
          break;
        };
        case VECTOR:
        case SET: {
          auto subType = schema->getSubtype();
          auto vals = utils::split(value, ';');
          addVectorToBuffer(buffer, vals, subType);
          break;
        }
        case COMMENT:
          // skip
          break;
        default:
          // doesn't support other type
          assert(false);
          break;
      }
    }
  }
  utils::writeBufferToFile(buffer, folderPath, fileName);
  p_resDataFileName = fileName;
}


void ExcelData::generateCode(const string& folderPath, const string& fileName)
{
  std::locale loc;
  string first_capital_file_name = fileName;
  first_capital_file_name[0] = toupper(fileName[0], loc);
  p_className = first_capital_file_name + "Data";
  CPPFileComplete* file = new CPPFileComplete(p_className);
  file->addHeaders("map", false, true);
  file->addHeaders("cocos2d.h", true, false);
  file->addHeaders("ByteBuffer.hpp", true, false);
  file->addHeaders("Utils.hpp", true, false);
  CPPClass *cppClass = new CPPClass(p_className);
  this->setInitFunction(p_className, cppClass, file);
  file->addClass(cppClass);
  file->saveFiles(folderPath);
  delete cppClass;
  delete file;
}

void addReadDataFunctionBody(CPPFunction *func, const string &variableName, const DataSchema *schema, int level) {
  
  string schemaName = "p_" + schema->getName(); // p_goodsId
  switch (schema->getType()) {
    case ID:
    case FRIEND_ID:
    case ICON:
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
    case SET: {
      func->addBodyStatementsList({
        "auto " + schema->getName() + "Count = buffer->getLong();",
        "for (int j = 0; j < " + schema->getName() + "Count; ++j) {"
      }, 3);
      string getterFuncName = schema->getSubtype(); // int
      getterFuncName[0] = toupper(getterFuncName[0]);  // Int
      getterFuncName = "get" + getterFuncName + "()";  // getInt()
      if (schema->getType() == VECTOR) {
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

void setPublicGetFunction(CPPClass *cppClass, const DataSchema *schema, const string &id_schema_name, const string &fileNameWithoutExt, CPPFunction *descFunction, CPPFileComplete *cppFile, CPPFunction *initFunction, const string &variableName)
{
  std::locale loc;
  auto type = schema->getType();
  if (type == COMMENT || type == VECTOR) {
    // skip comment and vector
    return;
  }
  string schemaName = "p_" + schema->getName(); // p_goodsId
  string getSchemaFuncName = schema->getName();
  getSchemaFuncName[0] = toupper(getSchemaFuncName[0], loc);
  getSchemaFuncName = "get" + getSchemaFuncName;  // getGoodsId
  
  string setSchemaFuncName = schema->getName();
  setSchemaFuncName[0] = toupper(setSchemaFuncName[0], loc);
  setSchemaFuncName = "set" + setSchemaFuncName;  // setGoodsId
  
  CPPFunction *getSchemaFunc = nullptr;
  CPPFunction *setSchemaFunc = nullptr;
  string descriptState_1 = "desc += \"\\t" + schema->getName() + " : \" + ";
  string descriptState_3 = "+ \"\\n\";";
  if (type == LANGUAGE) {
    // only add function, need id before it.
    assert(id_schema_name.length() > 0);
    string id_string_name = "p_" + id_schema_name;  // p_goodsId;
    getSchemaFunc = new CPPFunction(getSchemaFuncName, TYPE_STRING);
    if (schema->isWritable()) {
      cppClass->addVariable(schemaName, TYPE_STRING, true);
      getSchemaFunc->addBodyStatementsList({
        "if (" + schemaName + ".length() > 0) {",
        "\treturn " + schemaName + ";",
        "}"
      }, 0);
      
      setSchemaFunc = new CPPFunction(setSchemaFuncName, TYPE_VOID, {new CPPVariable(schema->getName(), TYPE_STRING)}, false, false);
      setSchemaFunc->addBodyStatements(schemaName + " = " + schema->getName() + ";");
      cppClass->addFunction(setSchemaFunc, false);
    }
    getSchemaFunc->addBodyStatementsList({
      "string localId = \"" + fileNameWithoutExt + "_" + schema->getName() + "_\" + " + id_string_name + ";",
      "return LocalizationHelper::getLocalization(localId);"
    }, 0);
    descFunction->addBodyStatements( descriptState_1 + getSchemaFuncName + "() " + descriptState_3);
    cppClass->addFunction(getSchemaFunc, false);
    return;
  }
  if (type == ICON) {
    string getIconFuncName = getSchemaFuncName; // getGoodsIconId
    getIconFuncName = getIconFuncName.substr(0, getIconFuncName.length() - 2);  // getGoodsIcon
    auto varIsDefault = new CPPVariable("isDefaultSize", TYPE_BOOL);
    varIsDefault->setInitialValue("true");
    auto getIconFunction = new CPPFunction(getIconFuncName, "cocos2d::Sprite*", {varIsDefault}, false, false);
    getIconFunction->addBodyStatementsList({
      "static const string s_basePath = \"" + schema->getSubtype() + "\";",
      "string path = s_basePath + " + schemaName + ";",
      "auto icon = cocos2d::Sprite::create(path);",
      "if (!isDefaultSize) {",
      "\ticon->setScale(cocos2d::Director::getInstance()->getContentScaleFactor());", "}",
      "return icon;"
      
    }, 0);
    cppClass->addFunction(getIconFunction, false);
  } if (type == MUSIC || type == EFFECT) {
    string getIconFuncName = getSchemaFuncName; // getMusicId
    getIconFuncName = getIconFuncName.substr(0, getIconFuncName.length() - 2) + "Path";  // getMusicPath
    auto getIconFunction = new CPPFunction(getIconFuncName, TYPE_STRING);
    getIconFunction->addBodyStatementsList({
      "static const string s_basePath = \"" + schema->getSubtype() + "\";",
      "return s_basePath + " + schemaName + ";",
      
    }, 0);
    cppClass->addFunction(getIconFunction, false);
    
  } else if (type == FRIEND_ID) {
    string friendClassName = schema->getSubtype() + "Data";
    cppFile->addHeaders(friendClassName + ".hpp", true, true);
    auto getFriendDataFunc = new CPPFunction("get" + friendClassName, friendClassName + "*");
    getFriendDataFunc->addBodyStatements("return " + friendClassName + "::get" + friendClassName + "ById(" + schemaName +");");
    cppClass->addFunction(getFriendDataFunc, false);
  }
  string descriptState_2 = "to_string(" + schemaName + ") ";
  string finalType;
  switch (type) {
    case ID:
      // Never set ID
      assert(!schema->isWritable());
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
      finalType = TYPE_VECTOR(schema->getSubtype());
      break;
    }
    case SET: {
      finalType = TYPE_SET(schema->getSubtype());
      break;
    }
    default:
      // unknow type
      assert(false);
      break;
  }
  
  if (finalType.length() > 0) {
    getSchemaFunc = new CPPFunction(getSchemaFuncName, finalType);
    cppClass->addVariable(schemaName, finalType, true);
    getSchemaFunc->addBodyStatements("return " + schemaName + ";");
    cppClass->addFunction(getSchemaFunc, false);
    // todo: need release data
    //            delete getSchemaFunc;
    if (schema->isWritable()) {
      setSchemaFunc = new CPPFunction(setSchemaFuncName, TYPE_VOID, {new CPPVariable(schema->getName(), finalType)}, false, false);
      setSchemaFunc->addBodyStatements(schemaName + " = " + schema->getName() + ";");
      cppClass->addFunction(setSchemaFunc, false);
    }
  }
  
  descFunction->addBodyStatements( descriptState_1 + descriptState_2 + descriptState_3);
  addReadDataFunctionBody(initFunction, variableName, schema, 3);
}

void ExcelData::setInitFunction(const string &className, CPPClass *cppClass, CPPFileComplete *cppFile) const
{
  std::locale loc;
  string variableName = className;
  variableName[0] = tolower(variableName[0], loc); // goodsData
  string classTypeName = className + "*";     // GoodsData*
  string mapDicType = "map<string, " + classTypeName + ">";
  string mapDicPointerType = mapDicType + "*";
  bool containLanguage = false;
  bool containSet = false;
  bool containVector = false;
  int needSaveDataNumber = 0;
  string staticMapName = "p_sharedDictionary";
  auto staticMapVariable = new CPPVariable(staticMapName, mapDicPointerType, true);
  staticMapVariable->setInitialValue("nullptr");
  cppClass->addVariable(staticMapVariable, true);
  
  auto initFunction = new CPPFunction("getSharedDictionary", mapDicPointerType, true);
  auto descFunction = new CPPFunction("description", TYPE_STRING);
  descFunction->addBodyStatements("string desc = \"" + variableName + " = {\\n\";");
  const string filePath = "res/base/data/" + p_resDataFileName;
  initFunction->addBodyStatementsList({
    "if (!" + staticMapName + ") {"
    
  }, 0);
  initFunction->addBodyStatementsList({
    staticMapName + " = new " + mapDicType + "();",
    "static string resPath = \"" + filePath + "\";",
    "auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(resPath);",
    "if (!data.isNull()) {",
  }, 1);
  initFunction->addBodyStatementsList({
    "auto bytes = data.getBytes();",
    "auto buffer = make_unique<bb::ByteBuffer>(bytes, data.getSize());",
    "auto count = buffer->getLong();",
    "for (int i = 0; i < count; ++i) {"
  }, 2);
  initFunction->addBodyStatements(classTypeName + " " + variableName + " = new " + className + "();", 3);
  string id_schema_name;  // goodsId;
  string fileNameWithoutExt = p_resDataFileName.substr(0, p_resDataFileName.find_last_of("."));
  for (auto schema : p_dataSchemas) {
    if (schema->getType() == ID) {
      id_schema_name = schema->getName();
    } else if (schema->getType() == LANGUAGE) {
      containLanguage = true;
    } else if (schema->getType() == VECTOR) {
      containVector = true;
    } else if (schema->getType() == SET) {
      containSet = true;
    }
    if (schema->isWritable()) {
      needSaveDataNumber++;
    }
  }
  if (containLanguage) {
    cppFile->addHeaders("LocalizationHelper.hpp", false, false);
  }
  if (containSet) {
    cppFile->addHeaders("unordered_set", false, true);
  }
  if (containVector) {
    cppFile->addHeaders("vector", false, true);
  }
  
  for (auto schema : p_dataSchemas) {
    setPublicGetFunction(cppClass, schema, id_schema_name, fileNameWithoutExt, descFunction, cppFile, initFunction, variableName);
  }
  
  descFunction->addBodyStatements("desc += \"}\\n\";");
  descFunction->addBodyStatements("return desc;");
  cppClass->addFunction(descFunction, false);
  
  string id_string_name = "p_" + id_schema_name;  // p_goodsId;
  initFunction->addBodyStatements(staticMapName + "->insert(pair<string, " + classTypeName+ ">("+ variableName + "->"+ id_string_name +", " + variableName +"));", 3);
  initFunction->addBodyStatements("}", 2);
  initFunction->addBodyStatements("}", 1);
  initFunction->addBodyStatements("}");
  initFunction->addBodyStatements("return " + staticMapName + ";");
  cppClass->addFunction(initFunction, false);
  
  string retrieveFuncName = "get" + className + "ById";
  auto retrieveArg = new CPPVariable(id_schema_name, "const string&");
  auto retrieveFunc = new CPPFunction(retrieveFuncName, classTypeName, {retrieveArg}, true, false);
  retrieveFunc->addBodyStatementsList({
    make_pair("if (" + className + "::getSharedDictionary()->count(" + id_schema_name + ")) {", 0),
    make_pair("return " + className + "::getSharedDictionary()->at(" + id_schema_name + ");", 1),
    make_pair("}", 0),
    make_pair("CCLOGERROR(\"invalid " + id_schema_name + " %s\", " + id_schema_name + ".c_str());", 0),
    make_pair("return nullptr;", 0),
  });
  cppClass->addFunction(retrieveFunc, false);
  
  /// save, load && clear
  if (needSaveDataNumber > 0) {
    auto pathVar = new CPPVariable("path", "const string &");
    auto saveFunc = new CPPFunction("saveData", TYPE_BOOL, {pathVar}, true, false);
    auto loadFunc = new CPPFunction("loadData", TYPE_BOOL, {pathVar}, true, false);
    
    string fistLine = "auto filePath = path + \"/" + getClassName() + ".dat\";";
    string secondLine = "auto dict = " + getClassName() + "::getSharedDictionary();";
    saveFunc->addBodyStatementsList({
      fistLine,
      secondLine,
      "auto buffer = make_unique<bb::ByteBuffer>();",
      "buffer->putLong(dict->size());",
      "buffer->putInt(" + to_string(needSaveDataNumber) + ");",
      "for (auto iter = dict->begin(); iter != dict->end(); iter++) {"
    }, 0);
    saveFunc->addBodyStatementsList({
      "auto dataId = iter->first;",
      "auto data = iter->second;",
      "buffer->putString(dataId);",
    }, 1);

    loadFunc->addBodyStatementsList({
      fistLine,
      secondLine,
      "auto fileData = cocos2d::FileUtils::getInstance()->getDataFromFile(filePath);",
      "if (!fileData.isNull()) {",
    }, 0);
    loadFunc->addBodyStatementsList({
      "auto bytes = fileData.getBytes();",
      "auto buffer = make_unique<bb::ByteBuffer>(bytes, fileData.getSize());",
      "auto size = buffer->getLong();",
      "auto dataSize = buffer->getInt();",
      "for (int i = 0; i < size; ++i) {",
    }, 1);
    loadFunc->addBodyStatementsList({
      "string dataId = buffer->getString();",
      getClassName() + " *data = nullptr;",
      "if (dict->count(dataId)) {",
      "\tdata = dict->at(dataId);",
      "}", "for (int j = 0; j < dataSize; ++j) {",
      "\tstring key = buffer->getString();",
      "\tstring value = buffer->getString();",
      "\tif (data != nullptr) {",
      
    }, 2);
    int count = 0;
    for (auto schema : p_dataSchemas) {
      if (schema->isWritable()) {
        saveFunc->addBodyStatementsList({
          "buffer->putString(\"" + schema->getName() + "\");",
          "buffer->putString(to_string(data->p_" + schema->getName() + "));",
        }, 1);
        string start = count > 0 ? "} else " : "";
        loadFunc->addBodyStatementsList({
          start + "if (key == \"" + schema->getName() + "\") {",
          "\tdata->p_" + schema->getName() + " = " + castFromStringToValue(schema->getType(), "value") + ";",
        }, 4);
        count++;
      }
    }
    
    loadFunc->addBodyStatementsList({
      "\t\t\t\t}","\t\t\t}", "\t\t}", "\t}", "}", "return true;"
    }, 0);
    
    saveFunc->addBodyStatementsList({
      "}","buffer->writeToFile(filePath);", "return true;",
    }, 0);
    cppClass->addFunction(saveFunc, false);
    cppClass->addFunction(loadFunc, false);
    // clear data
    auto clearFunc = new CPPFunction("clearData", TYPE_BOOL, {}, true, false);
    clearFunc->addBodyStatementsList({
      "if (" + staticMapName + " != nullptr) {",
      "\tfor (auto iter = " + staticMapName + "->begin(); iter != " + staticMapName + "->end(); ++iter) {",
      "\t\tauto data = iter->second;",
      "\t\tdelete data;",
      "\t}",
      "\tdelete " + staticMapName + ";",
      "\t" + staticMapName + " = nullptr;",
      "}",
      "return true;",
    }, 0);
    cppClass->addFunction(clearFunc, false);
    
  }
}

bool invalidChar (char c)
{
  return !isprint( static_cast<unsigned char>( c ) );
}

ExcelData* ExcelData::createWithPath(const string &filePath)
{
  ExcelData* data = new ExcelData();
  data->p_filePath = filePath;
  
  auto excelData = readCVSBylines(filePath);
  // First four lines are defines.
  assert(excelData.size() >= 4);
  auto names = excelData.at(0);
  auto types = excelData.at(1);
  auto subtypes = excelData.at(2);
  auto writables = excelData.at(3);
  assert(names.size() == types.size() && types.size() == subtypes.size() && types.size() == writables.size());
  for (int i = 0; i < names.size(); ++i) {
    string schemaName = names[i];
    string schemaType = types[i];
    string writable = writables[i];
    schemaName.erase(remove_if(schemaName.begin(),schemaName.end(), invalidChar), schemaName.end());
    schemaType.erase(remove_if(schemaType.begin(),schemaType.end(), invalidChar), schemaType.end());
    writable.erase(remove_if(writable.begin(),writable.end(), invalidChar), writable.end());
    DataSchema* schema = new DataSchema(schemaName, schemaType, subtypes[i], toupper(writable.at(0)) == 'Y');
    data->p_dataSchemas.push_back(schema);
  }
  
  for (int rowIndex = 4; rowIndex < excelData.size(); ++rowIndex) {
    auto row = excelData.at(rowIndex);
    data->p_values.push_back(row);
  }
  
  return data;
}

