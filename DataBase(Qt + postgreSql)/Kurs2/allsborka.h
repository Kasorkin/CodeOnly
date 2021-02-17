#ifndef ALLSBORKA_H
#define ALLSBORKA_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
class AllSborka;
}

class AllSborka : public QDialog
{
    Q_OBJECT

public:
    explicit AllSborka(QWidget *parent = nullptr);
    ~AllSborka();
private slots:
    void on_Add_clicked();
    void on_Delete_clicked();
    void on_Redact_clicked();
    void on_Osn_clicked();
    void on_Dop_clicked();
    void on_Exit_clicked();

private:
    Ui::AllSborka *ui;
    QSqlRelationalTableModel *mdl;
};

#endif // ALLSBORKA_H
