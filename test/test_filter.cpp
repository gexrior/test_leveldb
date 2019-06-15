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

#include "util.cpp"


int main() {
    leveldb::DB *db;
    leveldb::Options options;
    options.create_if_missing = true;
    options.comparator = leveldb::NumberComparator();
    std::string dbname_ = "/home/rrzhang/WorkSpace/Jetbrains/CLionProjects/test_leveldb/sst";
    leveldb::Status status = leveldb::DB::Open(options, dbname_, &db);

    // 打开文件号为 4 的 table
    leveldb::FileMetaData *fileMetaData = GetTargetFile(6, db);
    std::cout<< fileMetaData->number<<std::endl;
    std::string fname = leveldb::TableFileName(dbname_, fileMetaData->number);
    leveldb::RandomAccessFile *read_file = nullptr;
    leveldb::Table *table = nullptr;
    options.env->NewRandomAccessFile(fname, &read_file);
    status = leveldb::Table::Open(options, read_file, fileMetaData->file_size, &table);

    std::cout << table->KeyInTable(leveldb::ReadOptions(), "97882");

    delete db;
    return 0;
}
