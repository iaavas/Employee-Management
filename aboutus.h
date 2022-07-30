#ifndef ABOUTUS_H
#define ABOUTUS_H

#include <QDialog>


namespace Ui {
class aboutus;
}

class aboutus : public QDialog
{
    Q_OBJECT

public:
    explicit aboutus(QWidget *parent = nullptr);
    ~aboutus();

private slots:
    void on_pushButton_clicked();

private:
    Ui::aboutus *ui;

};

#endif // ABOUTUS_H
