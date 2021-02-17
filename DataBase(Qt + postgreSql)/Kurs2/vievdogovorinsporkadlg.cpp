#include "vievdogovorinsporkadlg.h"
#include "ui_vievdogovorinsporkadlg.h"
#include <QObject>
#include "Validator.h"

VievDogovorInSporkaDlg::VievDogovorInSporkaDlg(QSqlRelationalTableModel *model,QWidget *parent, int currec) :
    QDialog(parent),
    ui(new Ui::VievDogovorInSporkaDlg)
{
    mdl=model;
    ui->setupUi(this);
    StrValidator *v=new StrValidator(ui->NumberDg);       //создание объекта, который займётся проверкой
    ui->NumberDg->setValidator(v);                        //подключение этого объекта к полю;
    if(currec<0)
           currec=0;
       recnmb=currec;
       QSqlRecord record = mdl->record(currec);
       ui->NumberDg->setText(record.value("НомерДоговора").toString());
       ui->dateEdit->setDate(record.value("ДатаРождения").toDate());
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
              ui->comboBoxManager->addItem(query.value(1).toString(),query.value(0)); //поле с индексом 1 добавляется как значение в список, а с индексом 0 как UserData
          }
          ui->comboBoxManager->setCurrentIndex(ui->comboBoxManager->findText(record.value(6).toString()));
          while(query1.next())         //Проход по строкам запроса
          {
              ui->comboBoxZakaz->addItem(query1.value(1).toString(),query1.value(0)); //поле с индексом 1 добавляется как значение в список, а с индексом 0 как UserData
          }
          ui->comboBoxZakaz->setCurrentIndex(ui->comboBoxZakaz->findText(record.value(5).toString()));
          while(query2.next())         //Проход по строкам запроса
          {
              ui->comboBoxNumChet->addItem(query2.value(1).toString(),query2.value(0)); //поле с индексом 1 добавляется как значение в список, а с индексом 0 как UserData
          }
          ui->comboBoxNumChet->setCurrentIndex(ui->comboBoxNumChet->findText(record.value(7).toString()));
          if(record.value("Оплачено").toBool()==true)
          {
              ui->checkBoxOpl->setChecked(true);
          } else ui->checkBoxOpl->setChecked(false);

          if(record.value("Доставлено").toBool()==true)
          {
              ui->checkBoxDost->setChecked(true);
          } else ui->checkBoxDost->setChecked(false);
}

void VievDogovorInSporkaDlg::on_Accept_clicked()    //При нажатии на кнопку "Сохранить"
{
   QMessageBox msgBox; //Стоит спросить уверен ли пользователь
   QString str=QString("Уверены что хотите сохранить изменения о договоре на сборку?");//.arg(ui->anNameEdit->text());
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
   mdl->setData(mdl->index(recnmb,1),ui->NumberDg->text().toInt());
   mdl->setData(mdl->index(recnmb,2),ui->dateEdit->date());
   mdl->setData(mdl->index(recnmb,5),ui->comboBoxZakaz->itemData(ui->comboBoxZakaz->currentIndex()));
   mdl->setData(mdl->index(recnmb,6),ui->comboBoxManager->itemData(ui->comboBoxManager->currentIndex()));
   mdl->setData(mdl->index(recnmb,7),ui->comboBoxNumChet->itemData(ui->comboBoxNumChet->currentIndex()));
   if(ui->checkBoxOpl->isChecked())
       mdl->setData(mdl->index(recnmb,3),true);
   else
       mdl->setData(mdl->index(recnmb,3),false);
   if(ui->checkBoxDost->isChecked())
           mdl->setData(mdl->index(recnmb,4),true);
   else
       mdl->setData(mdl->index(recnmb,4),false);
       //Применение изменений
   mdl->submitAll();
   }
   ui->Accept->setEnabled(false);
   ui->Decline->setEnabled(false);
}

bool VievDogovorInSporkaDlg::on_Decline_clicked()  //При нажатии на кнопку "Отменить"
{
   //Уверен ли пользователь что хочет всё отменить?
   QMessageBox msgBox;
   QString str=QString("Уверены что хотите отменить внесённые изменения?");//.arg(ui->anNameEdit->text());
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
      ui->NumberDg->setText(record.value("НомерДоговора").toString());
      ui->dateEdit->setDate(record.value("ДатаЗаключения").toDate());
      return true;
   }
   return false;
}


void VievDogovorInSporkaDlg::on_Close_clicked()  //Кнопка "Выход"
{
    close();
}

VievDogovorInSporkaDlg::~VievDogovorInSporkaDlg()
{
    delete ui;
}
