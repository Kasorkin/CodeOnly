#ifndef ALLDOGOVORINPOSTAVKA_H
#define ALLDOGOVORINPOSTAVKA_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class AllDogovorInPostavka;
}

class AllDogovorInPostavka : public QDialog
{
    Q_OBJECT

public:
    explicit AllDogovorInPostavka(QWidget *parent = nullptr);
    ~AllDogovorInPostavka();
private slots:
    void on_Add_clicked();
    void on_Delete_clicked();
    void on_Redact_clicked();
    void on_Exit_clicked();
    void on_Go1_clicked();

private:
    Ui::AllDogovorInPostavka *ui;
    QSqlRelationalTableModel *mdl;
};

#endif // ALLDOGOVORINPOSTAVKA_H
