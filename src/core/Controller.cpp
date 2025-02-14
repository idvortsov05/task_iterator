#include "Controller.h"

Controller::Controller(QObject *parent) : QObject(parent)
{
    FileIterator *iterator = new FileIterator;
    iterator->moveToThread(&iteratorThread);

    connect(&iteratorThread, &QThread::finished, iterator, &QObject::deleteLater);
    connect(this, &Controller::operate, iterator, &FileIterator::iterate);
    connect(iterator, &FileIterator::iterationFinished, this, &Controller::handleResults);

    iteratorThread.start();
}

void Controller::iterate(const QString &path)
{
    emit operate(path);
}

void Controller::handleResults(int size_dir, int count_files, int count_dirs, QMap<QString, int> newfiles, qint64 time)
{
    files = std::move(newfiles);
    emit resultsReady(size_dir, count_files, count_dirs, files, time);
}

Controller::~Controller() noexcept
{
    iteratorThread.quit();
    iteratorThread.wait();
}


