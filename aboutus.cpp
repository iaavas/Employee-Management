#include "aboutus.h"
#include "ui_aboutus.h"
#include "mainwindow.h"

aboutus::aboutus(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::aboutus)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);


}

aboutus::~aboutus()
{
    delete ui;
}


void aboutus::on_pushButton_clicked()
{
    hide();
    MainWindow* mainWin = new MainWindow();

    mainWin->show();


}

