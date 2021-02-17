#ifndef NEWDOGOVORINSBORKADLG_H
#define NEWDOGOVORINSBORKADLG_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class newDogovorInSborkadlg;
}

class newDogovorInSborkadlg : public QDialog
{
    Q_OBJECT

public:
    explicit newDogovorInSborkadlg(QWidget *parent = nullptr);
    ~newDogovorInSborkadlg();
    struct NewEl{
        //QString DgNumberDogovor,DgText,DgPostProduct,DgUsl;
        QDate DgDate;
        int DgZakazchic,DgManager,DgChet,DgNumber;
        bool DgOpl,DgDost;
    };
    NewEl addel();
private:
    Ui::newDogovorInSborkadlg *ui;
};

#endif // NEWDOGOVORINSBORKADLG_H
