#ifndef ITERATOR_TASK_MAINWINDOW_H
#define ITERATOR_TASK_MAINWINDOW_H

#include "ui_iterator_ui.h"
#include "core/FileIterator.h"
#include "core/Controller.h"

#include <QMainWindow>
#include <QObject>

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

public slots:
    void onPushButtonIterate();
    void onPushButtonApplyFilters();
    void onPushButtonResetFilters();
    void onControllerResultsInfo(quint64 size_dir, int count_files, int count_dirs, QMap<QString, int>& files, qint64 time);

private:
    Ui::MainWindow* m_ui;
    QString dir_path;
    Controller *controller;

    void setupListWidget(const QMap<QString, int> &files) const;
    void setupTable() const;
    void setTable(const QMap<QString, int> &files);
    void updateChart(const QMap<QString, int> & files);
    void clear_layout();
};

#endif //ITERATOR_TASK_MAINWINDOW_H