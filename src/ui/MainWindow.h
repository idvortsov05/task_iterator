#ifndef ITERATOR_TASK_MAINWINDOW_H
#define ITERATOR_TASK_MAINWINDOW_H

#include "iterator_ui.h"
#include "../core/FileIterator.h"
#include "../core/Controller.h"

#include <QMainWindow>
#include <QObject>

class MainWindow : public QMainWindow, private Ui_MainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

public slots:
    void onPushButtonIterate();
    void onPushButtonApplyFilters();
    void onPushButtonResetFilters();
    void onControllerResultsInfo(int size_dir, int count_files, int count_dirs, QMap<QString, int> files, qint64 time);

private:
    QString dir_path;
    Controller *controller;

    void setupListWidget(const QMap<QString, int> &files) const;
    void setupTable() const;
    void setTable(const QMap<QString, int> &files);
    void updateChart(const QMap<QString, int> & files);
};

#endif //ITERATOR_TASK_MAINWINDOW_H