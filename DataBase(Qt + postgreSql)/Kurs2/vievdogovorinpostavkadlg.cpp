#include "vievdogovorinpostavkadlg.h"
#include "ui_vievdogovorinpostavkadlg.h"
#include <QObject>
#include "Validator.h"

vievDogovorInPostavkaDlg::vievDogovorInPostavkaDlg(QSqlRelationalTableModel *model,QWidget *parent, int currec) :
    QDialog(parent),
    ui(new Ui::vievDogovorInPostavkaDlg)
{
    mdl=model;
    ui->setupUi(this);
    StrValidator *v=new StrValidator(ui->DgNumber);       //создание объекта, который займётся проверкой
    ui->DgNumber->setValidator(v);                        //подключение этого объекта к полю

    if(currec<0)
           currec=0;
       recnmb=currec;
       QSqlRecord record = mdl->record(currec);
       ui->DgNumber->setText(record.value("НомерДоговора").toString());
       ui->dateZakl->setDate(record.value("ДатаЗаключения").toDate());
       ui->dateIst->setDate(record.value("ДатаИстечения").toDate());
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
          ui->DgPost->setCurrentIndex(ui->DgPost->findText(record.value(4).toString()));
          while(query1.next())         //Проход по строкам запроса
          {
              ui->DgManager->addItem(query1.value(1).toString(),query1.value(0)); //поле с индексом 1 добавляется как значение в список, а с индексом 0 как UserData
          }
          ui->DgManager->setCurrentIndex(ui->DgManager->findText(record.value(5).toString()));
          while(query2.next())         //Проход по строкам запроса
          {
              ui->DgTip->addItem(query2.value(1).toString(),query2.value(0)); //поле с индексом 1 добавляется как значение в список, а с индексом 0 как UserData
          }
          ui->DgTip->setCurrentIndex(ui->DgTip->findText(record.value(6).toString()));
}

void vievDogovorInPostavkaDlg::on_Accept_clicked()    //При нажатии на кнопку "Сохранить"
{
   QMessageBox msgBox; //Стоит спросить уверен ли пользователь
   QString str=QString("Уверены что хотите сохранить изменения о договоре на сборку?");
   msgBox.setText(str);
   msgBox.setWindowTitle("Подтверждение");
   msgBox.setIcon(QMessageBox::Warning);
   msgBox.setInformativeText("Данная операция необратима!");
   QPushButton* pButtonYes = msgBox.addButton("Да", QMessageBox::YesRole); //Для корректного перевода, кнопки добавлены вручную
   QPushButton* pButtonNo = msgBox.addButton("Нет", QMessageBox::NoRole);
   msgBox.setDefaultButton(pButtonNo);
   msgBox.exec();
   if(msgBox.clickedButton()==pButtonYes)  //Если пользователь решился сохранить
   {
       //Сохранение последних изменений в модель
   mdl->setData(mdl->index(recnmb,1),ui->DgNumber->text().toInt());
   mdl->setData(mdl->index(recnmb,2),ui->dateZakl->date());
   mdl->setData(mdl->index(recnmb,3),ui->dateIst->date());
   mdl->setData(mdl->index(recnmb,4),ui->DgPost->itemData(ui->DgPost->currentIndex()));
   mdl->setData(mdl->index(recnmb,5),ui->DgManager->itemData(ui->DgManager->currentIndex()));
   mdl->setData(mdl->index(recnmb,6),ui->DgTip->itemData(ui->DgTip->currentIndex()));
       //Применение изменений
   mdl->submitAll();
   ui->Accept->setEnabled(false);
   ui->Decline->setEnabled(false);
   }
}

bool vievDogovorInPostavkaDlg::on_Decline_clicked()  //При нажатии на кнопку "Отменить"
{
   //Уверен ли пользователь что хочет всё отменить?
   QMessageBox msgBox;
   QString str=QString("Уверены что хотите отменить внесённые изменения?");
   msgBox.setText(str);
   msgBox.setWindowTitle("Подтверждение");
   msgBox.setIcon(QMessageBox::Warning);
   msgBox.setInformativeText("Данная операция необратима!");
   QPushButton* pButtonYes = msgBox.addButton("Да", QMessageBox::YesRole); //Для корректного перевода, кнопки добавлены вручную
   QPushButton* pButtonNo = msgBox.addButton("Нет", QMessageBox::NoRole);
   msgBox.setDefaultButton(pButtonYes);        //А вот тут будем считать что пользователь уверен
   msgBox.exec();

   if(msgBox.clickedButton()==pButtonYes)  //Если пользователь решился сохранить
   {
      //Отмена изменений
      mdl->revertAll();
      //Сброс значений полей формы к изначальным
      QSqlRecord record = mdl->record(recnmb);
      ui->DgNumber->setText(record.value("НомерДоговора").toString());
      ui->dateZakl->setDate(record.value("ДатаЗаключения").toDate());
      ui->dateIst->setDate(record.value("ДатаИстечения").toDate());
      return true;
   }
   return false;
}


void vievDogovorInPostavkaDlg::on_Close_clicked()  //Кнопка "Выход"
{
    close();
}

vievDogovorInPostavkaDlg::~vievDogovorInPostavkaDlg()
{
    delete ui;
}
