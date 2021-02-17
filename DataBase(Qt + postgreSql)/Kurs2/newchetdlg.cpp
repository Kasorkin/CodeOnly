#include "newchetdlg.h"
#include "ui_newchetdlg.h"

newChetdlg::newChetdlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newChetdlg)
{
    ui->setupUi(this);
    //для ограничения ввода
    StrValidator *v=new StrValidator(ui->ChNumber);       //создание объекта, который займётся проверкой
    ui->ChNumber->setValidator(v);                        //подключение этого объекта к полю
    StrValidator *s=new StrValidator(ui->ChSum);       //создание объекта, который займётся проверкой
    ui->ChSum->setValidator(s);
}

newChetdlg::~newChetdlg()
{
    delete ui;
}

newChetdlg::NewEl4 newChetdlg::addel()
{
   NewEl4 el4;                           //Объявление структуры
   el4.NumberChet=ui->ChNumber->text().toInt();
   el4.Summ=ui->ChSum->text().toInt();
   el4.OplChet=ui->ChOpl->isChecked();
   return el4;          //Структура с данными возвращается в основную форму
}
