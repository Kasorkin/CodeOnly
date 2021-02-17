#ifndef VIEVZAKAZCHIKFROMMAINDLG_H
#define VIEVZAKAZCHIKFROMMAINDLG_H

#include <QDialog>
#include "mainwindow.h"
#include <QtSql>
#include <QFileDialog>

namespace Ui {
class vievZakazchikfrommaindlg;
}

class vievZakazchikfrommaindlg : public QDialog
{
    Q_OBJECT

public:
    explicit vievZakazchikfrommaindlg(QWidget *parent = nullptr,int currec=1);
    ~vievZakazchikfrommaindlg();
    int getRecNmb1();

private slots:
    void on_Next_clicked();

    void on_Last_clicked();

    void on_Accept_clicked();

    bool on_Decline_clicked();

    void on_Close_clicked();

private:
    Ui::vievZakazchikfrommaindlg *ui;
    QSqlRecord record1;
    int recnmb1;
};

#endif // VIEVZAKAZCHIKFROMMAINDLG_H
