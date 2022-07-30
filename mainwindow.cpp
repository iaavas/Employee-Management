#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QStringList>
#include <QDate>
#include "employeeinfo.h"





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableView->setAlternatingRowColors(true);
    ui->tableView->setStyleSheet("alternate-background-color: #E4E4E4;background-color:white;selection-background-color:#1492E6;selection-color:white;");
    ui->updateTableView->setAlternatingRowColors(true);
    ui->updateTableView->setStyleSheet("alternate-background-color: #E4E4E4;background-color:white;selection-background-color:#1492E6;selection-color:white;");

    ui->updateTableView->setAlternatingRowColors(true);
    ui->updateTableView->setStyleSheet("alternate-background-color: #E4E4E4;background-color:white;selection-background-color:#1492E6;selection-color:white;");

    ui->deleteTableView->setAlternatingRowColors(true);
    ui->deleteTableView->setStyleSheet("alternate-background-color: #E4E4E4;background-color:white;selection-background-color:#1492E6;selection-color:white;");












    if(!empd.connectToDB("mydb"))
    {
        QMessageBox::critical(this, "Error", "Failed to open the database, Check wheather your server is running or not.");
    }

    loadTotalData();


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_2_clicked()
{
    hide();
    abt = new aboutus(this);
    abt->show();
}


void MainWindow::on_pushButton_9_clicked()
{
    empd.setEmployeeDetails(ui->tableView);
    loadTotalData();
    ui->stackedWidget->setCurrentIndex(0);

}



void MainWindow::on_pushButton_8_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}



void MainWindow::on_pushButton_7_clicked()
{

    ui->stackedWidget->setCurrentIndex(2);
    empd.setEmployeeUpdateDetails(ui->updateTableView);

}


