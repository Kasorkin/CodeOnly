#ifndef VIEVMANAGERFROMMAINDLG_H
#define VIEVMANAGERFROMMAINDLG_H

#include <QDialog>
#include "mainwindow.h"
#include <QtSql>
#include <QFileDialog>

namespace Ui {
class vievManagerfrommaindlg;
}

class vievManagerfrommaindlg : public QDialog
{
    Q_OBJECT

public:
    explicit vievManagerfrommaindlg(QWidget *parent = nullptr,int currec=1);
    ~vievManagerfrommaindlg();
    int getRecNmb();

private slots:
    void on_Next_clicked();

    void on_Last_clicked();

    void on_Accept_clicked();

    bool on_Decline_clicked();

    void on_Close_clicked();


private:
    Ui::vievManagerfrommaindlg *ui;
    QSqlRecord record;
    int recnmb;
};

#endif // VIEVMANAGERFROMMAINDLG_H
