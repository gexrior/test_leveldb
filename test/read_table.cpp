//
// Created by rrzhang on 19-6-10.
//

#include <cassert>
#include <iostream>
#include <string>
#include "leveldb/db.h"
#include "leveldb/options.h"
#include "leveldb/env.h"
#include "leveldb/table.h"
#include "db/filename.h"
#include "db/version_set.h"
#include "db/version_edit.h"
#include "db/dbformat.h"

int main() {
    leveldb::DB *db;
    leveldb::Options options;
    options.create_if_missing = true;
    options.comparator = leveldb::NumberComparator();
    leveldb::Status status;
    std::string dbname_ = "/home/rrzhang/WorkSpace/Jetbrains/CLionProjects/test_leveldb/sst";
    leveldb::Status status2 = leveldb::DB::Open(options, dbname_, &db);

    leveldb::Version *current = db->GetCurrentVersion();
    std::vector<leveldb::FileMetaData *> files_ = current->GetFiles(0);

    std::string fname = leveldb::TableFileName(dbname_, files_[0]->number);
    leveldb::RandomAccessFile *file = nullptr;
    leveldb::Table *table = nullptr;
    leveldb::Env *env_ = options.env;
    env_->NewRandomAccessFile(fname, &file);
    leveldb::Table::Open(options, file, files_[0]->file_size, &table);

    leveldb::Iterator *result = table->NewIterator(leveldb::ReadOptions());

    result->SeekToFirst();
    while (result->Valid()) {
        leveldb::ParsedInternalKey ikey;
        leveldb::ParseInternalKey(result->key(), &ikey);
        std::cout << "key:" << ikey.user_key.ToString();
        std::cout << "   value:" << result->value().ToString() << std::endl;
        result->Next();
    }


}