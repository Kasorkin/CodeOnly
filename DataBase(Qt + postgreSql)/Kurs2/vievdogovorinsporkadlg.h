#ifndef VIEVDOGOVORINSPORKADLG_H
#define VIEVDOGOVORINSPORKADLG_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>
#include <QCloseEvent>

namespace Ui {
class VievDogovorInSporkaDlg;
}

class VievDogovorInSporkaDlg : public QDialog
{
    Q_OBJECT

public:
    explicit VievDogovorInSporkaDlg(QSqlRelationalTableModel *mdl,QWidget *parent = nullptr, int currec=1);
    ~VievDogovorInSporkaDlg();

private slots:
    void on_Accept_clicked();

    bool on_Decline_clicked();

    void on_Close_clicked();


private:
    Ui::VievDogovorInSporkaDlg *ui;
    QSqlRelationalTableModel* mdl;
    int recnmb;
};

#endif // VIEVDOGOVORINSPORKADLG_H