void MainWindow::on_pushButton_6_clicked()
{
    empd.setEmployeeDetails(ui->deleteTableView);
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::loadTotalData()
{
    int lastID = empd.getTotalEmployee().toInt();

    QString lastIDString = QString::number(lastID);

    if(lastIDString.length() == 1)
    {
        lastIDString = "00" + lastIDString;
    }
    else if(lastIDString.length() == 2)
    {
        lastIDString = "0" + lastIDString;
    }

    empd.setEmployeeDetails(ui->tableView);

    ui->empLabel->setText(lastIDString);

    QString dept = empd.getTotalDept();

    if(dept.length() == 1)
    {
        dept = "00" + dept;
    }
    else if(dept.length() == 2)
    {
        dept = "0" + dept;
    }

    ui->deptLabel->setText(dept);



 }

void MainWindow::on_pushButton_4_clicked()
{
    if(ui->empName->text().trimmed().isEmpty() ||
       ui->empAddress->text().trimmed().isEmpty() ||
       ui->empEmail->text().trimmed().isEmpty() ||
       ui->empFather->text().trimmed().isEmpty() ||
       ui->empPhone->text().trimmed().isEmpty() ||
       ui->empSalary->text().trimmed().isEmpty() ||
       ui->empID->text().trimmed().isEmpty())
    {
        QMessageBox::critical(this, "Empty", "All fields are mandatory to fill");
    }
    else
    {


        QSqlQuery* sqlQuery = new QSqlQuery(empd.empDB);
        if(empd.empDB.isOpen())
        {


            sqlQuery->prepare("insert into Employee (ID, Name, DOB, Gender, Father, Email, Phone, Address, Department, Designation, DOJ, Salary, Type) "
                             "values ('" +
                                ui->empID->text().trimmed() + "' ,'" +
                                ui->empName->text().trimmed() + "' , '" +
                                ui->empDOB->text().trimmed() + "' , '" +
                                ui->empGender->currentText().trimmed() + "' , '" +
                                ui->empFather->text().trimmed() + "' , '" +
                                ui->empEmail->text().trimmed() + "' , '" +
                                ui->empPhone->text().trimmed() + "' , '" +
                                ui->empAddress->text().trimmed() + "' , '" +
                                ui->empDept->currentText().trimmed() + "' , '" +
                                ui->empDesig->currentText().trimmed() + "' , '" +
                                ui->empDOJ->text().trimmed() + "' , " +
                                ui->empSalary->text().trimmed() + ", '" +
                                ui->empType->currentText() + "');"
                             );

            sqlQuery->prepare("INSERT INTO Employee (ID, Name, DOB, Gender, Father, Email, Phone, Address, Department, Designation, DOJ, Salary, Type) "
                              "VALUES(:ID, :Name, :DOB, :Gender, :Father, :Email, :Phone, :Address, :Department, :Designation, :DOJ, :Salary, :Type)");
            sqlQuery->bindValue(":ID", ui->empID->text().trimmed());
            sqlQuery->bindValue(":Name", ui->empName->text().trimmed());
            sqlQuery->bindValue(":DOB", ui->empDOB->text().trimmed());
            sqlQuery->bindValue(":Gender", ui->empGender->currentText().trimmed());
            sqlQuery->bindValue(":Father", ui->empFather->text().trimmed());
            sqlQuery->bindValue(":Email", ui->empEmail->text().trimmed());
            sqlQuery->bindValue(":Phone", ui->empPhone->text().trimmed());
            sqlQuery->bindValue(":Address", ui->empAddress->text().trimmed());
            sqlQuery->bindValue(":Department", ui->empDept->currentText().trimmed());
            sqlQuery->bindValue(":Designation", ui->empDesig->currentText().trimmed());
            sqlQuery->bindValue(":DOJ", ui->empDOJ->text().trimmed());
            sqlQuery->bindValue(":Salary", ui->empSalary->text().trimmed());
            sqlQuery->bindValue(":Type", ui->empType->currentText().trimmed());




            if(sqlQuery->exec())
            {
                QMessageBox::information(this, "Success", "Data inserted successfully");
                sqlQuery->next();
            }
            else
            {
                   qDebug() << "Error : "<<sqlQuery->lastError().text() << sqlQuery->isValid();
            }
        }
    }



}

void MainWindow::on_pushButton_3_clicked()
{
    ui->empName->setText("");
    ui->empAddress->setText("");
    ui->empEmail->setText("");
    ui->empFather->setText("");
    ui->empPhone->setText("");
    ui->empSalary->setText("");
    ui->empID->setText("");
}


void MainWindow::on_pushButton_clicked()
{


    int salary = 0;

    ui->empID->setText(empd.getEmployeeID(empd.getDepartmentShortName(ui->empDept), empd.getDesignationShortName(ui->empDesig)));

    if(ui->empType->currentIndex() == 0)
    {
        salary = empd.getSalary(ui->empDept , ui->empDesig) - 20000;
        ui->empSalary->setText(QString::number(salary));
    }
    else
    {
        salary = empd.getSalary(ui->empDept , ui->empDesig);
        ui->empSalary->setText(QString::number(salary));
    }


}


void MainWindow::on_deleteTableView_doubleClicked(const QModelIndex &index)
{
    QString id = ui->deleteTableView->model()->index(index.row(), 0).data().toString();

    QMessageBox::StandardButton reply;

    reply = QMessageBox::question(this, "Confirm", "Are you sure you want to delete '" + id + "' record");

    if(reply == QMessageBox::Yes)
    {
        empd.deleteEmployeeRecord(id);
    }
}


void MainWindow::on_pushButton_14_clicked()
{
    empd.setEmployeeDetails(ui->deleteTableView);
}


void MainWindow::on_empDept_currentTextChanged(const QString &arg1)
{
    if (arg1 == "Tech") {
            ui->empDesig->clear();
            ui->empDesig->addItem("Back End Engineer");
            ui->empDesig->addItem("Front End Engineer");

        }
        else if (arg1 == "Finance") {
        ui->empDesig->clear();
        ui->empDesig->addItem("CA");
        ui->empDesig->addItem("Analyst");
        }

}




void MainWindow::on_searchTextBox_textEdited(const QString &arg1)
{
    ui->tableView->setModel(NULL);
    empd.searchEmployeeDetails(ui->tableView, ui->searchTextBox->text().trimmed());

}





void MainWindow::on_pushButton_12_clicked()
{
  ui->updateEmpAddress->setText("");
  ui->updateEmpEmail->setText("");
  ui->updateEmpPhone->setText("");
  ui->updateEmpType->setCurrentIndex(0);



}





void MainWindow::on_updateTableView_doubleClicked(const QModelIndex &index)
{
    QString id = ui->updateTableView->model()->index(index.row(), 0).data().toString();
    ui->updateEmpID->setText(id);

    QSqlQuery* qry = empd.showEmployeeDetailsToLineEdit(id);


    QString type = qry->value("Type").toString();
    int salary = 0;

    if(type == "Fresher")
    {
        ui->updateEmpType->setCurrentIndex(0);
        salary = empd.getSalaryUpdate(qry->value("department") , qry->value("designation"));
        ui->updateEmpSalary->setText(QString::number(salary-20000));


    }

    else
    {
        ui->updateEmpType->setCurrentIndex(1);
        salary = empd.getSalaryUpdate(qry->value("department") , qry->value("designation"));
        ui->updateEmpSalary->setText(QString::number(salary));
    }















    ui->updateEmpEmail->setText(qry->value("email").toString());
    ui->updateEmpAddress->setText(qry->value("address").toString());
    ui->updateEmpPhone->setText(qry->value("phone").toString());





}




void MainWindow::on_pushButton_13_clicked()
{
    if( ui->updateEmpAddress->text().trimmed().isEmpty() ||
            ui->updateEmpEmail->text().trimmed().isEmpty() || ui->updateEmpPhone->text().trimmed().isEmpty()
            )
    {
        QMessageBox::warning(this, "Empty Data", "All fields are required to fill");
    }
    else
    {
        QSqlQuery* sqlQuery = new QSqlQuery(empd.empDB);



        if(empd.empDB.isOpen())
        {
            sqlQuery->prepare("UPDATE employee SET "
                              "email='" + ui->updateEmpEmail->text().trimmed() + "'," +
                              "phone='" + ui->updateEmpPhone->text().trimmed() + "'," +
                              "address='" + ui->updateEmpAddress->text().trimmed() + "'," +
                              "salary='" + ui->updateEmpSalary->text().trimmed() + "'," +
                              "type='" + ui->updateEmpType->currentText().trimmed() + "' WHERE id='" + ui->updateEmpID->text()+"';");


            if(sqlQuery->exec())
            {
                QMessageBox::information(this, "Success", "Data updated successfully");
            }
            else
            {
                   qDebug() << "Error : "<<sqlQuery->lastError().text() << sqlQuery->isValid();
            }
        }
    }

}








void MainWindow::on_updateEmpType_currentTextChanged(const QString &arg1)
{

    QSqlQuery* qry = empd.showEmployeeDetailsToLineEdit(ui->updateEmpID->text());
    int salary = 0;

    if(ui->updateEmpType->currentIndex() == 0)
    {

        salary = empd.getSalaryUpdate(qry->value("department") , qry->value("designation")) - 20000;
        qDebug() << salary;
        ui->updateEmpSalary->setText(QString::number(salary));
    }
    else
    {
        salary = empd.getSalaryUpdate(qry->value("department") , qry->value("designation"));
        qDebug() << salary;
        ui->updateEmpSalary->setText(QString::number(salary));
    }


}




void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    QString id = ui->tableView->model()->index(index.row(), 0).data().toString();

    empd.closeDBConnection();
    MainWindow::close();
    EmployeeInfo* emp = new EmployeeInfo(this, id);
    emp->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    emp->show();





}

