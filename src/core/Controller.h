#ifndef ITERATOR_TASK_CONTROLLER_H
#define ITERATOR_TASK_CONTROLLER_H

#include "FileIterator.h"

#include <QObject>
#include <QThread>

class Controller : public QObject
{
    Q_OBJECT

public:
    Controller(QObject *parent = nullptr);
    const QMap<QString, int> & getFiles() const { return files; }
    ~Controller() noexcept override;

public slots:
    void handleResults(int size_dir, int count_files, int count_dirs, QMap<QString, int> newfiles, qint64 time);
    void iterate(const QString &path);

signals:
    void operate(const QString &);
    void resultsReady(int size_dir, int count_files, int count_dirs, QMap<QString, int> newfiles, qint64 time);

private:
    QThread iteratorThread;
    QMap<QString, int> files;
};

#endif //ITERATOR_TASK_CONTROLLER_H
