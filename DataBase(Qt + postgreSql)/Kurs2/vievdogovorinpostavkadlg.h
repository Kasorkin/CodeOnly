#ifndef VIEVDOGOVORINPOSTAVKADLG_H
#define VIEVDOGOVORINPOSTAVKADLG_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>
#include <QCloseEvent>

namespace Ui {
class vievDogovorInPostavkaDlg;
}

class vievDogovorInPostavkaDlg : public QDialog
{
    Q_OBJECT

public:
    explicit vievDogovorInPostavkaDlg(QSqlRelationalTableModel *mdl,QWidget *parent = nullptr, int currec=1);
    ~vievDogovorInPostavkaDlg();

private slots:
    void on_Accept_clicked();

    bool on_Decline_clicked();

    void on_Close_clicked();

private:
    Ui::vievDogovorInPostavkaDlg *ui;
    QSqlRelationalTableModel* mdl;
    int recnmb;
};

#endif // VIEVDOGOVORINPOSTAVKADLG_H
