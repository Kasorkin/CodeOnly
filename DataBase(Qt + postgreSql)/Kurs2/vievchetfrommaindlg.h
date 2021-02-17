#ifndef VIEVCHETFROMMAINDLG_H
#define VIEVCHETFROMMAINDLG_H

#include <QDialog>
#include <QtSql>
#include <QFileDialog>
#include "mainwindow.h"

namespace Ui {
class VievChetfrommainDlg;
}

class VievChetfrommainDlg : public QDialog
{
    Q_OBJECT

public:
    explicit VievChetfrommainDlg(QWidget *parent = nullptr,int currec=1);
    ~VievChetfrommainDlg();
    int getRecNmb3();

private slots:
    void on_Next_clicked();

    void on_Last_clicked();

    void on_Accept_clicked();

    bool on_Decline_clicked();

    void on_Close_clicked();

private:
    Ui::VievChetfrommainDlg *ui;
    QSqlRecord record3;
    int recnmb3;

};

#endif // VIEVCHETFROMMAINDLG_H
