#include <QtSql/QSqlDatabase>
#include <QString>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QComboBox>
#include <QLabel>
#include <QTableView>
#include <QSqlDatabase>

class EmpData
{
public:
    QSqlDatabase empDB;

    bool connectToDB(QString dbName)
    {
        empDB = QSqlDatabase::addDatabase("QSQLITE");
        empDB.setDatabaseName("D:/EMS/employeeManagement/database/mydb.sqlite");

        if(!empDB.open())
        {
            qDebug() << ("Failed to open the database");
            return false;
        }
        else
        {

            qDebug() << ("Connected to database");
            return true;
        }
    }

    void closeDBConnection()
    {

        if (empDB.isValid())
        {
            empDB.close();
            empDB.removeDatabase(QSqlDatabase::defaultConnection);
        }
    }

    QSqlQuery* getData(QString id)
    {
        QSqlQuery *qry = new QSqlQuery(empDB);

        qry->prepare("SELECT * FROM employee WHERE id='" + id + "';");

        if(qry->exec())
        {
            qry->next();
            return qry;

            qDebug() << "Got the employee information from the database";
        }
        else
        {
            return NULL;
            qDebug() << "Failed";
        }


    }

    QString getTotalEmployee()
    {
        QSqlQuery *qry = new QSqlQuery(empDB);

        qry->prepare("SELECT COUNT(ID) FROM employee");
        qry->exec();
        qry->next();

        int lastID = qry->value(0).toInt();

        return QString::number(lastID);
    }

    QString getTotalDept()
    {
        QSqlQuery *qry = new QSqlQuery(empDB);

        qry->prepare("SELECT COUNT(Distinct(Designation)) FROM employee");
        qry->exec();
        qry->next();

        int lastID = qry->value(0).toInt();

        return QString::number(lastID);
    }

    QSqlQueryModel* getDesignationList(QComboBox* dept)
    {
        QSqlQueryModel *model = new QSqlQueryModel();
        QSqlQuery *qry = new QSqlQuery(empDB);

        qry->prepare("SELECT designation FROM company WHERE department='" + dept->currentText() + "';");

        if(qry->exec())
        {
            model->setQuery(*qry);
            qDebug() << "Sucesss";
        }
        else
        {
            qDebug() << "Failed";
        }

        return model;
    }

    QSqlQueryModel* getDepartmentList()
    {
        QSqlQueryModel *model = new QSqlQueryModel();
        QSqlQuery *qry = new QSqlQuery(empDB);

        qry->prepare("SELECT DISTINCT(department) FROM company");

        if(qry->exec())
        {
            model->setQuery(*qry);
            qDebug() << "Sucesss";
        }
        else
        {
            qDebug() << "Failed";
        }

        return model;
    }

    QString getLastID()
    {
        QSqlQuery *qry = new QSqlQuery(empDB);


        qry->prepare("SELECT MAX(Employee_ID) FROM Employee");

        qry->exec();
        qry->next();

        int lastID = qry->value(0).toInt() + 1;

        return QString::number(lastID);
    }


    void setEmployeeDetails(QTableView* tableView)
    {
        if(empDB.isOpen())
        {
            QSqlQueryModel *querModel = new QSqlQueryModel();
            querModel->setQuery("SELECT id, name, department, designation, phone FROM employee;");
            tableView->setModel(querModel);
        }
    }





    QString getEmployeeID(QString dept, QString design)
    {
        return dept + "/" + design + "/" + getLastID();
    }

    QString getDesignationShortName(QComboBox* design)
    {
        QSqlQuery *qry = new QSqlQuery(empDB);

        qry->prepare("SELECT desig_short FROM company WHERE designation='" + design->currentText() + "';");
        qry->exec();
        qry->next();

        QString x = qry->value(0).toString();

        return x;
    }

    QString getDepartmentShortName(QComboBox* dept)
    {
        QSqlQuery *qry = new QSqlQuery(empDB);

        qry->prepare("SELECT dept_short FROM company WHERE department='" + dept->currentText() + "';");
        qry->exec();
        qry->next();

        QString x = qry->value(0).toString();

        return x;
    }

    void setEmployeeUpdateDetails(QTableView* tableView)
    {
        if(empDB.isOpen())
        {
            QSqlQueryModel *querModel = new QSqlQueryModel();
            querModel->setQuery("SELECT id, name, department FROM employee;");
            tableView->setModel(querModel);
        }
    }

    void deleteEmployeeRecord(QString id)
    {
        QSqlQuery *qry = new QSqlQuery(empDB);

        qry->prepare("DELETE  FROM employee WHERE id='" + id + "';");

        qry->exec();
    }

    int getSalary(QComboBox* dept, QComboBox* design)
    {
        QSqlQuery *qry = new QSqlQuery(empDB);

        qry->prepare("SELECT salary FROM company WHERE department='" + dept->currentText() + "' AND designation='" +design->currentText() + "';");
        qry->exec();
        qry->next();

        int x = qry->value(0).toInt();

        return x;
    }

    int getSalaryUpdate(QVariant a, QVariant b)
    {
        QSqlQuery *qry = new QSqlQuery(empDB);
        QString xa = a.toString();
        QString xb = b.toString();

        qry->prepare("SELECT salary FROM company WHERE department='" +xa + "' AND designation='" + xb + "';");
        qry->exec();
        qry->next();

        int x = qry->value(0).toInt();

        return x;

    }

    void searchEmployeeDetails(QTableView* tableView, QString searchText)
    {
        if(empDB.isOpen())
        {
            QSqlQueryModel *querModel = new QSqlQueryModel();
            querModel->setQuery("SELECT id, name, department, designation, phone, email FROM employee WHERE name LIKE '" + searchText + "%' OR id LIKE '" + searchText +"%';");
            tableView->setModel(querModel);
        }
    }

    QSqlQuery* showEmployeeDetailsToLineEdit(QString id)
    {
        QSqlQuery *qry = new QSqlQuery(empDB);

        qry->prepare("SELECT * FROM employee WHERE id='" + id + "';");
        qry->exec();
        qry->next();

        return qry;
    }





};


