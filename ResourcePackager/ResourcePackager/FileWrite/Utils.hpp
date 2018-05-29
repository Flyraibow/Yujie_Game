//
//  Utils.hpp
//  ResourcePackager
//
//  Created by Yujie Liu on 5/16/18.
//  Copyright © 2018 Yujie Liu. All rights reserved.
//

#ifndef Utils_hpp
#define Utils_hpp

#include <stdio.h>
#include "ByteBuffer.hpp"
#include <string>
#include <vector>

namespace utils {
    const static std::string CSV_EXTENSION = ".csv";

    void createFolderIfNotExist(const std::string &folderPath);
    void writeBufferToFile(std::unique_ptr<bb::ByteBuffer> &buffer, const std::string &folderpath, const std::string filename);
    std::vector<std::string> getCSVFileList(const std::string &path);
}

#endif /* Utils_hpp */
