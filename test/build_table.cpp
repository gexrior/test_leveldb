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

int main() {
    leveldb::DB *db;
    leveldb::Options options;
    options.create_if_missing = true;
    options.comparator = leveldb::NumberComparator();
    std::string dbname_ = "C:\\Users\\rrzhang\\myspace\\WorkSpace\\Jetbrains\\JetbrainsCLionProjects\\test_leveldb\\sst";
    leveldb::Status status = leveldb::DB::Open(options, dbname_, &db);

    for(int i = 0; i<100000; i++){
        status = db->Put(leveldb::WriteOptions(), std::to_string(i), std::to_string(i+100000));
        assert(status.ok());
    }

    delete db;
    return 0;
}
