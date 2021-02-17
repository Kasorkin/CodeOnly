#ifndef NEWZAKAZCHIKDLG_H
#define NEWZAKAZCHIKDLG_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class newZakazchikdlg;
}

class newZakazchikdlg : public QDialog
{
    Q_OBJECT

public:
    explicit newZakazchikdlg(QWidget *parent = nullptr);
    ~newZakazchikdlg();
    struct NewEk{
        QString Fio;
        int NumberT,Passport;
        QDate dateRosh;
    };
    NewEk addel();


//private slots:
    //валидатор для проверки текста
    QLineEdit *inputEdit; // строковое поле для ввода
    class StrValidator:public QValidator // класс компонента проверки ввода, в данной программе он всегда принимает строку
    {
        public:
        StrValidator(QObject *parent):QValidator(parent){}
        virtual State validate(QString &str,int &pos)const
        {
            bool isOk;
            str.toInt(&isOk);
            if(isOk)
            {
                 return Acceptable;
            }
            else return Invalid;
            // метод всегда принимает вводимую строку
        }
    };

private:
    Ui::newZakazchikdlg *ui;
};

#endif // NEWZAKAZCHIKDLG_H
