#include "employeeinfo.h"
#include "ui_employeeinfo.h"
#include <QString>
#include <QMessageBox>
#include "mainwindow.h"
#include <QSqlQueryModel>


EmployeeInfo::EmployeeInfo(QWidget *parent,QString id) :
    QWidget(parent),
    ui(new Ui::EmployeeInfo)
{
    ui->setupUi(this);

    if(!empDBUtils.connectToDB("db"))
    {
        QMessageBox::critical(this, "Error", "Failed to open the employee database, Check wheather your server is running or not.");
    }

    ui->label_7->setText("<html><head/><body><p align='center'>" + id + "</p></body></html>");

    QSqlQuery* info = new QSqlQuery();
    info = empDBUtils.getData(id);

    ui->showEmpName->setText(info->value(1).toString());
    ui->showEmpDOB->setText(info->value(2).toString());
    ui->showEmpFather->setText(info->value(4).toString());
    ui->showEmpEmail->setText(info->value(5).toString());
    ui->showEmpPhone->setText(info->value(6).toString());
    ui->showEmpAddress->setText(info->value(7).toString());
    ui->dept->setText(info->value(8).toString());
    ui->design->setText(info->value(9).toString());
    ui->doj->setText(info->value(10).toString());
    ui->salary->setText(info->value(11).toString());
    ui->type->setText(info->value(12).toString());
}

EmployeeInfo::~EmployeeInfo()
{
    delete ui;
}

void EmployeeInfo::on_pushButton_clicked()
{
    empDBUtils.closeDBConnection();
    this->close();

    MainWindow* mainWin = new MainWindow();
    mainWin->show();
}

