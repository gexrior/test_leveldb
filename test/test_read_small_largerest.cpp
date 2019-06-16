#include <cassert>
#include <iostream>
#include <string>
#include "leveldb/db.h"
#include "leveldb/options.h"
#include "db/version_set.h"
#include "db/version_edit.h"

void fun(leveldb::Version *current, int level) {
    std::vector<leveldb::FileMetaData *> files_ = current->GetFiles(level);
    if (files_.size() > 0) {
        for (int i = 0; i < files_.size(); i++) {
            std::cout << files_[i]->number << " ";
            std::cout << files_[i]->smallest.user_key().ToString() << " ";
            std::cout << files_[i]->largest.user_key().ToString() << std::endl;

        }
    }
}

int main() {

    leveldb::DB *db;
    leveldb::Options options;
    options.create_if_missing = true;
    options.comparator = leveldb::NumberComparator();
    leveldb::Status status;
    std::string dbname_ = "/home/rrzhang/WorkSpace/Jetbrains/CLionProjects/test_leveldb/sst";
    status = leveldb::DB::Open(options, dbname_, &db);

//    写入数据
    for (int i = 0; i < 1000000; i++) {
        std::string key = std::to_string(i);
        std::string value = std::to_string(i);
        leveldb::Status s = db->Put(leveldb::WriteOptions(), key, value);
    }

    delete db;
    status = leveldb::DB::Open(options, dbname_, &db);
    leveldb::Version *current = db->GetCurrentVersion();
    for(int i = 0; i< 7;i++){
        fun(current, i);
    }

    return 0;
}