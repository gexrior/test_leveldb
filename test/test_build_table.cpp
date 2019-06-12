// Created by rrzhang on 19-6-12.
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

//using namespace leveldb;

leveldb::Status BuildTable(std::string const &fname, leveldb::Options const &options, uint64_t &file_size) {
    // 每个data block只有两个 entries

    leveldb::Status status;
    leveldb::WritableFile *outfile;
    status = options.env->NewWritableFile(fname, &outfile);
    leveldb::TableBuilder *builder = new leveldb::TableBuilder(options, outfile);

    std::string keys[] = {
            "the person", "the quick", "the reason", "the who", "the whose", "the zoo"
    };
    for (int i = 0; i < 6; i++) {
        uint64_t s = i;
        leveldb::InternalKey ikey(keys[i], s, leveldb::kTypeValue);
        builder->Add(ikey.Encode(), std::to_string(i));
    }
//    for (int i = 0; i < 10000; i++) {
//        uint64_t s = i;
//        leveldb::InternalKey ikey(std::to_string(i), s, leveldb::kTypeValue);
//        builder->Add(ikey.Encode(), std::to_string(i));
//    }
    builder->Finish();
    file_size = builder->FileSize();

    outfile->Sync();
    outfile->Close();

    delete outfile;
    delete builder;

    return status;
}

int main() {
    leveldb::Options options;
//    options.comparator = leveldb::NumberComparator();
    leveldb::Status status;
    std::string dbname_ = "/home/rrzhang/WorkSpace/Jetbrains/CLionProjects/test_leveldb/sst";

    uint64_t file_number = 111111;
    uint64_t file_size;
    std::string fname = leveldb::TableFileName(dbname_, file_number);
//
    status = BuildTable(fname, options, file_size);
    assert(status.ok());
    std::cout << " BuildTable ok" << std::endl;

// table->open
    leveldb::RandomAccessFile *file = nullptr;
    leveldb::Table *table = nullptr;
    options.env->NewRandomAccessFile(fname, &file);
    status = leveldb::Table::Open(options, file, file_size, &table);
    assert(status.ok());

//输出 index block 值
    leveldb::Iterator *iiter = table->GetIndexIterator();
    iiter->SeekToFirst();
    while (iiter->Valid()) {
        leveldb::ParsedInternalKey ikey;
        leveldb::ParseInternalKey(iiter->key(), &ikey);
        std::cout << "key_size : " << ikey.user_key.ToString().size() << "   key:" << ikey.user_key.ToString() ;
        leveldb::Slice handle = iiter->value();
        leveldb::BlockHandle bh;
        bh.DecodeFrom(&handle);
        std::cout << "   offset : " << bh.offset() << "   size : " << bh.size() << std::endl;
        iiter->Next();
    }

    leveldb::Iterator *result = table->NewIterator(leveldb::ReadOptions());
// 输出所有 data block 值
    result->SeekToFirst();
    while (result->Valid()) {
        leveldb::ParsedInternalKey ikey;
        leveldb::ParseInternalKey(result->key(), &ikey);
        std::cout << "key:" << ikey.user_key.ToString();
        std::cout << "   value:" << result->value().ToString() << std::endl;
        result->Next();
    }

    delete table;
    delete iiter;
    delete result;
}