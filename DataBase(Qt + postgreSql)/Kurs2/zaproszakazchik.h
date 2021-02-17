#ifndef ZAPROSZAKAZCHIK_H
#define ZAPROSZAKAZCHIK_H

#include <QDialog>
#include <QtSql>


namespace Ui {
class ZaprosZakazchik;
}

class ZaprosZakazchik : public QDialog
{
    Q_OBJECT

public:
    explicit ZaprosZakazchik(QWidget *parent = nullptr, int number=0);
    ~ZaprosZakazchik();
    int Metod1();
    QString Metod2();
    int Metod3();

private:
    Ui::ZaprosZakazchik *ui;
    int id;
};

#endif // ZAPROSZAKAZCHIK_H
