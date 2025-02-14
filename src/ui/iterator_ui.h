/********************************************************************************
** Form generated from reading UI file 'iterator_ui.ui'
**
** Created by: Qt User Interface Compiler version 5.15.16
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef ITERATOR_UI_H
#define ITERATOR_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label_path;
    QLineEdit *lineEdit_dir;
    QPushButton *pushButton_iterator_dir;
    QTableWidget *tableWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_sise_dir;
    QLabel *label_count_files;
    QLabel *label_count_dirs;
    QLabel *label_time;
    QListWidget *listWidget_filters;
    QPushButton *pushButton_apply_filters;
    QPushButton *pushButton_reset_filters;
    QLabel *label_sort;
    QLabel *label_count_files_;
    QFrame *horizontalFrame_graphics;
    QHBoxLayout *horizontalLayout;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(839, 714);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        label_path = new QLabel(centralwidget);
        label_path->setObjectName(QString::fromUtf8("label_path"));
        label_path->setGeometry(QRect(10, 90, 181, 16));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        label_path->setFont(font);
        lineEdit_dir = new QLineEdit(centralwidget);
        lineEdit_dir->setObjectName(QString::fromUtf8("lineEdit_dir"));
        lineEdit_dir->setGeometry(QRect(10, 110, 261, 21));
        pushButton_iterator_dir = new QPushButton(centralwidget);
        pushButton_iterator_dir->setObjectName(QString::fromUtf8("pushButton_iterator_dir"));
        pushButton_iterator_dir->setGeometry(QRect(10, 10, 201, 51));
        pushButton_iterator_dir->setFont(font);
        pushButton_iterator_dir->setStyleSheet(QString::fromUtf8("QPushButton {background-color: rgb(122, 88, 200)}\n"
"QPushButton{border: 2px solid black}"));
        tableWidget = new QTableWidget(centralwidget);
        if (tableWidget->columnCount() < 2)
            tableWidget->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignJustify|Qt::AlignVCenter);
        __qtablewidgetitem->setFont(font);
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setFont(font);
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(10, 490, 281, 192));
        tableWidget->setStyleSheet(QString::fromUtf8(""));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 150, 281, 98));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_sise_dir = new QLabel(verticalLayoutWidget);
        label_sise_dir->setObjectName(QString::fromUtf8("label_sise_dir"));
        label_sise_dir->setFont(font);

        verticalLayout->addWidget(label_sise_dir);

        label_count_files = new QLabel(verticalLayoutWidget);
        label_count_files->setObjectName(QString::fromUtf8("label_count_files"));
        label_count_files->setFont(font);

        verticalLayout->addWidget(label_count_files);

        label_count_dirs = new QLabel(verticalLayoutWidget);
        label_count_dirs->setObjectName(QString::fromUtf8("label_count_dirs"));
        label_count_dirs->setFont(font);

        verticalLayout->addWidget(label_count_dirs);

        label_time = new QLabel(verticalLayoutWidget);
        label_time->setObjectName(QString::fromUtf8("label_time"));
        label_time->setFont(font);

        verticalLayout->addWidget(label_time);

        listWidget_filters = new QListWidget(centralwidget);
        listWidget_filters->setObjectName(QString::fromUtf8("listWidget_filters"));
        listWidget_filters->setGeometry(QRect(10, 300, 281, 111));
        listWidget_filters->setStyleSheet(QString::fromUtf8("QListWidget {border: 1px solid black}"));
        pushButton_apply_filters = new QPushButton(centralwidget);
        pushButton_apply_filters->setObjectName(QString::fromUtf8("pushButton_apply_filters"));
        pushButton_apply_filters->setGeometry(QRect(10, 420, 161, 31));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(false);
        font1.setWeight(50);
        pushButton_apply_filters->setFont(font1);
        pushButton_apply_filters->setStyleSheet(QString::fromUtf8("QPushButton {border: 2px solid black}\n"
"QPushButton {background-color: rgb(0, 144, 44)}"));
        pushButton_reset_filters = new QPushButton(centralwidget);
        pushButton_reset_filters->setObjectName(QString::fromUtf8("pushButton_reset_filters"));
        pushButton_reset_filters->setGeometry(QRect(180, 420, 111, 31));
        pushButton_reset_filters->setStyleSheet(QString::fromUtf8("QPushButton {border: 2px solid black}\n"
"QPushButton {background-color: rgb(244, 0, 33)}"));
        label_sort = new QLabel(centralwidget);
        label_sort->setObjectName(QString::fromUtf8("label_sort"));
        label_sort->setGeometry(QRect(10, 280, 231, 16));
        label_sort->setFont(font);
        label_count_files_ = new QLabel(centralwidget);
        label_count_files_->setObjectName(QString::fromUtf8("label_count_files_"));
        label_count_files_->setGeometry(QRect(10, 470, 271, 16));
        label_count_files_->setFont(font);
        horizontalFrame_graphics = new QFrame(centralwidget);
        horizontalFrame_graphics->setObjectName(QString::fromUtf8("horizontalFrame_graphics"));
        horizontalFrame_graphics->setGeometry(QRect(300, 10, 531, 671));
        horizontalFrame_graphics->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout = new QHBoxLayout(horizontalFrame_graphics);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        MainWindow->setCentralWidget(centralwidget);
        listWidget_filters->raise();
        label_path->raise();
        lineEdit_dir->raise();
        pushButton_iterator_dir->raise();
        tableWidget->raise();
        verticalLayoutWidget->raise();
        pushButton_apply_filters->raise();
        pushButton_reset_filters->raise();
        label_sort->raise();
        label_count_files_->raise();
        horizontalFrame_graphics->raise();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\223\320\273\320\260\320\262\320\275\320\276\320\265 \320\276\320\272\320\275\320\276", nullptr));
        label_path->setText(QCoreApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\320\275\320\275\320\260\321\217 \320\264\320\270\321\200\320\265\320\272\321\202\320\276\321\200\320\270\321\217:", nullptr));
        pushButton_iterator_dir->setText(QCoreApplication::translate("MainWindow", "\320\230\320\267\321\203\321\207\320\270\321\202\321\214 \320\264\320\270\321\200\320\265\320\272\321\202\320\276\321\200\320\270\321\216", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\321\201\321\210\320\270\321\200\320\265\320\275\320\270\320\265 \321\204\320\260\320\271\320\273\320\260", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276", nullptr));
        label_sise_dir->setText(QString());
        label_count_files->setText(QString());
        label_count_dirs->setText(QString());
        label_time->setText(QString());
        pushButton_apply_filters->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\270\320\274\320\265\320\275\320\270\321\202\321\214 \321\204\320\270\320\273\321\214\321\202\321\200\321\213", nullptr));
        pushButton_reset_filters->setText(QCoreApplication::translate("MainWindow", "\320\241\320\261\321\200\320\276\321\201\320\270\321\202\321\214", nullptr));
        label_sort->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\321\200\321\202\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\277\320\276 \321\202\320\270\320\277\320\260\320\274 \321\204\320\260\320\271\320\273\320\276\320\262:", nullptr));
        label_count_files_->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // ITERATOR_UI_H
