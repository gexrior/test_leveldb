//
// Created by rrzhang on 19-6-15.
//



#include <cassert>
#include <iostream>
#include <string>
#include <format.h>
#include "leveldb/db.h"
#include "leveldb/options.h"
#include "leveldb/env.h"
#include "leveldb/table.h"
#include "leveldb/iterator.h"

#include "db/filename.h"
#include "db/version_set.h"
#include "db/version_edit.h"
#include "db/dbformat.h"

leveldb::FileMetaData *GetTargetFile(uint64_t file_number, leveldb::DB *db) {
    leveldb::Version *current = db->GetCurrentVersion();

    for (int i = 0; i < leveldb::config::kNumLevels; i++) {
        std::vector<leveldb::FileMetaData *> files_ = current->GetFiles(i);
        for(leveldb::FileMetaData* file : files_){
            if(file_number == file->number){
                return file;
            }
        }
    }

}