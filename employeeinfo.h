#ifndef EMPLOYEEINFO_H
#define EMPLOYEEINFO_H

#include <QWidget>
#include <QString>
#include <searchDatabase.cpp>


namespace Ui {
class EmployeeInfo;
}

class EmployeeInfo : public QWidget
{
    Q_OBJECT

public:
    explicit EmployeeInfo(QWidget *parent = nullptr, QString id="");
    ~EmployeeInfo();
    EmployeeDatabaseUtils empDBUtils;


private slots:
    void on_pushButton_clicked();

private:
    Ui::EmployeeInfo *ui;
};

#endif // EMPLOYEEINFO_H
