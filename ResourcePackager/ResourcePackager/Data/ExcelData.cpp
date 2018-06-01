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

string ExcelData::getFilePath() const
{
    return p_filePath;
}

vector<DataSchema*> ExcelData::getDataSchemas() const
{
    return p_dataSchemas;
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
                    // TODO
                    break;
                case COMMENT:
                    // TODO
                    break;
                default:
                    break;
            }
        }
    }
    utils::writeBufferToFile(buffer, folderPath, fileName);
    p_resDataFileName = fileName;
}


void ExcelData::generateCode(const string& folderPath, const string& fileName) const
{
    std::locale loc;
    string first_capital_file_name = fileName;
    first_capital_file_name[0] = toupper(fileName[0], loc);
    string dataFileName = first_capital_file_name + "Data";
    CPPFileComplete* file = new CPPFileComplete(dataFileName);
    file->addHeaders("unordered_map", false, true);
    file->addHeaders("cocos2d.h", true, false);
    file->addHeaders("ByteBuffer.hpp", true, false);
    CPPClass *cppClass = new CPPClass(dataFileName);
    this->setInitFunction(dataFileName, cppClass, file);
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
    string mapDicType = "unordered_map<string, " + classTypeName + ">";
    string mapDicPointerType = mapDicType + "*";
    bool containLanguage = false;
    
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
        string st = variableName + "->" + schemaName + " = buffer->";
        string descriptState_2;
        switch (schema->getType()) {
            case ID:
                id_string_name = schemaName;
                id_schema_name = schema->getName();
            case FRIEND_ID:
            case ICON:
            case STRING:
                st += "getString();";
                getSchemaFunc = new CPPFunction(getSchemaFuncName, TYPE_STRING);
                cppClass->addVariable(schemaName, TYPE_STRING, true);
                descriptState_2 = schemaName;
                break;
            case INT:
                cppClass->addVariable(schemaName, TYPE_INT, true);
                getSchemaFunc = new CPPFunction(getSchemaFuncName, TYPE_INT);
                st += "getInt();";
                descriptState_2 = "to_string(" + schemaName + ") ";
                break;
            case FLOAT:
                getSchemaFunc = new CPPFunction(getSchemaFuncName, TYPE_FLOAT);
                cppClass->addVariable(schemaName, TYPE_FLOAT, true);
                st += "getInt();";
                descriptState_2 = "to_string(" + schemaName + ") ";
            case LONG:
                getSchemaFunc = new CPPFunction(getSchemaFuncName, TYPE_LONG);
                cppClass->addVariable(schemaName, TYPE_LONG, true);
                descriptState_2 = "to_string(" + schemaName + ") ";
                st += "getLong();";
            case DOUBLE:
                getSchemaFunc = new CPPFunction(getSchemaFuncName, TYPE_DOUBLE);
                cppClass->addVariable(schemaName, TYPE_DOUBLE, true);
                st += "getDouble();";
                descriptState_2 = "to_string(" + schemaName + ") ";
            case BOOL:
                getSchemaFunc = new CPPFunction(getSchemaFuncName, TYPE_BOOL);
                cppClass->addVariable(schemaName, TYPE_BOOL, true);
                st += "getChar();";
                descriptState_2 = "to_string(" + schemaName + ") ";
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
        initFunction->addBodyStatements(st, 3);
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
    retrieveFunc->addBodyStatements("return " + className + "::getSharedDictionary()->at(" + id_schema_name + ");");
    cppClass->addFunction(retrieveFunc, false);
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
    assert(excelData.size() >= 3);
    auto names = excelData.at(0);
    auto types = excelData.at(1);
    auto subtype = excelData.at(2);
    assert(names.size() == types.size() && types.size() == subtype.size());
    for (int i = 0; i < names.size(); ++i) {
        string schemaName = names[i];
        string schemaType = types[i];
        schemaName.erase(remove_if(schemaName.begin(),schemaName.end(), invalidChar), schemaName.end());
        schemaType.erase(remove_if(schemaType.begin(),schemaType.end(), invalidChar), schemaType.end());
        DataSchema* schema = new DataSchema(schemaName, schemaType, subtype[i]);
        data->p_dataSchemas.push_back(schema);
    }
    
    for (int rowIndex = 3; rowIndex < excelData.size(); ++rowIndex) {
        auto row = excelData.at(rowIndex);
        data->p_values.push_back(row);
    }
    
    return data;
}
