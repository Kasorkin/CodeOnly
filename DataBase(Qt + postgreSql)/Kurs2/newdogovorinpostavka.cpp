#include "newdogovorinpostavka.h"
#include "ui_newdogovorinpostavka.h"
#include "Validator.h"

newdogovorinPostavka::newdogovorinPostavka(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newdogovorinPostavka)
{
    ui->setupUi(this);
    StrValidator *v=new StrValidator(ui->DgNumber);       //создание объекта, который займётся проверкой
    ui->DgNumber->setValidator(v);                        //подключение этого объекта к полю
    QSqlQuery query;
    QSqlQuery query1;
    QSqlQuery query2;
    QString  str = "SELECT id, НазваниеКомпании FROM Поставщик ORDER BY НазваниеКомпании";
    QString  str1 = "SELECT id, ФИО FROM Менеджер ORDER BY ФИО";
    QString  str2 = "SELECT id, Тип FROM ПоставляемаяПродукция ORDER BY Тип";

       if (!query.exec(str)||!query1.exec(str1)||!query2.exec(str2))  {                            //Выполнение запроса, в случае ошибки выдать предупреждение
           qDebug() <<  query.lastError().text();           //Так как в реальной ситуации запрос сработает всегда, вывод только в qDebug
           qDebug() <<  query1.lastError().text();
           qDebug() <<  query2.lastError().text();
       }
       while(query.next())         //Проход по строкам запроса
       {
           ui->DgPost->addItem(query.value(1).toString(),query.value(0)); //поле с индексом 1 добавляется как значение в список, а с индексом 0 как UserData
       }
       while(query1.next())         //Проход по строкам запроса
       {
           ui->DgManager->addItem(query1.value(1).toString(),query1.value(0)); //поле с индексом 1 добавляется как значение в список, а с индексом 0 как UserData
       }
       while(query2.next())         //Проход по строкам запроса
       {
           ui->DgTip->addItem(query2.value(1).toString(),query2.value(0)); //поле с индексом 1 добавляется как значение в список, а с индексом 0 как UserData
           qDebug() << query2.lastError().text();
       }
}

newdogovorinPostavka::~newdogovorinPostavka()
{
    delete ui;
}

newdogovorinPostavka::NewEl newdogovorinPostavka::addel()
{
   NewEl el;
   el.DgNumber=ui->DgNumber->text().toInt();   //Имя берётся из Line Edit
   el.DgDateZacl=ui->dateZakl->date();
   el.DgDateIst=ui->dateIst->date();
   el.DgPost=ui->DgPost->itemData(ui->DgPost->currentIndex()).toInt();
   el.DgManager=ui->DgManager->itemData(ui->DgManager->currentIndex()).toInt();
   el.DgTip=ui->DgTip->itemData(ui->DgTip->currentIndex()).toInt();
   return el;
}
