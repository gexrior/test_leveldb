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
#include "leveldb/slice.h"

#include "db/filename.h"
#include "db/version_set.h"
#include "db/version_edit.h"
#include "db/dbformat.h"


#define DB_NAMW_WIN "C:\\Users\\rrzhang\\myspace\\WorkSpace\\Jetbrains\\JetbrainsCLionProjects\\test_leveldb\\sst"
#define DB_NAME_POSIX "/home/rrzhang/WorkSpace/Jetbrains/CLionProjects/test_leveldb/sst"

void PrineAllLevelFile(leveldb::DB *db) {
//    std::cout << "In PrineAllLevelFile." << std::endl;
    leveldb::Version *current = db->GetCurrentVersion();
    for (int i = 0; i < leveldb::config::kNumLevels; i++) {
        std::vector<leveldb::FileMetaData *> files_ = current->GetFiles(i);
        int num = files_.size();
        std::cout << "level " << i << ": ";
        while (num > 0) {
            std::cout << files_[files_.size() - num]->number;
            num--;
        }
        std::cout << std::endl;
    }
}

uint64_t GetFirstFileNUmber(leveldb::DB *db) {
    leveldb::Version *current = db->GetCurrentVersion();
    return current->GetFiles(0)[0]->number;
}

leveldb::FileMetaData *GetTargetFile(uint64_t file_number, leveldb::DB *db) {
//    std::cout << "In GetTargetFile. " << std::endl;
    leveldb::Version *current = db->GetCurrentVersion();
    for (int i = 0; i < leveldb::config::kNumLevels; i++) {
        std::vector<leveldb::FileMetaData *> files_ = current->GetFiles(i);
        for (leveldb::FileMetaData *file : files_) {
            if (file_number == file->number) {
                return file;
            }
        }
    }
}

leveldb::Status
OpenFirstTable(std::string db_name, leveldb::DB *db, const leveldb::Options &options, leveldb::Table **table) {
    leveldb::Status status;
    leveldb::FileMetaData *target_file = GetTargetFile(GetFirstFileNUmber(db), db);
    leveldb::RandomAccessFile *file = nullptr;
    status = options.env->NewRandomAccessFile(leveldb::TableFileName(db_name, target_file->number), &file);
    status = leveldb::Table::Open(options, file, target_file->file_size, table);

    return status;
}

leveldb::Status BuildTable_0_100000(leveldb::DB *db) {

    leveldb::Status status;
    for (int i = 0; i < 100000; i++) {
        status = db->Put(leveldb::WriteOptions(), std::to_string(i), std::to_string(i + 100000));
//        status = db->Put(leveldb::WriteOptions(), std::to_string(i), std::to_string(i));
        assert(status.ok());
    }
    std::cout << "Put entries 0-100000 successful." << std::endl;
    return status;
}

leveldb::Status MyOpen(std::string db_name, leveldb::DB **db, leveldb::Options &options) {
    bool new_db = false;

    options.comparator = leveldb::NumberComparator();
    options.filter_policy = leveldb::NewBloomFilterPolicy(10);
    leveldb::Status status = leveldb::DB::Open(options, db_name, db);
    if (!status.ok()) {
        new_db = true;
        delete (*db);
        options.create_if_missing = true;
        status = leveldb::DB::Open(options, db_name, db);
        assert(status.ok());
        status = BuildTable_0_100000(*db);
    }

    if (true == new_db) {
        delete (*db);
        status = leveldb::DB::Open(options, db_name, db);
    }

    if (status.ok() && (*db) != nullptr) {
        std::cout << "MyOpen db successful." << std::endl;
    }

    return status;
}

void ScanTable(leveldb::Iterator *table_iter) {
    table_iter->SeekToFirst();
    while (table_iter->Valid()) {
        leveldb::ParsedInternalKey ikey;
        leveldb::ParseInternalKey(table_iter->key(), &ikey);
        std::cout << "key:" << ikey.user_key.ToString();
        std::cout << "   value:" << table_iter->value().ToString() << std::endl;
        table_iter->Next();
    }
}