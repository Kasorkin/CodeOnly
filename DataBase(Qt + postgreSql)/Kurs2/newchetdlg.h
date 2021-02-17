#ifndef NEWCHETDLG_H
#define NEWCHETDLG_H

#include <QDialog>
#include <QFileDialog>
#include <QtSql>

namespace Ui {
class newChetdlg;
}

class newChetdlg : public QDialog
{
    Q_OBJECT

public:
    explicit newChetdlg(QWidget *parent = nullptr);
    ~newChetdlg();
    struct NewEl4 {              //Структура для хранения полей создаваемой записи
        int NumberChet,Summ;
        bool OplChet;
    };
    NewEl4 addel();

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
    Ui::newChetdlg *ui;
};

#endif // NEWCHETDLG_H
