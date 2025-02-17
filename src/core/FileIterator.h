#ifndef ITERATOR_TASK_FILEITERATOR_H
#define ITERATOR_TASK_FILEITERATOR_H

#include <QObject>
#include <QFileInfo>
#include <QElapsedTimer>
#include <QMap>

class FileIterator : public QObject
{
    Q_OBJECT

public:
    explicit FileIterator(QObject * parent = nullptr);

public slots:
    void iterate(const QString &path);

signals:
    void iterationFinished(qint64 size_dir, int count_files, int count_dirs, QMap<QString, int>& file_types_count, qint64 elapsedTime);

private:
    QMap<QString, int> file_types_count;
    static constexpr qint64 BYTES_IN_MB = 1024 * 1024;
    qint64 total_size = 0;
    int count_files = 0;
    int count_dirs = 0;
    QElapsedTimer timer;

    void analyzeFile(const QFileInfo &file);
    void clearIterator();
};

#endif //ITERATOR_TASK_FILEITERATOR_H
