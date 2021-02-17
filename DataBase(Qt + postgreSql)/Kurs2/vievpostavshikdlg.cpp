#include "vievpostavshikdlg.h"
#include "ui_vievpostavshikdlg.h"
#include <QObject>
#include "Validator.h"

VievPostavshikDlg::VievPostavshikDlg(QSqlRelationalTableModel *model,QWidget *parent, int currec) :
    QDialog(parent),
    ui(new Ui::VievPostavshikDlg)
{
    mdl=model;
    ui->setupUi(this);
    StrValidator *v=new StrValidator(ui->PostRequ);       //создание объекта, который займётся проверкой
    ui->PostRequ->setValidator(v);                        //подключение этого объекта к полю

    if(currec<0)
           currec=0;
       recnmb=currec;
       QSqlRecord record = mdl->record(currec);
       ui->PostName->setText(record.value("НазваниеКомпании").toString());
       ui->PostDir->setText(record.value("Директор").toString());
       ui->PostBuh->setText(record.value("Бухгалтер").toString());
       ui->PostRequ->setText(record.value("Реквизиты").toString());
       QSqlQuery query;
       QString  str = "SELECT id, Тип FROM ПоставляемаяПродукция ORDER BY Тип";
          if (!query.exec(str))  {                            //Выполнение запроса, в случае ошибки выдать предупреждение
              qDebug() <<  query.lastError().text();           //Так как в реальной ситуации запрос сработает всегда, вывод только в qDebug
          }
          while(query.next())         //Проход по строкам запроса
          {
              ui->PostTip->addItem(query.value(1).toString(),query.value(0)); //поле с индексом 1 добавляется как значение в список, а с индексом 0 как UserData
          }
          ui->PostTip->setCurrentIndex(ui->PostTip->findText(record.value(5).toString()));
}

void VievPostavshikDlg::on_Accept_clicked()    //При нажатии на кнопку "Сохранить"
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
   mdl->setData(mdl->index(recnmb,1),ui->PostName->text());
   mdl->setData(mdl->index(recnmb,2),ui->PostDir->text());
   mdl->setData(mdl->index(recnmb,3),ui->PostBuh->text());
   mdl->setData(mdl->index(recnmb,4),ui->PostRequ->text().toInt());
   mdl->setData(mdl->index(recnmb,5),ui->PostTip->itemData(ui->PostTip->currentIndex()));
       //Применение изменений
   mdl->submitAll();
   ui->Accept->setEnabled(false);
   ui->Decline->setEnabled(false);

   }
}

bool VievPostavshikDlg::on_Decline_clicked()  //При нажатии на кнопку "Отменить"
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
      ui->PostName->setText(record.value("НазваниеКомпании").toString());
      ui->PostDir->setText(record.value("Директор").toString());
      ui->PostBuh->setText(record.value("Бухгалтер").toString());
      ui->PostRequ->setText(record.value("Реквизиты").toString());
      return true;
   }
   return false;
}


void VievPostavshikDlg::on_Close_clicked()  //Кнопка "Выход"
{
    close();
}


VievPostavshikDlg::~VievPostavshikDlg()
{
    delete ui;
}
