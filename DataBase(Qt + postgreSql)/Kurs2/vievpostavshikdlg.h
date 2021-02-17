#ifndef VIEVPOSTAVSHIKDLG_H
#define VIEVPOSTAVSHIKDLG_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>
#include <QCloseEvent>

namespace Ui {
class VievPostavshikDlg;
}

class VievPostavshikDlg : public QDialog
{
    Q_OBJECT

public:
    explicit VievPostavshikDlg(QSqlRelationalTableModel *mdl,QWidget *parent = nullptr, int currec=1);
    ~VievPostavshikDlg();

private slots:
    void on_Accept_clicked();

    bool on_Decline_clicked();

    void on_Close_clicked();

private:
    Ui::VievPostavshikDlg *ui;
    QSqlRelationalTableModel* mdl;
    int recnmb;
};

#endif // VIEVPOSTAVSHIKDLG_H
