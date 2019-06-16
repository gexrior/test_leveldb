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

#include "util.cpp"

void TEST_ScanTable(){
    leveldb::DB *db;
    leveldb::Options options;
    std::string db_name = DB_NAMW_WIN;
    leveldb::Status status = MyOpen(db_name, &db, options);
    assert(status.ok());

    leveldb::Table* table = nullptr;
    status = OpenFirstTable(db_name, db, options, &table);
    assert(status.ok());
    leveldb::Iterator *table_iter = table->NewIterator(leveldb::ReadOptions());
    ScanTable(table_iter);

    delete db;
}

int main() {
    TEST_ScanTable();
}
