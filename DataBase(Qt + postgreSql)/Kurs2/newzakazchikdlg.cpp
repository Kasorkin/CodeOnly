#include "newzakazchikdlg.h"
#include "ui_newzakazchikdlg.h"

newZakazchikdlg::newZakazchikdlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newZakazchikdlg)
{
    ui->setupUi(this);
    //для ограничения ввода
    StrValidator *v=new StrValidator(ui->PASS);       //создание объекта, который займётся проверкой
    ui->PASS->setValidator(v);                        //подключение этого объекта к полю
    StrValidator *s=new StrValidator(ui->NumberTel);       //создание объекта, который займётся проверкой
    ui->NumberTel->setValidator(s);

}

newZakazchikdlg::~newZakazchikdlg()
{
    delete ui;
}

newZakazchikdlg::NewEk newZakazchikdlg::addel()
{
   NewEk ek;                           //Объявление структуры
   ek.Fio=ui->FIOZ->text();
   ek.dateRosh=ui->dateEdit->date();   //Имя берётся из Line Edit
   ek.Passport=ui->PASS->text().toInt();
   ek.NumberT=ui->NumberTel->text().toInt();
   return ek;          //Структура с данными возвращается в основную форму
}
