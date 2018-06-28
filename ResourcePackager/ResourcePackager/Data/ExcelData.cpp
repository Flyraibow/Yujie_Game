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
  file->addHeaders("unordered_map", false, true);
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

void ExcelData::setInitFunction(const string &className, CPPClass *cppClass, CPPFileComplete *cppFile) const
{
  std::locale loc;
  string variableName = className;
  variableName[0] = tolower(variableName[0], loc); // goodsData
  string classTypeName = className + "*";     // GoodsData*
  string mapDicType = "unordered_map<string, " + classTypeName + ">";
  string mapDicPointerType = mapDicType + "*";
  bool containLanguage = false;
  bool containSet = false;
  bool containVector = false;
  
  auto initFunction = new CPPFunction("getSharedDictionary", mapDicPointerType, true);
  auto descFunction = new CPPFunction("description", TYPE_STRING);
  descFunction->addBodyStatements("string desc = \"" + variableName + " = {\\n\";");
  const string filePath = "res/base/data/" + p_resDataFileName;
  initFunction->addBodyStatementsList({
    "static " +  mapDicPointerType + " sharedDictionary = nullptr;",
    "if (!sharedDictionary) {"
    
  }, 0);
  initFunction->addBodyStatementsList({
    "sharedDictionary = new " + mapDicType + "();",
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
  string id_string_name;  // p_goodsId;
  string id_schema_name;  // goodsId;
  for (auto schema : p_dataSchemas) {
    auto type = schema->getType();
    if (type == COMMENT || type == VECTOR) {
      // skip comment and vector
      continue;
    }
    string schemaName = "p_" + schema->getName(); // p_goodsId
    string getSchemaFuncName = schema->getName();
    getSchemaFuncName[0] = toupper(getSchemaFuncName[0], loc);
    getSchemaFuncName = "get" + getSchemaFuncName;  // getGoodsId
    CPPFunction *getSchemaFunc = nullptr;
    string descriptState_1 = "desc += \"\\t" + schema->getName() + " : \" + ";
    string descriptState_3 = "+ \"\\n\";";
    if (type == LANGUAGE) {
      // only add function, need id before it.
      assert(id_string_name.length() > 0);
      string fileNameWithoutExt = p_resDataFileName.substr(0, p_resDataFileName.find_last_of("."));
      getSchemaFunc = new CPPFunction(getSchemaFuncName, TYPE_STRING);
      getSchemaFunc->addBodyStatementsList({
        "string localId = \"" + fileNameWithoutExt + "_" + schema->getName() + "_\" + " + id_string_name + ";",
        "return LocalizationHelper::getLocalization(localId);"
      }, 0);
      descFunction->addBodyStatements( descriptState_1 + getSchemaFuncName + "() " + descriptState_3);
      cppClass->addFunction(getSchemaFunc, false);
      
      if (!containLanguage) {
        containLanguage = true;
        cppFile->addHeaders("LocalizationHelper.hpp", false, false);
      }
      
      continue;
    }
    if (type == ICON) {
      string getIconFuncName = getSchemaFuncName; // getGoodsIconId
      getIconFuncName = getIconFuncName.substr(0, getIconFuncName.length() - 2);  // getGoodsIcon
      auto getIconFunction = new CPPFunction(getIconFuncName, "cocos2d::Sprite*");
      getIconFunction->addBodyStatementsList({
        "static const string s_basePath = \"" + schema->getSubtype() + "\";",
        "string path = s_basePath + " + schemaName + ";",
        "return cocos2d::Sprite::create(path);"
        
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
    switch (type) {
      case ID:
        id_string_name = schemaName;
        id_schema_name = schema->getName();
      case FRIEND_ID:
      case ICON:
      case MUSIC:
      case EFFECT:
      case STRING:
        getSchemaFunc = new CPPFunction(getSchemaFuncName, TYPE_STRING);
        cppClass->addVariable(schemaName, TYPE_STRING, true);
        break;
      case INT:
        cppClass->addVariable(schemaName, TYPE_INT, true);
        getSchemaFunc = new CPPFunction(getSchemaFuncName, TYPE_INT);
        break;
      case FLOAT:
        getSchemaFunc = new CPPFunction(getSchemaFuncName, TYPE_FLOAT);
        cppClass->addVariable(schemaName, TYPE_FLOAT, true);
      case LONG:
        getSchemaFunc = new CPPFunction(getSchemaFuncName, TYPE_LONG);
        cppClass->addVariable(schemaName, TYPE_LONG, true);
      case DOUBLE:
        getSchemaFunc = new CPPFunction(getSchemaFuncName, TYPE_DOUBLE);
        cppClass->addVariable(schemaName, TYPE_DOUBLE, true);
      case BOOL:
        getSchemaFunc = new CPPFunction(getSchemaFuncName, TYPE_BOOL);
        cppClass->addVariable(schemaName, TYPE_BOOL, true);
      case VECTOR: {
        string vectorType = TYPE_VECTOR(schema->getSubtype());
        getSchemaFunc = new CPPFunction(getSchemaFuncName, vectorType);
        cppClass->addVariable(schemaName, vectorType, true);
        if (!containVector) {
          containVector = true;
          cppFile->addHeaders("vector", false, true);
        }
        break;
      }
      case SET: {
        string vectorType = TYPE_SET(schema->getSubtype());
        getSchemaFunc = new CPPFunction(getSchemaFuncName, vectorType);
        cppClass->addVariable(schemaName, vectorType, true);
        if (!containSet) {
          containSet = true;
          cppFile->addHeaders("unordered_set", false, true);
        }
        break;
      }
      default:
        // unknow type
        assert(false);
        break;
    }
    if (getSchemaFunc != nullptr) {
      getSchemaFunc->addBodyStatements("return " + schemaName + ";");
      cppClass->addFunction(getSchemaFunc, false);
      // todo: need release data
      //            delete getSchemaFunc;
    }
    descFunction->addBodyStatements( descriptState_1 + descriptState_2 + descriptState_3);
    addReadDataFunctionBody(initFunction, variableName, schema, 3);
  }
  descFunction->addBodyStatements("desc += \"}\\n\";");
  descFunction->addBodyStatements("return desc;");
  cppClass->addFunction(descFunction, false);
  
  initFunction->addBodyStatements("sharedDictionary->insert(pair<string, " + classTypeName+ ">("+ variableName + "->"+ id_string_name +", " + variableName +"));", 3);
  initFunction->addBodyStatements("}", 2);
  initFunction->addBodyStatements("}", 1);
  initFunction->addBodyStatements("}");
  initFunction->addBodyStatements("return sharedDictionary;");
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
  
  /// save and load
  if (containWritableData()) {
    auto pathVar = new CPPVariable("path", "const string &");
    auto saveFunc = new CPPFunction("saveData", TYPE_BOOL, {pathVar}, true, false);
    saveFunc->addBodyStatements("return true;");
    auto loadFunc = new CPPFunction("loadData", TYPE_BOOL, {pathVar}, true, false);
    loadFunc->addBodyStatements("return true;");
    cppClass->addFunction(saveFunc, false);
    cppClass->addFunction(loadFunc, false);
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
  
  for (int rowIndex = 3; rowIndex < excelData.size(); ++rowIndex) {
    auto row = excelData.at(rowIndex);
    data->p_values.push_back(row);
  }
  
  return data;
}

