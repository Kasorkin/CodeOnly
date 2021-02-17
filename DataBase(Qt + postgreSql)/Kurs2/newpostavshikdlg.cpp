#include "newpostavshikdlg.h"
#include "ui_newpostavshikdlg.h"
#include "Validator.h"

NewPostavshikdlg::NewPostavshikdlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewPostavshikdlg)
{
    ui->setupUi(this);
    StrValidator *v=new StrValidator(ui->PostRequ);       //создание объекта, который займётся проверкой
    ui->PostRequ->setValidator(v);                        //подключение этого объекта к полю

    QSqlQuery query;
    QString  str = "SELECT id,Тип FROM ПоставляемаяПродукция ORDER BY Тип";
//DISTINCT
       if (!query.exec(str))  {                            //Выполнение запроса, в случае ошибки выдать предупреждение
           qDebug() <<  query.lastError().text();           //Так как в реальной ситуации запрос сработает всегда, вывод только в qDebug
       }
       while(query.next())         //Проход по строкам запроса
       {
           ui->PostTip->addItem(query.value(1).toString(),query.value(0)); //поле с индексом 1 добавляется как значение в список, а с индексом 0 как UserData
       }
}

NewPostavshikdlg::NewEq NewPostavshikdlg::addel()
{
   NewEq eq;
   eq.PostNameCompany=ui->PostName->text();   //Имя берётся из Line Edit
   eq.PostDirector=ui->PostDir->text();
   eq.PostBuhgalter=ui->PostBuh->text();
   eq.PostRequisits=ui->PostRequ->text().toInt();
   eq.PostTip=ui->PostTip->itemData(ui->PostTip->currentIndex()).toInt();
   return eq;
}

NewPostavshikdlg::~NewPostavshikdlg()
{
    delete ui;
}
