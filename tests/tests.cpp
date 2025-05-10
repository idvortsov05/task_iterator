#include "core/FileIterator.h"
#include <gtest/gtest.h>

#include <QMetaType>
#include <QTemporaryDir>
#include <QSignalSpy>
#include <QtTest>
#include <QDebug>

TEST(FileIteratorTests, TestEmptyDir)
{
    qRegisterMetaType<QMap<QString, int>*>("QMap<QString, int>&");

    FileIterator iterator;
    QTemporaryDir dir;
    QSignalSpy spy(&iterator, &FileIterator::iterationFinished);
    ASSERT_TRUE(dir.isValid());

    iterator.iterate(dir.path());

    ASSERT_EQ(spy.count(), 1);

    QList<QVariant> arguments = spy.takeFirst();

    const int actual_size_dir = arguments.at(0).toInt();
    const int expected_size_dir = 0;

    const int actual_count_files = arguments.at(1).toInt();
    const int expected_count_files = 0;

    const int actual_count_dirs = arguments.at(2).toInt();
    const int expected_count_dirs = 2; // 2 потому что unix создает 2 скрытые поддиректории

    const int actual_elapsed_time = arguments.at(4).toInt();
    const int expected_elapsed_time = 0;

    EXPECT_EQ(actual_size_dir, expected_size_dir);
    EXPECT_EQ(actual_count_files, expected_count_files);
    EXPECT_EQ(actual_count_dirs, expected_count_dirs);
    EXPECT_EQ(actual_elapsed_time, expected_elapsed_time);
}

TEST(FileIteratorTests, TestSubDir)
{
    qRegisterMetaType<QMap<QString, int>*>("QMap<QString, int>&");

    QTemporaryDir tempDir;
    ASSERT_TRUE(tempDir.isValid());

    QDir dir(tempDir.path());
    dir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    dir.mkdir("subdir");

    FileIterator iterator;
    QSignalSpy spy(&iterator, &FileIterator::iterationFinished);

    iterator.iterate(tempDir.path());

    ASSERT_EQ(spy.count(), 1);

    QList<QVariant> arguments = spy.takeFirst();
    const int actual_size_dir = arguments.at(0).toInt();
    const int expected_size_dir = 0;

    const int actual_count_files = arguments.at(1).toInt();
    const int expected_count_files = 0;

    const int actual_count_dirs = arguments.at(2).toInt();
    const int expected_count_dirs = 5; // 5 потому что unix создает 2 скрытые поддиректории
    // в каждой созданной директории: (2 * 2) + 1 = 5; 4 скрытые и одна добавленная

    const int actual_elapsed_time = arguments.at(4).toInt();
    const int expected_elapsed_time = 0;

    EXPECT_EQ(actual_size_dir, expected_size_dir);
    EXPECT_EQ(actual_count_files, expected_count_files);
    EXPECT_EQ(actual_count_dirs, expected_count_dirs);
    EXPECT_GE(actual_elapsed_time, expected_elapsed_time);
}

TEST(FileIteratorTests, TestIterateDir)
{
    qRegisterMetaType<QMap<QString, int>*>("QMap<QString, int>&");

    QTemporaryDir tempDir;
    ASSERT_TRUE(tempDir.isValid());

    QDir dir(tempDir.path());
    QFile file1(dir.filePath("file1.txt"));
    file1.open(QIODevice::WriteOnly);
    file1.write("Hello, world!");
    file1.close();

    QFile file2(dir.filePath("file2.txt"));
    file2.open(QIODevice::WriteOnly);
    file2.write("Hello, world!");
    file2.close();

    FileIterator iterator;
    QSignalSpy spy(&iterator, &FileIterator::iterationFinished);

    iterator.iterate(tempDir.path());

    ASSERT_EQ(spy.count(), 1);

    QList<QVariant> arguments = spy.takeFirst();
    const int actual_size_dir = arguments.at(0).toInt();
    const int expected_size_dir = 0;

    const int actual_count_files = arguments.at(1).toInt();
    const int expected_count_files = 2;

    const int actual_count_dirs = arguments.at(2).toInt();
    const int expected_count_dirs = 2; // 2 потому что unix создает 2 скрытые поддиректории

    const int actual_elapsed_time = arguments.at(4).toInt();
    const int expected_elapsed_time = 0;

    EXPECT_GE(actual_size_dir, expected_size_dir);
    EXPECT_EQ(actual_count_files, expected_count_files);
    EXPECT_EQ(actual_count_dirs, expected_count_dirs);
    EXPECT_GE(actual_elapsed_time, expected_elapsed_time);
}
























