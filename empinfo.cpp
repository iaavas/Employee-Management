#include "empinfo.h"
#include "empinfo.h"
#include "ui_empinfo.h"
#include <QString>
#include <QMessageBox>
#include "mainwindow.h"
#include <QSqlQueryModel>

empinfo::empinfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::empinfo)
{
    ui->setupUi(this);
}

empinfo::~empinfo()
{
    delete ui;
}
