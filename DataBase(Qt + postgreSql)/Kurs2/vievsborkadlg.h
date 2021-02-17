#ifndef VIEVSBORKADLG_H
#define VIEVSBORKADLG_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>
#include <QCloseEvent>

namespace Ui {
class VievSborkaDlg;
}

class VievSborkaDlg : public QDialog
{
    Q_OBJECT

public:
    explicit VievSborkaDlg(QSqlRelationalTableModel *mdl,QWidget *parent = nullptr, int currec=1);
    ~VievSborkaDlg();

private slots:
    void on_Accept_clicked();

    bool on_Decline_clicked();

    void on_Close_clicked();

private:
    Ui::VievSborkaDlg *ui;
    QSqlRelationalTableModel* mdl;
    int recnmb;
};

#endif // VIEVSBORKADLG_H
