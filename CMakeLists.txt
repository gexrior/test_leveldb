cmake_minimum_required(VERSION 3.14)
project(test_leveldb)

set(CMAKE_CXX_STANDARD 11)

include_directories(db)
include_directories(helpers/memenv)
include_directories(include)
include_directories(include/leveldb)
include_directories(include/port)
include_directories(port)
include_directories(table)
include_directories(util)

include_directories(
        "${PROJECT_BINARY_DIR}/include"
        "${PROJECT_SOURCE_DIR}"
)

add_executable(db_bench
        #        db/autocompact_test.cc
        #        db/c_test.c
        #        db/corruption_test.cc
        #        db/fault_injection_test.cc
        #        db/db_test.cc
        #        db/dbformat_test.cc
        #        util/status_test.cc
        #        util/testharness.cc
        #        util/testharness.h
        #        db/filename_test.cc
        #        db/leveldbutil.cc
        #        db/filename_test.cc
        #        db/leveldbutil.cc
        #        table/filter_block_test.cc
        #        table/table_test.cc
        #        util/bloom_test.cc
        #        util/coding_test.cc
        #        util/cache_test.cc
        #        util/arena_test.cc
        #        util/env_posix_test.cc
        #        util/env_posix_test_helper.h
        #        util/env_test.cc
        #        util/env_windows.cc
        #        util/env_windows_test.cc
        #        util/env_windows_test_helper.h
        #        util/crc32c_test.cc
        #        util/no_destructor_test.cc
        #        util/hash_test.cc
        #        util/logging_test.cc
        #        util/testutil.cc
        #        util/windows_logger.h
        #        db/log_test.cc
        #        db/recovery_test.cc
        #        db/version_edit_test.cc
        #        db/version_set_test.cc
        #        db/skiplist_test.cc
        #        db/write_batch_test.cc
        #        doc/bench/db_bench_sqlite3.cc
        #        doc/bench/db_bench_tree_db.cc
        #        issues/issue178_test.cc
        #        issues/issue200_test.cc
        #        helpers/memenv/memenv_test.cc


        db/builder.cc
        db/builder.h
        db/c.cc
        db/db_impl.cc
        db/db_impl.h
        db/db_iter.cc
        db/db_iter.h
        db/dbformat.cc
        db/dbformat.h
        db/dumpfile.cc
        db/filename.cc
        db/filename.h
        db/log_format.h
        db/log_reader.cc
        db/log_reader.h
        db/log_writer.cc
        db/log_writer.h
        db/memtable.cc
        db/memtable.h
        db/repair.cc
        db/skiplist.h
        db/snapshot.h
        db/table_cache.cc
        db/table_cache.h
        db/version_edit.cc
        db/version_edit.h
        db/version_set.cc
        db/version_set.h
        db/write_batch.cc
        db/write_batch_internal.h
        helpers/memenv/memenv.cc
        helpers/memenv/memenv.h
        include/leveldb/c.h
        include/leveldb/cache.h
        include/leveldb/comparator.h
        include/leveldb/db.h
        include/leveldb/dumpfile.h
        include/leveldb/env.h
        include/leveldb/export.h
        include/leveldb/filter_policy.h
        include/leveldb/iterator.h
        include/leveldb/options.h
        include/leveldb/slice.h
        include/leveldb/status.h
        include/leveldb/table.h
        include/leveldb/table_builder.h
        include/leveldb/write_batch.h
        include/port/port_config.h
        port/port.h
        port/port_example.h
        port/port_stdcxx.h
        port/thread_annotations.h
        table/block.cc
        table/block.h
        table/block_builder.cc
        table/block_builder.h
        table/filter_block.cc
        table/filter_block.h
        table/format.cc
        table/format.h
        table/iterator.cc
        table/iterator_wrapper.h
        table/merger.cc
        table/merger.h
        table/table.cc
        table/table_builder.cc
        table/two_level_iterator.cc
        table/two_level_iterator.h
        util/arena.cc
        util/arena.h
        util/bloom.cc
        util/cache.cc
        util/coding.cc
        util/coding.h
        util/comparator.cc
        util/crc32c.cc
        util/crc32c.h
        util/env.cc
        util/env_posix.cc
        util/filter_policy.cc
        util/hash.cc
        util/hash.h
        util/histogram.cc
        util/histogram.h
        util/logging.cc
        util/logging.h
        util/mutexlock.h
        util/no_destructor.h
        util/options.cc
        util/posix_logger.h
        util/random.h
        util/status.cc
        util/testutil.h

        db/db_bench.cc
        )
