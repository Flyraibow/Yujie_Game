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
    return m_filePath;
}

vector<DataSchema*> ExcelData::getDataSchemas() const
{
    return m_dataSchemas;
}

void ExcelData::saveData(const string& folderPath, const string& fileName, LanguageData &langData) const
{
    auto buffer = std::make_unique<bb::ByteBuffer>();
    buffer->putLong(m_values.size());
    for (int i = 0; i < m_values.size(); ++i) {
        auto row = m_values.at(i);
        string id;
        for (int j = 0; j < m_dataSchemas.size(); ++j) {
            DataSchema *schema = m_dataSchemas.at(j);
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
}


void ExcelData::generateCode(const string& folderPath, const string& fileName) const
{
    std::locale loc;
    string first_capital_file_name = fileName;
    first_capital_file_name[0] = toupper(fileName[0], loc);
    string dataFileName = first_capital_file_name + "Data";
    CPPFileComplete* file = new CPPFileComplete(dataFileName);
    file->saveFiles(folderPath, dataFileName);
    delete file;
}

ExcelData* ExcelData::createWithPath(const string &filePath)
{
    ExcelData* data = new ExcelData();
    data->m_filePath = filePath;
    
    auto excelData = readCVSBylines(filePath);
    assert(excelData.size() >= 3);
    auto names = excelData.at(0);
    auto types = excelData.at(1);
    auto subtype = excelData.at(2);
    assert(names.size() == types.size() && types.size() == subtype.size());
    for (int i = 0; i < names.size(); ++i) {
        DataSchema* schema = new DataSchema(names[i], types[i], subtype[i]);
        data->m_dataSchemas.push_back(schema);
    }
    
    for (int rowIndex = 3; rowIndex < excelData.size(); ++rowIndex) {
        auto row = excelData.at(rowIndex);
        data->m_values.push_back(row);
    }
    
    return data;
}
