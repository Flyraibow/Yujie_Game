//
//  LanguageWriter.cpp
//  ResourcePackager
//
//  Created by Yujie Liu on 5/16/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#include "LanguageWriter.hpp"
#include "ByteBuffer.hpp"
#include "Utils.hpp"

using namespace std;

void LanguageWriter::writeLanguageData(const LanguageData &data, const std::string &path)
{
    auto dict = data.get_dictionary();
    for (auto lang = dict.begin(); lang != dict.end(); ++lang) {
        string language = lang->first;
        auto dic = lang->second;
        const string filename = language + ".lang";
        auto buffer = std::make_unique<bb::ByteBuffer>();
        buffer->putLong(dic.size());
        for (auto localData = dic.begin(); localData != dic.end(); ++localData) {
            auto localId = localData->first;
            auto localTrans = localData->second;
            buffer->putString(localId);
            buffer->putString(localTrans);
            cout<< localId << " -> " << localTrans << endl;
        }
        cout << dic.size() << endl;
        utils::writeBufferToFile(buffer, path, filename);
    }
}
