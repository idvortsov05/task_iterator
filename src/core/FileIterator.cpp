#include "FileIterator.h"

#include <QDirIterator>
#include <QDebug>
#include <QString>

FileIterator::FileIterator(QObject *parent) : QObject(parent) {}

void FileIterator::iterate(const QString &path)
{
    if(!QDir(path).exists())
    {
       qWarning() << "Can't open this file path!";
       return;
    }

    clearIterator();

    QDirIterator it(path, QDir::AllEntries | QDir::Hidden | QDir::System,
                    QDirIterator::Subdirectories | QDirIterator::FollowSymlinks);
    timer.start();

    while (it.hasNext())
    {
        it.next();
        QFileInfo fileInfo = it.fileInfo();

        if (!fileInfo.isReadable())
        {
            qWarning() << "No read access to:" << fileInfo.filePath();
            continue;
        }

        if (fileInfo.isFile())
        {
            analyzeFile(fileInfo);
            total_size += fileInfo.size() / BYTES_IN_MB;
            count_files++;
        }
        else if (fileInfo.isDir())
        {
            count_dirs++;
        }
    }
    emit iterationFinished(total_size, count_files, count_dirs, file_types_count, timer.elapsed());
}

void FileIterator::analyzeFile(const QFileInfo &file)
{
    QString extension = file.suffix().toLower();
    if (file.suffix().isEmpty())
    {
       extension = "no_extension";
    }
    file_types_count[extension]++;
}

void FileIterator::clearIterator()
{
    file_types_count.clear();
    total_size = 0;
    count_files = 0;
    count_dirs = 0;
}