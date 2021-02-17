#ifndef ALLPOSTAVSHIC_H
#define ALLPOSTAVSHIC_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class AllPostavshic;
}

class AllPostavshic : public QDialog
{
    Q_OBJECT

public:
    explicit AllPostavshic(QWidget *parent = nullptr);
    ~AllPostavshic();
private slots:
    void on_Add_clicked();
    void on_Delete_clicked();
    void on_Redact_clicked();
    void on_Exit_clicked();
    void on_Go1_clicked();

private:
    Ui::AllPostavshic *ui;
    QSqlRelationalTableModel *mdl;
};

#endif // ALLPOSTAVSHIC_H
