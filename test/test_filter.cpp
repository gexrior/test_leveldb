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
    std::string db_name = DB_NAMW_WIN;
    leveldb::Status status = MyOpen(db_name, &db, options);
    assert(status.ok());
    std::cout << "filter name : " << options.filter_policy->Name() << std::endl;

// 打开第一个 table
    leveldb::Table *table = nullptr;
    OpenFirstTable(db_name, db, options, &table);

// 获取第一个 table 的第一个 key,value
    leveldb::Iterator *table_iter = table->NewIterator(leveldb::ReadOptions());
    table_iter->SeekToFirst();
    std::string user_key;
    std::string user_value;
    if (table_iter->Valid()) {
        leveldb::ParsedInternalKey ikey;
        leveldb::ParseInternalKey(table_iter->key(), &ikey);
        user_key = ikey.user_key.ToString();
        user_value = table_iter->value().ToString();
        std::cout << std::endl << "first table's first entry:" << std::endl << "user_key:" << user_key << ", user_value:" << user_value << std::endl << std::endl;
    }// user_key:0, user_value:100000

//    应该找不到 key = 0 时对应的值
//    std::string get_value;
//    db->Get(leveldb::ReadOptions(), user_key, &get_value);
//    std::cout << "get_value:" << get_value << ", get_value size:" << get_value.size() << std::endl << std::endl;

    uint64_t seq = 2;
    std::string tmp_value = user_value;
    leveldb::PutFixed64(&tmp_value, seq);
    std::cout << table->ValueInTable(leveldb::ReadOptions(), tmp_value);

    delete db;
    return 0;
}
