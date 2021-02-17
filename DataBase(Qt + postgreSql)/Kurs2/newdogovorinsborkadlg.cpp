#include "newdogovorinsborkadlg.h"
#include "ui_newdogovorinsborkadlg.h"
#include "Validator.h"


newDogovorInSborkadlg::newDogovorInSborkadlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newDogovorInSborkadlg)
{
    ui->setupUi(this);
    StrValidator *v=new StrValidator(ui->NumberDg);       //создание объекта, который займётся проверкой
    ui->NumberDg->setValidator(v);                        //подключение этого объекта к полю
    QSqlQuery query;
    QSqlQuery query1;
    QSqlQuery query2;
    QString  str = "SELECT id, ФИО FROM Менеджер ORDER BY ФИО";
    QString  str1 = "SELECT id, ФИО FROM Заказчик ORDER BY ФИО";
    QString  str2 = "SELECT id, НомерСчета FROM Счет ORDER BY НомерСчета";

       if (!query.exec(str)||!query1.exec(str1)||!query2.exec(str2))  {                            //Выполнение запроса, в случае ошибки выдать предупреждение
           qDebug() <<  query.lastError().text();           //Так как в реальной ситуации запрос сработает всегда, вывод только в qDebug
           qDebug() <<  query1.lastError().text();
           qDebug() <<  query2.lastError().text();
       }
       while(query.next())         //Проход по строкам запроса
       {
           ui->comboBox2->addItem(query.value(1).toString(),query.value(0)); //поле с индексом 1 добавляется как значение в список, а с индексом 0 как UserData
       }
       while(query1.next())         //Проход по строкам запроса
       {
           ui->comboBox1->addItem(query1.value(1).toString(),query1.value(0)); //поле с индексом 1 добавляется как значение в список, а с индексом 0 как UserData
       }
       while(query2.next())         //Проход по строкам запроса
       {
           ui->comboBox3->addItem(query2.value(1).toString(),query2.value(0)); //поле с индексом 1 добавляется как значение в список, а с индексом 0 как UserData
       }
}

newDogovorInSborkadlg::~newDogovorInSborkadlg()
{
    delete ui;
}

newDogovorInSborkadlg::NewEl newDogovorInSborkadlg::addel()
{
   NewEl el;
   el.DgNumber=ui->NumberDg->text().toInt();   //Имя берётся из Line Edit
   el.DgDate=ui->dateEdit->date();
   el.DgZakazchic=ui->comboBox1->itemData(ui->comboBox1->currentIndex()).toInt();
   el.DgManager=ui->comboBox2->itemData(ui->comboBox2->currentIndex()).toInt();
   el.DgChet=ui->comboBox3->itemData(ui->comboBox3->currentIndex()).toInt();
   el.DgOpl=ui->checkBox1->isChecked();
   el.DgDost=ui->checkBox2->isChecked();
   return el;
}
