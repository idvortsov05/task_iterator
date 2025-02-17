#include "MainWindow.h"

#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>

#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    m_ui->centralwidget->setLayout(m_ui->verticalLayout_main);

    controller = new Controller();

    QObject::connect(m_ui->pushButton_iterator_dir, &QPushButton::clicked, this, &MainWindow::onPushButtonIterate);
    QObject::connect(m_ui->pushButton_apply_filters, &QPushButton::clicked, this, &MainWindow::onPushButtonApplyFilters);
    QObject::connect(m_ui->pushButton_reset_filters, &QPushButton::clicked, this, &MainWindow::onPushButtonResetFilters);
    QObject::connect(controller, &Controller::resultsReady, this, &MainWindow::onControllerResultsInfo);

    setupTable();
    showFullScreen();
}

void MainWindow::setupListWidget(const QMap<QString, int> &files) const
{
    for (auto it = files.begin(); it != files.end(); ++it)
    {
        auto *item = new QListWidgetItem(it.key());
        item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
        item->setCheckState(Qt::Unchecked);
        m_ui->listWidget_filters->addItem(item);
    }
}

void MainWindow::setupTable() const
{
    m_ui->lineEdit_dir->setReadOnly(true);
    m_ui->tableWidget->resizeRowsToContents();
    m_ui->tableWidget->resizeColumnsToContents();
    m_ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::onPushButtonIterate()
{
    dir_path = QFileDialog::getExistingDirectory(this, "Выберите директорию");
    if (!dir_path.isEmpty())
    {
        m_ui->lineEdit_dir->setText(dir_path);
        QMessageBox::information(this, "Информация", "Директория успешно выбрана!");
        emit controller->operate(dir_path);
    }
    else
    {
        QMessageBox::warning(this, "Предупреждение", "Директория не была выбрана!");
    }
}

void MainWindow::onControllerResultsInfo(quint64 size_dir, int count_files, int count_dirs, QMap<QString, int>& files, qint64 time)
{
    if (files.empty())
    {
        QMessageBox::warning(this, "Ошибка", "Нет данных для отображения в таблице!");
        return;
    }
    setTable(files);
    setupListWidget(files);
    updateChart(files);

    m_ui->label_sise_dir->setText("Занимаемое место на диске: " + QString::number(size_dir) + " MB");
    m_ui->label_count_files->setText("Количество файлов: " + QString::number(count_files) + " шт.");
    m_ui->label_count_dirs->setText("Количество директорий: " + QString::number((count_dirs)) + " шт.");
    m_ui->label_time->setText("Время обхода директории: " + QString::number(time / 1000.0, 'f', 3) + " сек.");
}

void MainWindow::setTable(const QMap<QString, int> &files)
{
    m_ui->tableWidget->setColumnCount(2);
    m_ui->tableWidget->setRowCount(files.size());

    auto row = 0;
    for (auto it = files.begin(); it != files.end(); ++it)
    {
        m_ui->tableWidget->setItem(row, 0, new QTableWidgetItem("." + it.key()));
        m_ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(it.value())));
        row++;
    }

    m_ui->tableWidget->resizeColumnsToContents();
    m_ui->tableWidget->resizeRowsToContents();
}

void MainWindow::onPushButtonApplyFilters()
{
    auto count = 0;
    QSet<QString> checked;

    for (int i = 0; i < m_ui->listWidget_filters->count(); i++)
    {
        if (m_ui->listWidget_filters->item(i)->checkState() == Qt::Checked)
        {
            checked.insert(m_ui->listWidget_filters->item(i)->text());
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
        if (checked.contains(it.key()))
        {
            result[it.key()] = it.value();
            count += it.value();
        }
    }
    setTable(result);
    updateChart(result);

    m_ui->label_count_sorted_files->setText("Кол-во отсортированных файлов: " + QString::number(count));
}


void MainWindow::onPushButtonResetFilters()
{
    QMap<QString, int> files = controller->getFiles();

    if (files.empty())
    {
        QMessageBox::warning(this, "Ошибка", "Нет данных для отображения в таблице!");
        return;
    }

    for (int i = 0; i < m_ui->listWidget_filters->count(); i++)
    {
        QListWidgetItem *item = m_ui->listWidget_filters->item(i);
        if (item)
        {
            item->setCheckState(Qt::Unchecked);
        }
    }
    m_ui->label_count_sorted_files->setText("");
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

    clear_layout();

    auto *newLayout = new QVBoxLayout(m_ui->horizontalFrame_graphics);
    m_ui->horizontalFrame_graphics->setLayout(newLayout);

    auto *set = new QBarSet("Количество файлов");

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
    auto font = axisX->labelsFont();
    font.setPointSize(8);
    axisX->setLabelsFont(font);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    auto *axisY = new QValueAxis();
    auto maxValue = 0;
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

    auto *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    newLayout->addWidget(chartView);
}

void MainWindow::clear_layout()
{
    auto *oldLayout = m_ui->horizontalFrame_graphics->layout();
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
}








