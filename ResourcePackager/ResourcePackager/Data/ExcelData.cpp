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

#include "ExcelParserBase.hpp"

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
  } else if (type == BOOL) {
    return "(atoi("+val+".c_str()) != 0)";
  } else if (type == SET || type == FRIEND_ID_SET) {
    return "atoset("+val+")";
  } else if (type == VECTOR || type == FRIEND_ID_VECTOR) {
    return "atoset("+val+")";
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
          if (schema->getSubtype() == TYPE_INT) {
            buffer->putInt(atoi(value.c_str()));
          } else {
            buffer->putString(value);
          }
          break;
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
        case FRIEND_ID_SET:
        case FRIEND_ID_VECTOR:
        case VECTOR:
        case SET:{
          auto subType = schema->getSubtype();
          if (schema->getType() == FRIEND_ID_SET || schema->getType() == FRIEND_ID_VECTOR) {
            subType = TYPE_STRING;
          }
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
  file->addHeaders("BaseData.h", true, true);
  file->addHeaders("cocos2d.h", true, false);
  file->addHeaders("ByteBuffer.hpp", true, false);
  file->addHeaders("Utils.hpp", true, false);
  CPPClass *cppClass = new CPPClass(p_className);
  cppClass->setFatherClass("BaseData");
  this->setInitFunction(p_className, cppClass, file);
  file->addClass(cppClass);
  file->saveFiles(folderPath);
  delete cppClass;
  delete file;
}

void ExcelData::setInitFunction(const string &className, CPPClass *cppClass, CPPFileComplete *cppFile) const
{
  std::locale loc;
  string variableName = className;
  variableName[0] = tolower(variableName[0], loc); // goodsData
  string classTypeName = className + "*";     // GoodsData*
  bool containLanguage = false;
  bool containSet = false;
  bool containVector = false;
  int needSaveDataNumber = 0;
  
  string id_schema_name;  // goodsId;
  string id_schema_type;  // int or string;
  string fileNameWithoutExt = p_resDataFileName.substr(0, p_resDataFileName.find_last_of("."));
  for (auto schema : p_dataSchemas) {
    if (schema->getType() == ID) {
      id_schema_name = schema->getName();
      id_schema_type = schema->getSubtype();
      assert(id_schema_type == TYPE_STRING || id_schema_type == TYPE_INT);
      auto getIdFunc = new CPPFunction("getId", TYPE_STRING, {}, false, true, true);
      getIdFunc->addBodyStatements("return to_string(p_" + id_schema_name + ");");
      cppClass->addFunction(getIdFunc, false);
    } else if (schema->getType() == LANGUAGE) {
      containLanguage = true;
    } else if (schema->getType() == VECTOR || schema->getType() == FRIEND_ID_VECTOR) {
      containVector = true;
    } else if (schema->getType() == SET || schema->getType() == FRIEND_ID_SET) {
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
    cppFile->addHeaders("set", false, true);
  }
  if (containVector) {
    cppFile->addHeaders("vector", false, true);
  }
  
  string staticMapName = "p_sharedDictionary";
  string mapDicType = "map<"+ id_schema_type + ", " + classTypeName + ">";
  string mapDicPointerType = mapDicType + "*";
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
  
  for (auto schema : p_dataSchemas) {
    if (schema->getType() != COMMENT) {
      auto parser = ExcelParserBase::createWithSchema(schema, id_schema_name);
      parser->setFileNameWithoutExt(fileNameWithoutExt);
      parser->addFunctionsInclass(cppClass);
      parser->addHeaders(cppFile);
      descFunction->addBodyStatements(parser->getDescription());
      parser->addInitFuncBody(initFunction);
      delete parser;
    }
  }
  
  descFunction->addBodyStatements("desc += \"}\\n\";");
  descFunction->addBodyStatements("return desc;");
  cppClass->addFunction(descFunction, false);
  
  string id_string_name = "p_" + id_schema_name;  // p_goodsId;
  initFunction->addBodyStatements(staticMapName + "->insert(pair<"+id_schema_type+", " + classTypeName+ ">("+ variableName + "->"+ id_string_name +", " + variableName +"));", 3);
  initFunction->addBodyStatements("}", 2);
  initFunction->addBodyStatements("}", 1);
  initFunction->addBodyStatements("}");
  initFunction->addBodyStatements("return " + staticMapName + ";");
  cppClass->addFunction(initFunction, false);
  
  string retrieveFuncName = "get" + className + "ById";
  CPPVariable* retrieveArg = nullptr;
  
  if (id_schema_type == TYPE_INT) {
    retrieveArg = new CPPVariable(id_schema_name, id_schema_type);
  } else {
    retrieveArg = new CPPVariable(id_schema_name, "const string&");
  }
  
  auto retrieveFunc = new CPPFunction(retrieveFuncName, classTypeName, {retrieveArg}, true, false);
  retrieveFunc->addBodyStatementsList({
    make_pair("if (" + className + "::getSharedDictionary()->count(" + id_schema_name + ")) {", 0),
    make_pair("return " + className + "::getSharedDictionary()->at(" + id_schema_name + ");", 1),
    make_pair("}", 0),
    make_pair("return nullptr;", 0),
  });
  cppClass->addFunction(retrieveFunc, false);
  
  if (id_schema_type == TYPE_INT) {
    retrieveArg = new CPPVariable(id_schema_name, "const string&");
    retrieveFunc= new CPPFunction(retrieveFuncName, classTypeName, {retrieveArg}, true, false);
    retrieveFunc->addBodyStatementsList({
      "if (" + id_schema_name + ".length() == 0) return nullptr;",
      "return " + className + "::" + retrieveFuncName + "(atoi(" + id_schema_name + ".c_str()));",
    }, 0);
    cppClass->addFunction(retrieveFunc, false);
  }
  
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
    string putID = id_schema_type == TYPE_INT ? "putInt" : "putString";
    string getID = id_schema_type == TYPE_INT ? "getInt" : "getString";
    saveFunc->addBodyStatementsList({
      "auto dataId = iter->first;",
      "auto data = iter->second;",
      "buffer->" + putID + "(dataId);",
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
      "auto dataId = buffer->" + getID +"();",
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
        auto parser = ExcelParserBase::createWithSchema(schema, id_schema_name);
        auto schemaName = parser->getVariableName();
        saveFunc->addBodyStatementsList({
          "buffer->putString(\"" + schemaName + "\");",
          "buffer->putString(to_string(data->" + schemaName + "));",
        }, 1);
        string start = count > 0 ? "} else " : "";
        loadFunc->addBodyStatementsList({
          start + "if (key == \"" + schemaName + "\") {",
          "\tdata->" + schemaName + " = " + castFromStringToValue(schema->getType(), "value") + ";",
        }, 4);
        count++;
        delete parser;
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

