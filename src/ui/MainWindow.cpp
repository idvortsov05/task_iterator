#include "MainWindow.h"

#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setupUi(this);
    controller = new Controller();

    QObject::connect(pushButton_iterator_dir, &QPushButton::clicked, this, &MainWindow::onPushButtonIterate);
    QObject::connect(pushButton_apply_filters, &QPushButton::clicked, this, &MainWindow::onPushButtonApplyFilters);
    QObject::connect(pushButton_reset_filters, &QPushButton::clicked, this, &MainWindow::onPushButtonResetFilters);
    QObject::connect(controller, &Controller::resultsReady, this, &MainWindow::onControllerResultsInfo);

    setupTable();
}

void MainWindow::setupListWidget(const QMap<QString, int> &files) const
{
    for (auto it = files.begin(); it != files.end(); ++it)
    {
        QListWidgetItem *item = new QListWidgetItem(it.key());
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
        listWidget_filters->addItem(item);
    }
}

void MainWindow::setupTable() const
{
    lineEdit_dir->setReadOnly(true);
    tableWidget->resizeRowsToContents();
    tableWidget->resizeColumnsToContents();
}

void MainWindow::onPushButtonIterate()
{
    dir_path = QFileDialog::getExistingDirectory(this, "Выберите директорию");
    if (!dir_path.isEmpty())
    {
        lineEdit_dir->setText(dir_path);
        QMessageBox::information(this, "Информация", "Директория успешно выбрана!");
        emit controller->operate(dir_path);
    }
    else
    {
        QMessageBox::warning(this, "Предупреждение", "Директория не была выбрана!");
    }
}

void MainWindow::onControllerResultsInfo(int size_dir, int count_files, int count_dirs, QMap<QString, int> files, qint64 time)
{
    if (files.empty())
    {
        QMessageBox::warning(this, "Ошибка", "Нет данных для отображения в таблице!");
        return;
    }
    setTable(files);
    setupListWidget(files);
    updateChart(files);

    label_sise_dir->setText("Занимаемое место на диске: " + QString::number(size_dir) + " MB");
    label_count_files->setText("Количество файлов: " + QString::number(count_files) + " шт.");
    label_count_dirs->setText("Количество директорий: " + QString::number((count_dirs)) + " шт.");
    label_time->setText("Время обхода директории: " + QString::number(time / 1000.0, 'f', 3) + " сек.");
}

void MainWindow::setTable(const QMap<QString, int> &files)
{
    tableWidget->setColumnCount(2);
    tableWidget->setRowCount(files.size());

    int row = 0;
    for (auto it = files.begin(); it != files.end(); ++it)
    {
        tableWidget->setItem(row, 0, new QTableWidgetItem("." + it.key()));
        tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(it.value())));
        row++;
    }

    tableWidget->resizeColumnsToContents();
    tableWidget->resizeRowsToContents();
}

void MainWindow::onPushButtonApplyFilters()
{
    int count = 0;
    QSet<QString> checked;

    for (int i = 0; i < listWidget_filters->count(); i++)
    {
        if (listWidget_filters->item(i)->checkState() == Qt::Checked)
        {
            QString item = listWidget_filters->item(i)->text();
            checked.insert(item);
        }
    }

    if (checked.isEmpty())
    {
        QMessageBox::warning(this, "Предупреждение", "Выберите хотя-бы 1 тип файла!");
        return;
    }

    QMap<QString, int> files = controller->getFiles();
    QMap<QString, int> result;

    for (auto it = files.begin(); it != files.end(); ++it)
    {
        QString ext = it.key();

        if (checked.contains(ext))
        {
            result[ext] = it.value();
            count += it.value();
        }
    }

    setTable(result);
    updateChart(result);
    label_count_files_->setText("Кол-во файлов: " + QString::number(count));
}


void MainWindow::onPushButtonResetFilters()
{
    QMap<QString, int> files = controller->getFiles();

    if (files.empty())
    {
        QMessageBox::warning(this, "Ошибка", "Нет данных для отображения в таблице!");
        return;
    }

    for (int i = 0; i < listWidget_filters->count(); i++)
    {
        QListWidgetItem *item = listWidget_filters->item(i);
        if (item)
        {
            item->setCheckState(Qt::Unchecked);
        }
    }

    label_count_files_ ->setText("");
    QMessageBox::information(this, "Информация", "Фильтры успешно сброшены!");
    setTable(files);
    updateChart(files);
}

using namespace QtCharts;
void MainWindow::updateChart(const QMap<QString, int> &files)
{
    if (files.isEmpty())
    {
        qWarning() << "Нет содержимого для отображения графика!";
        return;
    }

    QLayout *oldLayout = horizontalFrame_graphics->layout();
    if (oldLayout)
    {
        QLayoutItem *item;
        while ((item = oldLayout->takeAt(0)) != nullptr)
        {
            delete item->widget();
            delete item;
        }
        delete oldLayout;
    }
    auto *newLayout = new QVBoxLayout(horizontalFrame_graphics);
    horizontalFrame_graphics->setLayout(newLayout);

    auto *set = new QBarSet("Файлы");

    for (auto it = files.begin(); it != files.end(); ++it)
    {
        *set << it.value();
    }

    auto *series = new QBarSeries();
    series->append(set);

    auto *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Распределение файлов по типам");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    for (auto it = files.begin(); it != files.end(); ++it)
    {
        categories << it.key();
    }

    auto *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    QFont font = axisX->labelsFont();
    font.setPointSize(8);
    axisX->setLabelsFont(font);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    auto *axisY = new QValueAxis();
    int maxValue = 0;
    for (int i = 0; i < set->count(); ++i)
    {
        if (set->at(i) > maxValue)
        {
            maxValue = set->at(i);
        }
    }

    axisY->setRange(0, maxValue + 1);
    axisY->setTitleText("Количество");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    newLayout->addWidget(chartView);
}








