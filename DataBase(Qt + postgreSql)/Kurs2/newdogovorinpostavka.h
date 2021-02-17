#ifndef NEWDOGOVORINPOSTAVKA_H
#define NEWDOGOVORINPOSTAVKA_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class newdogovorinPostavka;
}

class newdogovorinPostavka : public QDialog
{
    Q_OBJECT

public:
    explicit newdogovorinPostavka(QWidget *parent = nullptr);
    ~newdogovorinPostavka();
    struct NewEl{
        QDate DgDateZacl,DgDateIst;
        int DgManager,DgPost,DgNumber,DgTip;
    };
     NewEl addel();

private:
    Ui::newdogovorinPostavka *ui;
};

#endif // NEWDOGOVORINPOSTAVKA_H
