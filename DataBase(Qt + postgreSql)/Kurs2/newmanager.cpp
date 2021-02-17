#include "newmanager.h"
#include "ui_newmanager.h"

newManager::newManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newManager)
{
    ui->setupUi(this);
}

newManager::~newManager()
{
    delete ui;
}

newManager::NewEl newManager::addel()
{
   NewEl el;                           //Объявление структуры
   el.FIO=ui->FIO->text();   //Имя берётся из Line Edit
   return el;          //Структура с данными возвращается в основную форму
}