# 改写了 table/table_builder, 重新写了个放在 test/table_builder,对应测试文件文 test_build_table
add_executable(test_build_table
        db/builder.cc
        db/builder.h
        db/c.cc
        db/db_impl.cc
        db/db_impl.h
        db/db_iter.cc
        db/db_iter.h
        db/dbformat.cc
        db/dbformat.h
        db/dumpfile.cc
        db/filename.cc
        db/filename.h
        db/log_format.h
        db/log_reader.cc
        db/log_reader.h
        db/log_writer.cc
        db/log_writer.h
        db/memtable.cc
        db/memtable.h
        db/repair.cc
        db/skiplist.h
        db/snapshot.h
        db/table_cache.cc
        db/table_cache.h
        db/version_edit.cc
        db/version_edit.h
        db/version_set.cc
        db/version_set.h
        db/write_batch.cc
        db/write_batch_internal.h
        helpers/memenv/memenv.cc
        helpers/memenv/memenv.h
        include/leveldb/c.h
        include/leveldb/cache.h
        include/leveldb/comparator.h
        include/leveldb/db.h
        include/leveldb/dumpfile.h
        include/leveldb/env.h
        include/leveldb/export.h
        include/leveldb/filter_policy.h
        include/leveldb/iterator.h
        include/leveldb/options.h
        include/leveldb/slice.h
        include/leveldb/status.h
        include/leveldb/table.h
        include/leveldb/table_builder.h
        include/leveldb/write_batch.h
        include/port/port_config.h
        port/port.h
        port/port_example.h
        port/port_stdcxx.h
        port/thread_annotations.h
        table/block.cc
        table/block.h
        table/block_builder.cc
        table/block_builder.h
        table/filter_block.cc
        table/filter_block.h
        table/format.cc
        table/format.h
        table/iterator.cc
        table/iterator_wrapper.h
        table/merger.cc
        table/merger.h
        table/table.cc
        #        table/table_builder.cc
        test/table_builder.cc
        table/two_level_iterator.cc
        table/two_level_iterator.h
        util/arena.cc
        util/arena.h
        util/bloom.cc
        util/cache.cc
        util/coding.cc
        util/coding.h
        util/comparator.cc
        util/crc32c.cc
        util/crc32c.h
        util/env.cc
        util/env_posix.cc
        util/filter_policy.cc
        util/hash.cc
        util/hash.h
        util/histogram.cc
        util/histogram.h
        util/logging.cc
        util/logging.h
        util/mutexlock.h
        util/no_destructor.h
        util/options.cc
        util/posix_logger.h
        util/random.h
        util/status.cc
        util/testutil.h

        test/test_build_table.cpp
        )

add_executable(test_all
        db/builder.cc
        db/builder.h
        db/c.cc
        db/db_impl.cc
        db/db_impl.h
        db/db_iter.cc
        db/db_iter.h
        db/dbformat.cc
        db/dbformat.h
        db/dumpfile.cc
        db/filename.cc
        db/filename.h
        db/log_format.h
        db/log_reader.cc
        db/log_reader.h
        db/log_writer.cc
        db/log_writer.h
        db/memtable.cc
        db/memtable.h
        db/repair.cc
        db/skiplist.h
        db/snapshot.h
        db/table_cache.cc
        db/table_cache.h
        db/version_edit.cc
        db/version_edit.h
        db/version_set.cc
        db/version_set.h
        db/write_batch.cc
        db/write_batch_internal.h
        helpers/memenv/memenv.cc
        helpers/memenv/memenv.h
        include/leveldb/c.h
        include/leveldb/cache.h
        include/leveldb/comparator.h
        include/leveldb/db.h
        include/leveldb/dumpfile.h
        include/leveldb/env.h
        include/leveldb/export.h
        include/leveldb/filter_policy.h
        include/leveldb/iterator.h
        include/leveldb/options.h
        include/leveldb/slice.h
        include/leveldb/status.h
        include/leveldb/table.h
        include/leveldb/table_builder.h
        include/leveldb/write_batch.h
        include/port/port_config.h
        port/port.h
        port/port_example.h
        port/port_stdcxx.h
        port/thread_annotations.h
        table/block.cc
        table/block.h
        table/block_builder.cc
        table/block_builder.h
        table/filter_block.cc
        table/filter_block.h
        table/format.cc
        table/format.h
        table/iterator.cc
        table/iterator_wrapper.h
        table/merger.cc
        table/merger.h
        table/table.cc
        table/table_builder.cc
        table/two_level_iterator.cc
        table/two_level_iterator.h
        util/arena.cc
        util/arena.h
        util/bloom.cc
        util/cache.cc
        util/coding.cc
        util/coding.h
        util/comparator.cc
        util/crc32c.cc
        util/crc32c.h
        util/env.cc
        util/env_posix.cc
        util/filter_policy.cc
        util/hash.cc
        util/hash.h
        util/histogram.cc
        util/histogram.h
        util/logging.cc
        util/logging.h
        util/mutexlock.h
        util/no_destructor.h
        util/options.cc
        util/posix_logger.h
        util/random.h
        util/status.cc
        util/testutil.h

        test/test_all.cpp
        )
find_package(Threads REQUIRED)
target_link_libraries(db_bench Threads::Threads)
target_link_libraries(test_build_table Threads::Threads)
target_link_libraries(test_all Threads::Threads)