#ifndef EMPINFO_H
#define EMPINFO_H

#include <QDialog>

namespace Ui {
class empinfo;
}

class empinfo : public QDialog
{
    Q_OBJECT

public:
    explicit empinfo(QWidget *parent = nullptr);
    ~empinfo();

private:
    Ui::empinfo *ui;
};

#endif // EMPINFO_H
