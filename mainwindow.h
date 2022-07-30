#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "aboutus.h"
#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QString>
#include <QDebug>
#include <QSqlError>
#include <QMainWindow>
#include <QPushButton>
#include <QWidget>
#include <QPoint>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>

#include "empdatabase.cpp"




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    EmpData empd;



private slots:
    void loadTotalData();
    void on_pushButton_2_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_deleteTableView_doubleClicked(const QModelIndex &index);

    void on_pushButton_14_clicked();

    void on_empDept_currentTextChanged(const QString &arg1);





    void on_searchTextBox_textEdited(const QString &arg1);





    void on_pushButton_12_clicked();



    void on_updateTableView_doubleClicked(const QModelIndex &index);

    void on_pushButton_13_clicked();



    void on_updateEmpType_currentTextChanged(const QString &arg1);

    void on_tableView_doubleClicked(const QModelIndex &index);

private:
    Ui::MainWindow *ui;
    aboutus *abt;
};
#endif // MAINWINDOW_H
