#ifndef ALLDOGOVORINSBORKA_H
#define ALLDOGOVORINSBORKA_H

#include <QDialog>
#include <QtSql>
#include <QMessageBox>

namespace Ui {
class AllDogovorInSborka;
}

class AllDogovorInSborka : public QDialog
{
    Q_OBJECT

public:
    explicit AllDogovorInSborka(QWidget *parent = nullptr);
    ~AllDogovorInSborka();
private slots:
    void on_Add_clicked();
    void on_Delete_clicked();
    void on_Redact_clicked();
    void on_Exit_clicked();
    void on_Go1_clicked();

private:
    Ui::AllDogovorInSborka *ui;
    QSqlRelationalTableModel *mdl;  //Модель для работы с таблицей
};

#endif // ALLDOGOVORINSBORKA_H
