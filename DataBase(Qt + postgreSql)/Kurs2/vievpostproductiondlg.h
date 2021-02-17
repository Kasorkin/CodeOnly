#ifndef VIEVPOSTPRODUCTIONDLG_H
#define VIEVPOSTPRODUCTIONDLG_H

#include <QDialog>
#include "mainwindow.h"
#include <QtSql>
#include <QFileDialog>

namespace Ui {
class vievPostProductiondlg;
}

class vievPostProductiondlg : public QDialog
{
    Q_OBJECT

public:
    explicit vievPostProductiondlg(QWidget *parent = nullptr,int currec=1);
    ~vievPostProductiondlg();
    int getRecNmb2();

private slots:
    void on_Next_clicked();

    void on_Last_clicked();

    void on_Accept_clicked();

    bool on_Decline_clicked();

    void on_Close_clicked();

private:
    Ui::vievPostProductiondlg *ui;
    QSqlRecord record2;
    int recnmb2;
};

#endif // VIEVPOSTPRODUCTIONDLG_H
