#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <QDialog>
#include <QtSql>

    //QLineEdit *inputEdit; // строковое поле для ввода
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

#endif // VALIDATOR_H
