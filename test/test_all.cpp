//
// Created by rrzhang on 2019/6/17.
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

std::string db_name = DB_NAMW_WIN;

void TEST_ScanTable(){
    leveldb::DB *db;
    leveldb::Options options;
    leveldb::Status status = MyOpen(db_name, &db, options);
    assert(status.ok());

    leveldb::Table* table = nullptr;
    status = OpenFirstTable(db_name, db, options, &table);
    assert(status.ok());
    leveldb::Iterator *table_iter = table->NewIterator(leveldb::ReadOptions());
    ScanTable(table_iter);

    delete db;
}

// 需要指定 bloomfilter, 且数据库需要重新建立。
// table/table_builder.cc 中 add() 函数做了相应修改
void TEST_Filter(){
    DeleteFile(db_name.data());

    leveldb::DB *db;
    leveldb::Options options;
    options.filter_policy = leveldb::NewBloomFilterPolicy(10); // 指定 bloomfilter
    leveldb::Status status = MyOpen(db_name, &db, options);
    assert(status.ok());

    std::cout << "filter name : " << options.filter_policy->Name() << std::endl;

// 打开第一个 table
    leveldb::Table *table = nullptr;
    OpenFirstTable(db_name, db, options, &table);

// 获取第一个 table 的第一个 key,value
// user_key:0, user_value:100000
    std::string key;
    std::string value;
    GetFirstEntry(table, &key, &value);

    bool flag = ValueInTable(table, value);
    std::cout << (true == flag ? "TEST_Filter success" : "TEST_Filter failed")<<std::endl;
}

// 测试每个 table 中最大最小 key
void TEST_ReadSmallAndLargerest(){
    leveldb::DB *db;
    leveldb::Options options;
    leveldb::Status status = MyOpen(db_name, &db, options);
    assert(status.ok());

    leveldb::Version *current = db->GetCurrentVersion();
    for(int i = 0; i< 7;i++){
        std::vector<leveldb::FileMetaData *> files_ = current->GetFiles(i);
        if (files_.size() > 0) {
            for (int i = 0; i < files_.size(); i++) {
                std::cout << files_[i]->number << " ";
                std::cout << files_[i]->smallest.user_key().ToString() << " ";
                std::cout << files_[i]->largest.user_key().ToString() << std::endl;
            }
        }
    }
}

int main(){
    void (*p)(void);
    p = TEST_Filter;
    p();

    DeleteFile(db_name.data());
    return 0;
}