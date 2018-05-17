//
//  Utils.cpp
//  ResourcePackager
//
//  Created by Yujie Liu on 5/16/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#include "Utils.hpp"
#include <fstream>
#include <cstdlib>
#include <assert.h>

using namespace std;

void write::createFolderIfNotExist(const std::string &folderPath)
{
    int err = system(("mkdir -p " + folderPath).c_str());
    assert(err == 0);
}

void write::writeBufferToFile(std::unique_ptr<bb::ByteBuffer> &buffer, const std::string &folderpath, const std::string filename)
{
    // write buffer
    createFolderIfNotExist(folderpath);
    const string path = folderpath + "/" + filename;
    auto size = buffer->size();
    ofstream outfile (path);
    uint8_t* buf = new uint8_t[size];
    buffer->getBytes(buf, size);
    char *chrs = new char[size];
    memcpy(chrs, buf, size);
    outfile.write (chrs,size);
    delete [] buf;
    delete [] chrs;
}
